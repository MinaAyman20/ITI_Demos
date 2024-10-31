/******************************************************************************
 *
 * Module: USART Driver.
 *
 * File Name: MUSART_prog.c
 *
 * Description: Driver's APIs' Implementation and typedefs' declaration.
 *
 * Authors: Momen Hamed.
 *
 *******************************************************************************/



/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/MUSART/MUSART_interface.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

// #define USART_BUADRATE_MASK 0x0000FFFF
#define USART_PERI_NUM 3
#define USART_PERI_ENABLE 0x00002000
#define USART_SYNC_TXE_FLAG 0x00000080
#define USART_SYNC_RXNE_FLAG 0x00000020
#define USART_TX_ENABLE_FLAG 0x00000008
#define USART_TXEIE_ENABLE_FLAG 0x00000080
#define USART_RX_ENABLE_FLAG 0x00000004
#define USART_RXNEIE_ENABLE_FLAG 0x00000020
#define USART_REQ_STATE_BUSY 1
#define USART_REQ_STATE_READY 0
#define USART_PERI_INDEX_FLAG 0x00000003
#define USART_TX_DONE_IRQ 0x00000080
#define USART_RX_DONE_IRQ 0x00000020
#define USART_LBD_FLAG 0x00000100
#define USART_REG_NUM 3
#define USART_FRACTION_OVERFLOW_LIMIT 0x10
#define USART_4_BIT_OFFSET 4
#define USART_FIRST_BYTE_MASK 0x0F
#define USART_SECOND_BYTE_MASK 0xF0
#define USART_SR_CLEAR_MASK 0xFFFFFFFF
#define USART_SEND_BREAK_MASK 0x00000001

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct
{
    volatile u32 SR;
    volatile u32 DR;
    volatile u32 BRR;
    volatile u32 CR1;
    volatile u32 CR2;
    volatile u32 CR3;
    volatile u32 GTPR;
} USART_Peri_t;

typedef struct
{
    u8 *data;
    u32 pos;
    u32 size;
} buffer_t;

typedef struct
{
    buffer_t buffer;
    u8 state;
    CallBack_t CallBack;
} TX_Req_t;

typedef struct
{
    buffer_t buffer;
    u8 state;
    CallBack_t CallBack;
} RX_Req_t;

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
TX_Req_t TX_Request[USART_PERI_NUM];
RX_Req_t RX_Request[USART_PERI_NUM];
USART_Peri_t *USART_ADD[USART_REG_NUM] = {(USART_Peri_t *)0x40011000, (USART_Peri_t *)0x40004400, (USART_Peri_t *)0x40011400};
CallBack_t BreakCallBack[USART_PERI_NUM];
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

Error_Status
USART_Init(USART_cfg_t USART_CfgArr)
{
    Error_Status LOC_Status = Status_NOK;
    f32 LOC_BRRValue = 0;
    u32 LOC_CR1Value = 0;
    u32 LOC_CR2Value = 0;
    u16 LOC_Mantissa;
    u16 LOC_Fraction;
    u32 LOC_USARTDIV;
    u32 LOC_OverSampling;

    if (USART_CfgArr.address > USART_Peri_6 || USART_CfgArr.OverSampling > USART_OVERSAMPLING_8)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else if (USART_CfgArr.ParityControl > USART_PARITY_ENABLE || USART_CfgArr.ParitySelect > USART_PARITY_ODD)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else if (USART_CfgArr.StopBits > USART_STOP_BITS_2 || USART_CfgArr.WordLength > USART_WORD_LENGTH_9)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else
    {
        LOC_Status = Status_OK;
        // get the over sampling status 1 or 0 using the USART_OVERSAMPLING_8 value
        LOC_OverSampling = USART_CfgArr.OverSampling / USART_OVERSAMPLING_8;
        // calculate the USARTDIV value and multiply by 1000 to get the fraction as integer
        LOC_USARTDIV = (((u64)USART_CLK * 1000) / (USART_CfgArr.BaudRate * (8 * (2 - LOC_OverSampling))));

        LOC_Mantissa = LOC_USARTDIV / 1000;
        LOC_Fraction = (LOC_USARTDIV % 1000) * (8 * (2 - LOC_OverSampling));

        // Check if the fraction part needs rounding
        if (LOC_Fraction % 1000 >= 500)
        {
            // Round up the fraction part
            LOC_Fraction = (LOC_Fraction / 1000) + 1;
        }
        else
        {
            LOC_Fraction = LOC_Fraction / 1000;
        }
        // check if there is any carry from the fraction
        if (LOC_Fraction >= USART_FRACTION_OVERFLOW_LIMIT)
        {
            LOC_Mantissa += LOC_Fraction & USART_SECOND_BYTE_MASK;
        }

        LOC_BRRValue = (LOC_Mantissa << USART_4_BIT_OFFSET) | (LOC_Fraction & USART_FIRST_BYTE_MASK);
        LOC_CR1Value = USART_PERI_ENABLE | USART_CfgArr.WordLength | USART_CfgArr.OverSampling;
        LOC_CR1Value |= USART_CfgArr.ParityControl | USART_CfgArr.ParitySelect | USART_RX_ENABLE_FLAG | USART_TX_ENABLE_FLAG;
        LOC_CR2Value = USART_CfgArr.StopBits;

        (USART_ADD[USART_CfgArr.address])->BRR = LOC_BRRValue;
        (USART_ADD[USART_CfgArr.address])->CR1 = LOC_CR1Value;
        (USART_ADD[USART_CfgArr.address])->CR2 = LOC_CR2Value;
    }

    return LOC_Status;
}

