# LED Chaser — Timer0 (Interrupt-Driven)

Interrupt-driven version of [`led-chaser-polling`](../led-chaser-polling),
rebuilt to move Timer0 overflow handling into a vectored ISR instead of
polling `TMR0IF` in the main loop.

## Hardware
- PIC18F57Q84 @ 64 MHz (Fosc)
- 8 LEDs on PORTD (LATD)
- Push button on RA3 (weak pull-up enabled), used to invert the displayed
  LED pattern while held

## How it works
- Timer0 configured the same as the polling version (16-bit mode, Fosc/4,
  1:16 prescale, `0xFC18` preload → 1 ms period)
- The PIC18F57Q84 uses a Vectored Interrupt Controller (VIC) rather than
  the classic PIC18 high/low priority vector scheme, so the ISR is
  declared with XC8's `__interrupt(irq(...))` syntax tied to the `IRQ_TMR0`
  vector
- `INTCON0.GIE` (global enable) and `PIE3.TMR0IE` (peripheral enable) are
  set in `Interrupt_init()`; `IPEN` is left at 0 since there's only one
  interrupt source in this project and no need for the priority scheme
- The ISR clears `TMR0IF`, reloads `TMR0H:TMR0L`, and increments `msTicks`
- `main()`'s loop only reads `msTicks` to time the 5 ms LED update — no
  flag-checking left in the loop

## Known gotcha (worth documenting)
`msTicks` and `lastUpdate` are both `uint16_t`. An earlier draft narrowed
both to `uint8_t` to make the read in `main()` atomic on this 8-bit core
(avoiding a torn read while the ISR is mid-increment). That introduced a
real bug: `msTicks - lastUpdate` still promotes to `int` (16-bit on this
target) before the subtraction happens, so the 8-bit wraparound trick the
comparison depends on doesn't actually apply — once `lastUpdate` landed
near the top of the 8-bit range, the true signed difference could never
reach the 5-tick threshold again, and the chase would freeze permanently
after a consistent number of cycles. Reverted to `uint16_t` for both
variables. A `uint8_t` version is still possible with an explicit cast —
`(uint8_t)(msTicks - lastUpdate) >= 5` — to force the subtraction back
down to 8-bit width, but wasn't pursued further here.

## Related
- [`led-chaser-polling`](../led-walking%20ones-polling) — the original polled version
