#include "lora_module.h"
#include "string.h"
#include "stdio.h"

#define RELAY1_PIN GPIO_PIN_0
#define RELAY1_PORT GPIOB
#define RELAY2_PIN GPIO_PIN_1
#define RELAY2_PORT GPIOB
#define RELAY3_PIN GPIO_PIN_2
#define RELAY3_PORT GPIOB
#define RELAY4_PIN GPIO_PIN_4
#define RELAY4_PORT GPIOB

char rxBuffer[256];
volatile uint16_t rxIndex = 0;

extern UART_HandleTypeDef huart1;

volatile uint8_t relay1_state = 0; // 0 for OFF, 1 for ON
volatile uint8_t relay2_state = 0;
volatile uint8_t relay3_state = 0;
volatile uint8_t relay4_state = 0;

char cmdQueue[][256] = {
    "AT\r\n",
    "AT+MODE=TEST\r\n",
    "AT+TEST=RFCFG,866,SF12,125,12,15,14,ON,OFF,OFF\r\n",
    "AT+TEST=RXLRPKT\r\n"
};

void TransmitCommand(uint8_t cmdIndex) {
    printf("Transmitting Command: %s", cmdQueue[cmdIndex]);  // Debug print for command
    HAL_UART_Transmit_IT(&huart1, (uint8_t *)cmdQueue[cmdIndex], strlen(cmdQueue[cmdIndex]));
}

void ReceiveResponse(void) {
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rxBuffer[rxIndex], 1);
}

void lora_config() {
    TransmitCommand(0); // AT command
    HAL_Delay(500);
    ReceiveResponse();

    TransmitCommand(1); // AT+MODE=TEST
    HAL_Delay(500);
    ReceiveResponse();

    TransmitCommand(2); // AT+TEST=RFCFG
    HAL_Delay(500);
    ReceiveResponse();

    TransmitCommand(3); // AT+TEST=RXLRPKT
    HAL_Delay(500);
    ReceiveResponse();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        if (rxBuffer[rxIndex] == '\n') {
            rxBuffer[rxIndex + 1] = '\0'; // Null-terminate the buffer
            char *payloadStart = strstr((char *)rxBuffer, "+TEST: RX \"");
                        if (payloadStart) {
                            payloadStart += strlen("+TEST: RX \"");

                            char extractedData[256];
                            char *endQuote = strchr(payloadStart, '\"');
                            if (endQuote) {
                                size_t length = endQuote - payloadStart;
                                strncpy(extractedData, payloadStart, length);
                                extractedData[length] = '\0';

                                char asciiString[128];
                                size_t i, j;
                                for (i = 0, j = 0; i < length; i += 2) {
                                    unsigned int hexValue;
                                    sscanf(&extractedData[i], "%2x", &hexValue);
                                    asciiString[j++] = (char)hexValue;
                                }
                                asciiString[j] = '\0';

                                printf("Last Received Data: %s\n", asciiString);

                                if (strcmp(asciiString, "SL1:ON") == 0) {
                                    HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_SET);
                                    relay1_state = 1;
                                } else if (strcmp(asciiString, "SL1:OFF") == 0) {
                                    HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_RESET);
                                    relay1_state = 0;
                                } else if (strcmp(asciiString, "SL2:ON") == 0) {
                                    HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_SET);
                                    relay2_state = 1;
                                } else if (strcmp(asciiString, "SL2:OFF") == 0) {
                                    HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_RESET);
                                    relay2_state = 0;
                                } else if (strcmp(asciiString, "SL3:ON") == 0) {
                                    HAL_GPIO_WritePin(RELAY3_PORT, RELAY3_PIN, GPIO_PIN_SET);
                                    relay3_state = 1;
                                } else if (strcmp(asciiString, "SL3:OFF") == 0) {
                                    HAL_GPIO_WritePin(RELAY3_PORT, RELAY3_PIN, GPIO_PIN_RESET);
                                    relay3_state = 0;
                                } else if (strcmp(asciiString, "SL4:ON") == 0) {
                                    HAL_GPIO_WritePin(RELAY4_PORT, RELAY4_PIN, GPIO_PIN_SET);
                                    relay4_state = 1;
                                } else if (strcmp(asciiString, "SL4:OFF") == 0) {
                                    HAL_GPIO_WritePin(RELAY4_PORT, RELAY4_PIN, GPIO_PIN_RESET);
                                    relay4_state = 0;
                                }

                                UpdateLCD();
                            }
                        }
            // Handle received data (you can pass control to another module here)
            rxIndex = 0; // Reset buffer index for the next message
        } else {
            rxIndex++;
        }
        ReceiveResponse(); // Continue receiving
    }
}
