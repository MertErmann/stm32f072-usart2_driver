/* -----------------------------------------------------------
 * STM32F0 Minimal UART2 Driver (PA2=TX, PA3=RX)
 * Author: MERT ERMAN
 * UartDriver.h
 * Public API for a minimal USART2 driver (PA2=TX, PA3=RX, AF1) on STM32F0.
 * Keep only user-facing declarations and required includes here.
 * Implementation details live in UartDriver.c.
 */

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "stm32f0xx.h"

/* Initializes GPIOA (PA2/PA3) to AF1 and configures USART2 with the baud
 * from ProjectConfig.h. Enables TX and RX in blocking mode. */
void uart2rxtx_init(void);

/* Sends a single byte (blocking). Argument is truncated to 8 bits. */
void uart2_write(int ch);

/* Receives a single byte (blocking). Returns 0..255. */
int uart2_read(void);

#endif /* UART_DRIVER_H */
