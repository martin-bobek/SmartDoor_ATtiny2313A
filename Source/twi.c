#include "util.h"

#define TINY_ADDRESS            0xA5

typedef enum { ADDRESS, ACK, DONE } state_t;

#pragma vector=USI_START_vect
__interrupt void TwiStart_Handler(void);
#pragma vector=USI_OVERFLOW_vect
__interrupt void TwiOverflow_Handler(void);

static state_t state;

#pragma vector=USI_START_vect
__interrupt void TwiStart_Handler(void) {
  DDRB_Bit5 = 0;                                        // makes sure driver for SDA is off
  state = ADDRESS;
  USICR =  MSK(USISIE) | MSK(USIOIE) | MSK(USIWM1) | /*MSK(USIWM0) |*/ MSK(USICS1);         // enables overflow interrupt and SCL hold after overflow interrupt.
  USISR = MSK(USISIF) | MSK(USIOIF);                    // clears the start flag, releasing SCL, and overflow flag, just in case before enabling overflow interrupt. Clears the timer.
}

#pragma vector=USI_OVERFLOW_vect
__interrupt void TwiOverflow_Handler(void) {
  switch (state) {
  case ADDRESS: {
    if (USIDR != TINY_ADDRESS)
      break;
    uint8_t num = 0;
    while(PINB_Bit7)
      if (++num > 10)
        break;
    PORTB_Bit5 = 0;                     // SDA will go low when enabled
    DDRB_Bit5 = 1;                      // turns on driver for SDA, pulling it low
    USISR = MSK(USIOIF) | 0xE;          // clears overflow flag, releasing SCL, and sets counter to 14, so it overflows after the ack pulse // MODIFIED TO CLEAR START CONDITION
    state = ACK;
    return;
  }
  case ACK:
    USIDR = G_Status;                   // places the status bits in the Data register, waiting to be shifted out.
    PORTB_Bit5 = 1;                     // hands control of SDA to MSB of the shift register
    USISR = MSK(USIOIF);                // clears the timer and clears the overflow flag, releasing SCL
    USICR = MSK(USISIE) | MSK(USIOIE) | MSK(USIWM1) | MSK(USICS1);
    state = DONE;
    return;
  case DONE:
    DDRB_Bit5 = 0;                      // turns off the driver for SDA
    break;
  }
  
  USISR = MSK(USIOIF);                  //  clears the timer and clears the overflow flag, releasing SCL
  USICR = MSK(USISIE) | MSK(USIWM1) | MSK(USICS1);  // resets USI to initial state, with overflow interrupt and SCL hold after overflow off
}
