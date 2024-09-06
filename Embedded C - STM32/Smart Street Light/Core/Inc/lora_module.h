#ifndef LORA_MODULE_H
#define LORA_MODULE_H

extern char rxBuffer[256];
//extern volatile uint16_t rxIndex;
//extern volatile uint8_t relay1_state;
//extern volatile uint8_t relay2_state;
//extern volatile uint8_t relay3_state;
//extern volatile uint8_t relay4_state;

#include "main.h"

extern char rxBuffer[256];
//extern volatile uint16_t rxIndex;
void TransmitCommand(uint8_t cmdIndex);
void ReceiveResponse(void);
void lora_config(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif // LORA_MODULE_H