Error_Status USART_SendByte(USART_Req_t USART_Req)
{
    Error_Status LOC_Status = Status_NOK;
    volatile u16 TimeOut = 3000;

    if (USART_Req.USART_Peri > USART_Peri_6)
    {
        LOC_Status = Status_Null_Pointer;
    }
    else if (USART_Req.length > 1)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else if (TX_Request[USART_Req.USART_Peri].state == USART_REQ_STATE_BUSY)
    {
        LOC_Status = Status_USART_Busy_Buffer;
    }
    else
    {
        LOC_Status = Status_OK;
        TX_Request[USART_Req.USART_Peri].state = USART_REQ_STATE_BUSY;
        (USART_ADD[USART_Req.USART_Peri])->DR = *(USART_Req.buffer);

        while (TimeOut)
        {
            TimeOut--;
        }

        TX_Request[USART_Req.USART_Peri].state = USART_REQ_STATE_READY;
    }
    return LOC_Status;
}

Error_Status USART_GetByte(USART_Req_t USART_Req)
{
    Error_Status LOC_Status = Status_NOK;
    u16 TimeOut = 60000;

    if (USART_Req.buffer == NULL)
    {
        LOC_Status = Status_Null_Pointer;
    }
    else if (USART_Req.USART_Peri > USART_Peri_6 || USART_Req.length > 1)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else if (RX_Request[USART_Req.USART_Peri].state == USART_REQ_STATE_BUSY)
    {
        LOC_Status = Status_USART_Busy_Buffer;
    }
    {
        LOC_Status = Status_OK;
        RX_Request[USART_Req.USART_Peri].state = USART_REQ_STATE_BUSY;
        while (!((USART_ADD[USART_Req.USART_Peri])->SR & USART_SYNC_RXNE_FLAG) && TimeOut)
        {
            TimeOut--;
        }

        if (!TimeOut)
        {
            LOC_Status = Status_USART_TimeOut;
        }
        else
        {
            *(USART_Req.buffer) = (USART_ADD[USART_Req.USART_Peri])->DR;
        }

        RX_Request[USART_Req.USART_Peri].state = USART_REQ_STATE_BUSY;
    }
    return LOC_Status;
}

Error_Status USART_TXBufferAsyncZC(USART_Req_t USART_Req)
{

    Error_Status LOC_Status = Status_NOK;

    if (USART_Req.buffer == NULL)
    {
        LOC_Status = Status_Null_Pointer;
    }
    else if (TX_Request[USART_Req.USART_Peri].state == USART_REQ_STATE_BUSY)
    {
        LOC_Status = Status_USART_Busy_Buffer;
    }
    else if (USART_Req.USART_Peri > USART_Peri_6)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else
    {
        TX_Request[USART_Req.USART_Peri].buffer.data = USART_Req.buffer;
        TX_Request[USART_Req.USART_Peri].buffer.size = USART_Req.length;
        TX_Request[USART_Req.USART_Peri].buffer.pos = 0;
        TX_Request[USART_Req.USART_Peri].CallBack = USART_Req.CB;
        TX_Request[USART_Req.USART_Peri].state = USART_REQ_STATE_BUSY;

        (USART_ADD[USART_Req.USART_Peri])->DR = TX_Request[USART_Req.USART_Peri].buffer.data[0];
        TX_Request[USART_Req.USART_Peri].buffer.pos++;
        (USART_ADD[USART_Req.USART_Peri])->CR1 |= USART_TXEIE_ENABLE_FLAG;
    }

    return LOC_Status;
}

