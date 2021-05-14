#ifndef UART_H_
#define UART_H_

void UART_Initialize(void);
void UART_SetTxInterruptHandler(void (* interruptHandler)());
void UART_SetRxInterruptHandler(void (* interruptHandler)());


#endif /* UART_H_ */