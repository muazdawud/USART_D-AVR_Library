# USART_D Library

**USART_D** is a high-performance, interrupt-driven USART communication library specifically designed for 8-bit AVR micro-controllers. It offers efficient memory management through circular buffers and a flexible abstraction layer that supports both modern (e.g., ATmega328P) and legacy (e.g., ATmega8) AVR architectures. It provides a robust alternative to standard blocking I/O by utilizing circular buffers and background interrupt processing, allowing your application logic to remain responsive during heavy serial communication.

> *Check [Medium](https://medium.com/@muazdawud307_31605/deep-dive-into-usart-d-a-high-performance-avr-communication-library-770d47e9cd9f) platform for a more technical breakdown on how the library functions*
> *The Article doesn't include changes done after 01-08-2026.*

> *See `/examples` directory for comprehensive implementation templates.*

---

## Technical Deep Dive: How It Works

### 1. Non-Blocking Transmission (TX)
Unlike standard `putchar` functions that "spin-lock" (wait) until the hardware buffer is empty, **USART_D** uses a circular buffer. When you call a print function:
1. Data is pushed to the `tx_buf`.
2. The **UDRE** (Data Register Empty) interrupt is enabled.
3. The CPU immediately returns to your main code.
4. The ISR (Interrupt Service Routine) feeds the hardware `UDR` register one byte at a time whenever it is ready, disabling itself only when the buffer is exhausted.

### 2. Intelligent String Reception (RX)
`USART_getString()` implements a "Watchdog-style" timeout mechanism using **Timer2**. This is critical for bare-metal systems to prevent the CPU from hanging indefinitely if a sender stops transmitting mid-string.
* **Flow:** It flushes hardware noise, enables the **RXC** (Receive Complete) interrupt, and starts **Timer2**.
* **Termination:** The process ends if a Carriage Return (`\r`) is detected, the buffer limit is reached, or the timer exceeds the `~2.4s` inactivity threshold (`150` ticks at `16ms`).

### 3. Architecture Abstraction Layer (`reg_defs.h`)
The library solves the "Legacy vs. Modern" AVR problem. Older chips like the **ATmega8** share I/O addresses for the Baud Rate High (`UBRRH`) and Control (`UCSRC`) registers. **USART_D** automatically handles the `URSEL` register-selection bit and maps inconsistent bit names (e.g., `UCSZ0` vs `UCSZ00`) to a unified internal `API`.

---

## Features

* **Interrupt-Driven Transmission:** Non-blocking data transfer using the `UDRE` (Data Register Empty) interrupt. Which in turn maximize CPU cycles by handling I/O in the background.
* **Circular Buffering:** Efficient use of memory for `RX` and `TX` buffers to prevent data loss. And uses Bitwise masking (`& (BUFFER_SIZE - 1)`) for ultra-fast pointer wrapping (avoiding the division `/` function which is expensive on 8-bit microcontrollers).
* **Architecture Agnostic:** Uses `reg_defs.h` to abstract register names, making it compatible across various AVR MCUs. Uses single codebase for `ATmega8`, `16`, `32`, `168`, `328P`, `2560`, and more.
* **String Formatting:** Includes `USART_print`, a lightweight `printf`-like function supporting `%d`, `%s`, `%c`, and `%%` without the massive overhead of `stdio.h`.
* **Input Handling:** `USART_getString` includes built-in timeout support (via `Timer2`) and rigid backspace/delete handling.
* **Resource Efficient:** Optimized for bare-metal development with direct register manipulation.
* **Memory Safe:** Explicit bounds checking prevents buffer overflows and memory corruption.

---

## Hardware Support

The library dynamically detects your MCU architecture. Supported hardware includes:
* **Modern AVR:** `ATmega328P`, `ATmega168`, `ATmega2560`, etc.
* **Legacy AVR:** `ATmega8`, `ATmega16`, `ATmega32`, etc.

---

## File Structure

| File | Description |
| :--- | :--- |
| `USART_D.c` | Core implementation of USART initialization, interrupts, and I/O functions. |
| `USART_D.h` | Public API, configuration macros, and function prototypes. |
| `reg_defs.h` | Internal hardware abstraction layer for cross-MCU portability. |

---

## Configuration

Before compiling, ensure you define your *clock frequency* and desired *baud rate* in your project settings, makefile or header. Most `Makefiles` provide `F_CPU` automatically.

```c
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#include "USART_D.h"
#include <util/setbaud.h>
```

---

## Buffer Sizes
Default buffer sizes are defined in `USART_D.c`. You can adjust these based on your RAM constraints.
**Note**: *Sizes must be a power of 2 (e.g., 16, 32, 64, 128) to maintain bitwise masking efficiency.*

* **TX_BUFFER**: Default 32 bytes.
* **RX_BUFFER**: Default 64 bytes.

---

## Usage Examples
Initialization

```c
#include "USART_D.h"

int main(void) {
    USART_begin(); // Initializes Baud rate, RX/TX enables, and set global interrupts
    
    USART_print("USART_D System Online\r\n");
    
    while(1) {
        // Your logic
    }
}
```

---

## Printing Formatted Data
```c
int sensorValue = 1024;
char unit[] = "mV";
int16_t temperature = -15;
char status[] = "STABLE";

USART_print("Reading: %d %s\r\n", sensorValue, unit);

// Handles negative numbers and strings efficiently
USART_print("Temp: %d C | Status: %s\r\n", temperature, status);
```

---

## Secure String Input (with Timeout)
```c
USART_print("Enter Name: ");
const char* input = USART_getString();
USART_print("\r\nHello, %s!", input);
```

---

## License
Licensed under the **MIT License**.

Copyright (c) 2026 Dauda Muazu Sulaiman & [KibrisOrder](https://ss.kibrisorder.com).

See the LICENSE file for more details.

---

## Credits
**Author**: Dauda Muazu Sulaiman
**Organization**: KibrisOrder

Special thanks to **KibrisOrder** for supporting the development of high-performance embedded drivers.

Website: https://ss.kibrisorder.com

---

*"Good and rigid answers are the foundation of stable systems."*

*(I hope this will be useful to the public and the open source community)*