Error_Status USART_RXBufferAsyncZC(USART_Req_t USART_Req)
{

    Error_Status LOC_Status = Status_NOK;

    if (USART_Req.buffer == NULL)
    {
        LOC_Status = Status_Null_Pointer;
    }
    else if (RX_Request[USART_Req.USART_Peri].state == USART_REQ_STATE_BUSY)
    {
        LOC_Status = Status_USART_Busy_Buffer;
    }
    else if (USART_Req.USART_Peri > USART_Peri_6)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else
    {
        RX_Request[USART_Req.USART_Peri].buffer.data = USART_Req.buffer;
        RX_Request[USART_Req.USART_Peri].buffer.size = USART_Req.length;
        RX_Request[USART_Req.USART_Peri].buffer.pos = 0;
        RX_Request[USART_Req.USART_Peri].CallBack = USART_Req.CB;
        RX_Request[USART_Req.USART_Peri].state = USART_REQ_STATE_BUSY;

        (USART_ADD[USART_Req.USART_Peri])->SR &= ~USART_RX_DONE_IRQ;
        (USART_ADD[USART_Req.USART_Peri])->CR1 |= USART_RXNEIE_ENABLE_FLAG;
    }
    return LOC_Status;
}

Error_Status USART_LIN_Init(USART_LIN_cfg_t USART_LIN_CfgArr)
{
    Error_Status LOC_Status = Status_NOK;
    u32 LOC_CR2Value = 0;

    if (USART_LIN_CfgArr.USART_Peri > USART_Peri_6 || USART_LIN_CfgArr.LIN_Mode > USART_LIN_MODE_ENABLE)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else if (USART_LIN_CfgArr.LIN_IRQ > USART_LIN_IRQ_ENABLE || USART_LIN_CfgArr.LIN_BreakLength > USART_LIN_BRK_LENGTH_11)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else
    {
        LOC_Status = Status_OK;
        LOC_CR2Value = USART_LIN_CfgArr.LIN_Mode | USART_LIN_CfgArr.LIN_IRQ | USART_LIN_CfgArr.LIN_BreakLength;

        (USART_ADD[USART_LIN_CfgArr.USART_Peri])->CR2 = LOC_CR2Value;
    }

    return LOC_Status;
}

Error_Status USART_GenerateBreak(u8 USART_Peri)
{
    Error_Status LOC_Status = Status_NOK;

    if (USART_Peri > USART_Peri_6)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else
    {
        LOC_Status = Status_OK;
        (USART_ADD[USART_Peri])->CR1 |= USART_SEND_BREAK_MASK;
    }

    return LOC_Status;
}

Error_Status USART_Set_BreakCallBack(u8 USART_Peri, CallBack_t CB)
{
    Error_Status LOC_Status = Status_NOK;

    if (USART_Peri > USART_Peri_6)
    {
        LOC_Status = Status_Invalid_Input;
    }
    else if (CB == NULL)
    {
        LOC_Status = Status_Null_Pointer;
    }
    else
    {
        LOC_Status = Status_OK;
        BreakCallBack[USART_Peri] = CB;
    }

    return LOC_Status;
}

void USART1_IRQHandler(void)
{
    if ((USART_ADD[USART_Peri_1])->SR & USART_LBD_FLAG)
    {
        if (BreakCallBack[USART_Peri_1])
        {
            (USART_ADD[USART_Peri_1])->SR &= ~USART_LBD_FLAG;
            BreakCallBack[USART_Peri_1]();
        }
    }

    if ((USART_ADD[USART_Peri_1])->SR & USART_RX_DONE_IRQ && (RX_Request[USART_Peri_1].state == USART_REQ_STATE_BUSY))
    {
        if (RX_Request[USART_Peri_1].buffer.pos < RX_Request[USART_Peri_1].buffer.size)
        {
            RX_Request[USART_Peri_1].buffer.data[RX_Request[USART_Peri_1].buffer.pos] = (USART_ADD[USART_Peri_1])->DR;
            RX_Request[USART_Peri_1].buffer.pos++;
        }

        if (RX_Request[USART_Peri_1].buffer.pos == RX_Request[USART_Peri_1].buffer.size)
        {
            (USART_ADD[USART_Peri_1])->CR1 &= ~USART_RXNEIE_ENABLE_FLAG;
            RX_Request[USART_Peri_1].state = USART_REQ_STATE_READY;
            if (RX_Request[USART_Peri_1].CallBack)
            {
                RX_Request[USART_Peri_1].CallBack();
            }
        }
    }
    /*adding the second condition to ensure the tx is not executed when the receive event happens*/
    if ((USART_ADD[USART_Peri_1])->SR & USART_TX_DONE_IRQ && (TX_Request[USART_Peri_1].state == USART_REQ_STATE_BUSY))
    {
        if (TX_Request[USART_Peri_1].buffer.pos < TX_Request[USART_Peri_1].buffer.size)
        {
            (USART_ADD[USART_Peri_1])->DR = TX_Request[USART_Peri_1].buffer.data[TX_Request[USART_Peri_1].buffer.pos];
            TX_Request[USART_Peri_1].buffer.pos++;
        }
        else
        {
            (USART_ADD[USART_Peri_1])->CR1 &= ~USART_TXEIE_ENABLE_FLAG;
            TX_Request[USART_Peri_1].state = USART_REQ_STATE_READY;

            if (TX_Request[USART_Peri_1].CallBack)
            {
                TX_Request[USART_Peri_1].CallBack();
            }
        }
    }
}

