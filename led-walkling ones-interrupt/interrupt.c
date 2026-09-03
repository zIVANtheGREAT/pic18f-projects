/*
 * File:   Interrupt.c
 * Author: Ivan C.
 *
 * Created on September 2, 2026, 2:15 PM
 */


#include <xc.h>

/*
 * DEFINES / MACROS
 */
#define _XTAL_FREQ 64000000

/*
 * Prototypes
 */
void timer0_init(void);
void PORT_init(void);
void Interrupt_init(void);

volatile uint16_t msTicks = 0;
uint8_t LED = 0x01;
int8_t direction = 1;
static uint16_t lastUpdate = 0;

void main(void) 
{
    timer0_init();
    PORT_init();
    Interrupt_init();
    
    while(1)
    {
        if ((msTicks - lastUpdate) >= 5)
        {
            
            lastUpdate = msTicks;
            
            //LATD = LED;
            
            //---------------
            //---Added Code--
            if (PORTAbits.RA3 == 0x00)
                LATD = (~LED) & 0xFF;
            else
                LATD = LED;
            //---------------
            
            if (direction == 1)
            {
                LED <<= 1;
                
                if (LED == 0x80)
                    direction = -1;
            }
            else
            {
                LED >>= 1;
                if (LED == 0x01)
                    direction = 1;
            }
        }
    }
    return;
}

//Functions
void timer0_init(void)
{
    T0CON0bits.T0EN = 1;
    T0CON0bits.T016BIT = 1;
    //bit 7 enabled
    //bit 4 set to 16 bit mode
    
    T0CON1bits.T0CS = 0b010;
    T0CON1bits.T0CKPS = 0b0100;
    //clock source Fosc/4
    //prescaler 1:16
    
    TMR0H = 0xFC;
    TMR0L = 0x18;
    
    PIR3bits.TMR0IF = 0;
}

void PORT_init(void)
{
    //preparing the weak pull up RA3
    TRISAbits.TRISA3   = 1; //pin RA3 is an input
    ANSELAbits.ANSELA3 = 0; //Allows for digital use.
    WPUAbits.WPUA3     = 1; //Enables weak pull-up
    
    //Initializing PORTD
    LATD   = 0xa0; //Output Latches low
    TRISD  = 0x00; //PORTD output mode
    ANSELD = 0x00; //PORTD digital mode
    
}

void Interrupt_init(void)
{
    INTCON0bits.GIE = 1;
    INTCON0bits.IPEN = 0;
    
    PIE3bits.TMR0IE = 1;
}

void __interrupt(irq(IRQ_TMR0)) TMR0_ISR(void)
{
    PIR3bits.TMR0IF = 0;
            
    TMR0H = 0xFC;
    TMR0L = 0x18;
    msTicks++;
}
