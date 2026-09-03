# LED Chaser — Timer0 (Polled)

Bare-metal "Knight Rider" style LED chaser on the PIC18F57Q84 (MPLAB X / XC8),
timed with Timer0 and polled from the main loop.

## Hardware
- PIC18F57Q84 @ 64 MHz (Fosc)
- 8 LEDs on PORTD (LATD)
- Push button on RA3 (weak pull-up enabled), used to invert the displayed
  LED pattern while held

## How it works
- Timer0 configured for 16-bit mode, clock source Fosc/4, prescaler 1:16
  → 1 MHz timer clock → 1 µs/count
- Preload value `0xFC18` gives a 1000-count (1 ms) period
- `TMR0IF` is polled in `main()`'s `while(1)` loop (no interrupts) — on
  each overflow the flag is cleared, the timer is reloaded, and a software
  millisecond counter (`msTicks`) is incremented
- Every 5 ms, the LED shifts one position and bounces direction at each end
  (0x01 ↔ 0x80), with the displayed pattern inverted while RA3 reads low

## Notes
- This version uses polling rather than an interrupt — see
  [`led-chaser-interrupt`](../led-chaser-interrupt) for the interrupt-driven
  version of the same project, along with a Timer0 overflow ISR on the
  Q84's vectored interrupt controller.
