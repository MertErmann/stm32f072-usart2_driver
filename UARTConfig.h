/* -----------------------------------------------------------
 * STM32F0 Minimal UART2 Driver (PA2=TX, PA3=RX)
 * Author: MERT ERMAN
 * ProjectConfig.h
 * Board/system-level settings intended to be edited by end users.
 * Put project-wide tunables here (clocks, default UART baud, timer PSC/ARR).
 * By isolating them in one header, the driver .c files can stay unchanged.
 */

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

/* ---------------- System Clocks ---------------- */
#define SYS_FREQ    8000000U
#define APB1_CLK    SYS_FREQ

/* ---------------- UART Defaults ---------------- */
#define UART_BAUD   115200U

#endif /* PROJECT_CONFIG_H */
