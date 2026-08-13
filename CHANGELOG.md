# Changelog

All notable changes to the **USART_D Library** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


---

## [1.1.0] - 2026-08-13

This is the **feature upgrade release** which focused on delivering non-blocking `RX` communication with a host.

Read the full technical breakdown [here](https://medium.com/@muazdawud307_31605/deep-dive-into-usart-d-a-high-performance-avr-communication-library-770d47e9cd9f).

### Added
- Added a new `USART_getCheck` function which handles the EOEvent of the `RX` communication.
- Fully non-blocking.

### Refactored
- Re-implemented internal logic for `USART_getString` to ensure a non-blocking, fully interrupt-driven USART Rx communication.

### Changed
- The main must first call the `USART_getCheck` to check if there is no ongoing USART `RX` communication, which is always true at the beginning of a session.
- `TIMER2` is automatically active (but) without a clock prescale at the first call of `USART_begin`.
- `TIMER2` clock prescaler is being set at the begining of the transmission to optimize function call latency.
- Non-Blocking operations usually come with a cost, for this, after getting back the array as and only as a string literal, you'll have to manually load the return buffer into the stack if you need to perform string operations.

---

## [1.0.0] - 2026-04-13

This is the **initial stable release** of the library, providing high-performance, bare-metal ISR-driven USART Communication for AVR-based systems.

### Added
- **Core USART Engine:** Implemented interrupt-driven transmission and reception for 8-bit AVR microcontrollers.
- **Architecture Abstraction (`reg_defs.h`):** Created a unified register mapping system supporting both "Modern" (ATmega328P/2560) and "Legacy" (ATmega8/16/32) architectures.
- **Circular Buffer System:** Implemented power-of-two circular buffers for transmission (`TX_BUFFER`) and reception (`RX_BUFFER`) to minimize data loss. Added high-performance TX and RX buffers using bitwise masking logic for zero-division pointer wrapping.
- **Formatted Printing:** Added `USART_print` function, a lightweight `printf` alternative, with support for format specifiers:
  - `%d`: Signed 16-bit integers.
  - `%s`: Null-terminated strings.
  - `%c`: Individual characters.
  - `%%`: Literal percent sign.
- **Robust String Reception (with Watchdog):** Added `USART_getString` featuring:
  - **Timer2 Integration:** Automatic input termination via hardware timer timeout (`150`-count threshold `~2.4s`) to prevent CPU blocking.
  - **Real-time Editing:** Basic support for Backspace (`\b`) and Delete (`127`) characters during reception.
  - **Termination Logic:** Automatic termination on Carriage Return (`\r`) or buffer overflow.
- **Utility Functions:**
  - `USART_begin()`: Automatic baud rate calculation using `<util/setbaud.h>`.
  - `USART_flush()`: Clears the hardware receive buffer and ensure data integrity at the start of new sessions..
  - `USART_getByte()`: Blocking single-byte reception with echo.
- **Hardware Compatibility:** Added support for the `URSEL` register-selection bit required for legacy AVR hardware.
- **Documentation:** Initial release of the comprehensive README and example implementation templates.
- **Licensing**: Project released under the MIT License.

### Changed
- **Performance Optimization:** Transitioned from polling-based transmission to `UDRE` (Data Register Empty) interrupt-driven transmission.
- **Memory Safety:** Applied `volatile` qualifiers to all shared state variables accessed within ISRs to prevent compiler optimization errors.

### Fixed
- **Null-Termination Logic:** Corrected a pointer decrement issue in the RX ISR to ensure safe C-string termination without buffer underflow.
- **Register Corruption:** Fixed potential collision between `TCCR2A` and `TCCR2B` on single-register legacy timers.
- **Deadlock Prevention:** Removed blocking function calls within ISRs to ensure system stability during high-traffic serial bursts.

### [Unreleased]
- **Planned**: Full Arduino Support.

---

### Optimized
- **Floating Point Removal:** Replaced floating-point math in `OCR2A` calculations with integer arithmetic to reduce Flash footprint.
- **CPU Efficiency:** Added automatic Timer2 shutdown (`TCCR2B = 0`) after string reception to conserve power and clock cycles.

---

**Note:** This is the initial stable release of the USART_D library.

*"Good and rigid answers are the foundation of stable systems."*