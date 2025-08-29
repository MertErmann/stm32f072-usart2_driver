/* -----------------------------------------------------------
 * STM32F0 Minimal UART2 Driver (PA2=TX, PA3=RX)
 * Author: MERT ERMAN
 * main.c
 * Minimal example application:
 * - Initializes USART2
 * - Performs a blocking echo loop (RX -> TX)
 * The driver API comes from UartDriver.h.
 */

#include "UART_Driver.h"

char key;

/* Retargets printf()/putchar() to UART TX for simple console output. */
int __io_putchar(int ch) {
    uart2_write(ch);
    return ch;
}

/* Application entry point. Initializes UART and echoes received bytes. */
int main(void){
    uart2rxtx_init();

    while(1){
        key = uart2_read();
        uart2_write(key);
    }

    return 0; /* never reached in embedded, but keeps compiler happy */
}
