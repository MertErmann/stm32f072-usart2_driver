# STM32F0 Minimal UART2 Driver

This repository contains a **register-level UART2 driver** for the STM32F072RBTx microcontroller (tested on NUCLEO-F072RB).  
It was implemented without relying on the STM32 HAL UART functions, to provide full control and understanding of the peripheral registers.

---

## 📌 Features
- Blocking UART2 TX/RX driver  
- Configurable system frequency and baud rate via `UARTConfig.h`  
- Modular structure:
  - `UART_Driver.c/.h` → driver implementation
  - `UARTConfig.h` → project-level settings (clocks, baud)
  - `main.c` → echo application example
- Based on STM32CubeIDE project structure

---

## 🛠 Hardware
- **Board**: NUCLEO-F072RB  
- **MCU**: STM32F072RBTx  
- **USART2 pins**:  
  - PA2 → USART2_TX  
  - PA3 → USART2_RX  

On NUCLEO boards, **USART2 (PA2/PA3) is internally connected to the ST-LINK Virtual COM Port (VCP)**.  
This means you only need to connect the board to your PC via USB — no external USB-UART adapter is required.  

On your PC, the COM port will appear as:  
- Windows: *STMicroelectronics STLink Virtual COM Port (COMx)*  
- Linux/Mac: `/dev/ttyACM0` or similar

---

## ⚙️ Build Instructions
1. Open the project in **STM32CubeIDE**.
2. Clone this repository and import as an existing project.
3. Ensure your board is set to **STM32F072RBTx (NUCLEO-F072RB)**.
4. Flash the firmware to your NUCLEO board.
5. Open a serial terminal at **115200 baud, 8N1** on the ST-LINK Virtual COM Port.

---

## ▶️ Example
The included `main.c` demonstrates a simple **echo application**:  
Any byte received over USART2 is immediately transmitted back.

```c
int main(void){
    uart2rxtx_init();

    while(1){
        char key = uart2_read();
        uart2_write(key);  // echo received byte
    }
}
