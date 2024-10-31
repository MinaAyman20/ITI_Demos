#include "MCAL/USART.h"
#include "MCAL/GPIO.h"
#include "MCAL/SYSTICK.h"
#include "HAL/Switch.h"
#include "HAL/LCD.h"
#include "MCAL/RCC.h"
#include "SERVICE/SCHED.h"
#include "MCAL/NVIC.h"
#include "STM32f401CC_peripherals_interrupt.h"

USART_RXBuffer rx_button_buff = 
	{
		.Channel = USART1,
		.Data = NULL,
		.Size = 1,
		.Index = 0
	};

extern void recieve_callback(void);



void lcd_done(void)
{
	USART_RegisterCallBackFunction(USART1,RECEIVE,recieve_callback);
	USART_ReceiveBuffer(&rx_button_buff);
}


int main()
{
	RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOA,Status_Enable);
	RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOC,Status_Enable);
	RCC_Control_AHB1Peripherals(RCC_PERI_AHB1ENR_GPIOB,Status_Enable);
	RCC_Control_APB2Peripherals(RCC_PERI_APB2ENR_USART1,Status_Enable);


	USART_Config usart_config = {
        .Channel = USART1,
        .Oversampling = OVERSAMPLING_8,
        .USART_Enable = ENABLE,
        .WordLength = WORDLENGTH_8,
        .ParityControl = PARITY_NONE,
        .TransComplete_Int = ENABLE,
        .TransEnable = ENABLE,
		.ReceiveEnable = ENABLE,
		.ReceiveDateRegisterEmpty_Int = ENABLE,
        .BaudRate = 9600
    };

	GPIO_CONFIG_T TX_PIN = 
	{
		.Mode = GPIO_MODE_AF_PP,
		.Speed = GPIO_SPEED_HIGH,
		.Port = GPIO_PORT_A,
		.Pin = GPIO_PIN_9,
		.Alternative = GPIO_ALTERNATIVE_USART1_2
	};

	GPIO_CONFIG_T RX_PIN = 
	{
		.Mode = GPIO_MODE_AF_PP_PU,
		.Speed = GPIO_SPEED_HIGH,
		.Port = GPIO_PORT_A,
		.Pin = GPIO_PIN_10,
		.Alternative = GPIO_ALTERNATIVE_USART1_2
	};

	GPIO_InitPin(&TX_PIN);
	GPIO_InitPin(&RX_PIN);


	LCD_enuInitAsync(lcd_done);	
	Switch_init();
	NVIC_EnableIRQ(USART1_IRQ);
	USART_Init(&usart_config);
	SCHED_Init();
	SCHED_Start();	

	while (1)
	{
	}
	
}


