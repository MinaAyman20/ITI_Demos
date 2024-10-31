#ifndef ERROR
#define ERROR
typedef enum
{
    Ok,
    NotOk,
    NullPointerError,
    ArgumentError,
    TimeOutError 
}ErrorStatus_t;

#define NULL ((void *)0)

#endif 