void USART2_IRQHandler(void)
{
    if ((USART_ADD[USART_Peri_2])->SR & USART_LBD_FLAG)
    {
        if (BreakCallBack[USART_Peri_2])
        {
            (USART_ADD[USART_Peri_2])->SR &= ~USART_LBD_FLAG;
            BreakCallBack[USART_Peri_2]();
        }
    }

    if ((USART_ADD[USART_Peri_2])->SR & USART_RX_DONE_IRQ && (RX_Request[USART_Peri_2].state == USART_REQ_STATE_BUSY))
    {
        if (RX_Request[USART_Peri_2].buffer.pos < RX_Request[USART_Peri_2].buffer.size)
        {
            RX_Request[USART_Peri_2].buffer.data[RX_Request[USART_Peri_2].buffer.pos] = (USART_ADD[USART_Peri_2])->DR;
            RX_Request[USART_Peri_2].buffer.pos++;
        }
        if (RX_Request[USART_Peri_2].buffer.pos == RX_Request[USART_Peri_2].buffer.size)
        {
            (USART_ADD[USART_Peri_2])->CR1 &= ~USART_RXNEIE_ENABLE_FLAG;
            RX_Request[USART_Peri_2].state = USART_REQ_STATE_READY;
            if (RX_Request[USART_Peri_2].CallBack)
            {
                RX_Request[USART_Peri_2].CallBack();
            }
        }
    }

    if ((USART_ADD[USART_Peri_2])->SR & USART_TX_DONE_IRQ && (TX_Request[USART_Peri_2].state == USART_REQ_STATE_BUSY))
    {
        if (TX_Request[USART_Peri_2].buffer.pos < TX_Request[USART_Peri_2].buffer.size)
        {
            (USART_ADD[USART_Peri_2])->DR = TX_Request[USART_Peri_2].buffer.data[TX_Request[USART_Peri_2].buffer.pos];
            TX_Request[USART_Peri_2].buffer.pos++;
        }
        else
        {
            (USART_ADD[USART_Peri_2])->CR1 &= ~USART_TXEIE_ENABLE_FLAG;
            TX_Request[USART_Peri_2].state = USART_REQ_STATE_READY;
            if (TX_Request[USART_Peri_2].CallBack)
            {
                TX_Request[USART_Peri_2].CallBack();
            }
        }
    }
}

void USART6_IRQHandler(void)
{
    if ((USART_ADD[USART_Peri_6])->SR & USART_LBD_FLAG)
    {
        if (BreakCallBack[USART_Peri_6])
        {
            (USART_ADD[USART_Peri_6])->SR &= ~USART_LBD_FLAG;
            BreakCallBack[USART_Peri_6]();
        }
    }

    if ((USART_ADD[USART_Peri_6])->SR & USART_RX_DONE_IRQ && (TX_Request[USART_Peri_6].state == USART_REQ_STATE_BUSY))
    {
        if (RX_Request[USART_Peri_6].buffer.pos < RX_Request[USART_Peri_6].buffer.size)
        {
            RX_Request[USART_Peri_6].buffer.data[RX_Request[USART_Peri_6].buffer.pos] = (USART_ADD[USART_Peri_6])->DR;
            RX_Request[USART_Peri_6].buffer.pos++;
        }
        if (RX_Request[USART_Peri_6].buffer.pos == RX_Request[USART_Peri_6].buffer.size)
        {
            (USART_ADD[USART_Peri_6])->CR1 &= ~USART_RXNEIE_ENABLE_FLAG;
            RX_Request[USART_Peri_6].state = USART_REQ_STATE_READY;
            if (RX_Request[USART_Peri_6].CallBack)
            {
                RX_Request[USART_Peri_6].CallBack();
            }
        }
    }

    if ((USART_ADD[USART_Peri_6])->SR & USART_TX_DONE_IRQ && (TX_Request[USART_Peri_6].state == USART_REQ_STATE_BUSY))
    {
        if (TX_Request[USART_Peri_6].buffer.pos < TX_Request[USART_Peri_6].buffer.size)
        {
            (USART_ADD[USART_Peri_6])->DR = TX_Request[USART_Peri_6].buffer.data[TX_Request[USART_Peri_6].buffer.pos];
            TX_Request[USART_Peri_6].buffer.pos++;
        }
        else
        {
            (USART_ADD[USART_Peri_6])->CR1 &= ~USART_TXEIE_ENABLE_FLAG;
            TX_Request[USART_Peri_6].state = USART_REQ_STATE_READY;
            if (TX_Request[USART_Peri_6].CallBack)
            {
                TX_Request[USART_Peri_6].CallBack();
            }
        }
    }
}
