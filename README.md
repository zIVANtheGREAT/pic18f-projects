# PIC Projects

Bare-metal PIC microcontroller projects (MPLAB X / XC8, register-level C,
no libraries).

## Layout
Each project lives in its own folder under [`pic18f-projects/`](../pic18f-projects/), with its own
README covering hardware setup and how it works.

- [`pic18f-projects/led-walking ones-polling`](pic18f-projects/led-walking%20ones-polling) — Timer0-timed LED
  chaser on the PIC18F57Q84, timing handled by polling `TMR0IF` in the
  main loop
- [`pic18f-projects/led-walking ones-interrupt`](pic18f-projects/led-walkling%20ones-interrupt) — same project,
  rebuilt to use a Timer0 overflow interrupt (vectored ISR) instead of
  polling
