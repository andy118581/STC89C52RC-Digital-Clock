#ifndef __UART_H__
#define __UART_H__

//調用函数：
void UART_Init(void);
void UART_SendByte(unsigned char Byte);
void UART_SendTime(unsigned int hr,unsigned int min,unsigned int sec);

#endif