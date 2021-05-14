#ifndef UART_H_
#define UART_H_

void UART_Initialize(void);
void UART_SetTxInterruptHandler(void (* interruptHandler)());
void UART_SetRxInterruptHandler(void (* interruptHandler)());

int UART_ReadFlag();
void UART_WriteMessage(uint8_t *buffer);
uint8_t UART_Read();
void UART_Write(uint8_t byte);
bool UART_IsRxReady();
bool UART_IsTxReady();


#endif /* UART_H_ */