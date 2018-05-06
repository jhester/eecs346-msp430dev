#include <msp430.h>
#include <stdint.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;         // Stop watchdog timer
    
    P1DIR |= BIT0;                    // Set pin direction to output  
    P1OUT |= BIT0;                    // Set pin level to HIGH

    while(1) {
        // Delay and toggle pin
        __delay_cycles(100000);
        P1OUT ^= BIT0;
    }

    return 0;
}
