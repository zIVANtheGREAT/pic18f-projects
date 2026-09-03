# PIC Projects

Bare-metal PIC microcontroller projects (MPLAB X / XC8, register-level C,
no libraries).

## Layout
Each project lives in its own folder under [`pic/`](pic/), with its own
README covering hardware setup and how it works.

- [`pic/led-walking ones-polling`](pic/led-walking%20-polling) — Timer0-timed LED
  chaser on the PIC18F57Q84, timing handled by polling `TMR0IF` in the
  main loop
- [`pic/led-walking ones-interrupt`](pic/led-walking%20ones-interrupt) — same project,
  rebuilt to use a Timer0 overflow interrupt (vectored ISR) instead of
  polling
