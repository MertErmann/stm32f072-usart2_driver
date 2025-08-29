/* -----------------------------------------------------------
 * STM32F0 Minimal UART2 Driver (PA2=TX, PA3=RX)
 * Author: MERT ERMAN
 * UartDriver.c
 * Implementation of a minimal blocking USART2 driver for STM32F0.
 * - Sets PA2/PA3 to AF1 for TX/RX
 * - Programs BRR using ProjectConfig.h clocks/baud
 * - Provides simple byte-level TX/RX routines
 * Internal helpers are kept static to avoid leaking symbols.
 */

#include "stm32f0xx.h"
#include "UARTConfig.h"
#include "UART_Driver.h"

/* ---- Low-level bit definitions ---- */
#define GPIOAEN    (1U<<17)
#define UART2EN    (1U<<17)
#define UART2TEN   (1U<<3)
#define UART2CR1EN (1U<<0)
#define SR_TXE     (1U<<7)
#define SR_RXE     (1U<<5)
#define CR1_RE     (1U<<2)

/* ---- Private helpers ---- */
/* Computes BRR using "rounded" divider: (PeriphClk + Baud/2) / Baud.
 * Matches the typical integer BRR calculation for oversampling by 16. */
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

/* Writes BRR field of the given USART instance using the computed divider. */
static void set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

/* ---- Public API ---- */
void uart2rxtx_init(void){
    /* Enable GPIOA clock */
    RCC->AHBENR |= GPIOAEN;

    /* PA2 -> AF mode */
    GPIOA->MODER &= ~(1U<<4);
    GPIOA->MODER |=  (1U<<5);

    /* PA3 -> AF mode */
    GPIOA->MODER &= ~(1U<<6);
    GPIOA->MODER |=  (1U<<7);

    /* Select AF1 for PA2 (bits 11:8) */
    GPIOA->AFR[0] |=  (1U<<8);
    GPIOA->AFR[0] &= ~(1U<<9);
    GPIOA->AFR[0] &= ~(1U<<10);
    GPIOA->AFR[0] &= ~(1U<<11);

    /* Select AF1 for PA3 (bits 15:12) */
    GPIOA->AFR[0] |=  (1U<<12);
    GPIOA->AFR[0] &= ~(1U<<13);
    GPIOA->AFR[0] &= ~(1U<<14);
    GPIOA->AFR[0] &= ~(1U<<15);

    /* Enable USART2 clock */
    RCC->APB1ENR |= UART2EN;

    /* Set baud rate */
    set_baudrate(USART2, APB1_CLK, UART_BAUD);

    /* Enable TX and RX */
    USART2->CR1 = (UART2TEN | CR1_RE);

    /* Enable USART2 */
    USART2->CR1 |= UART2CR1EN;
}

void uart2_write(int ch){
    /* Wait until TX buffer empty */
    while(!(USART2->ISR & SR_TXE)) { }
    USART2->TDR = (ch & 0xFF);
}

int uart2_read(void){
    /* Wait until RX buffer not empty */
    while(!(USART2->ISR & SR_RXE)) { }
    return (int)(USART2->RDR & 0xFF);
}

/* ---- Private helper definitions ---- */
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
    return (uint16_t)((PeriphClk + (BaudRate/2U)) / BaudRate);
}

static void set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
    USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}
