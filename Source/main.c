#include "util.h"
#include "buttons.h"
#include "IR.h"

#pragma vector=TIMER0_COMPA_vect
__interrupt void SysTick_Handler(void);
#pragma inline=forced
static void SystemInit(void);
#pragma inline=forced
static void SystemSleep(void);

uint8_t G_Status;

static volatile uint8_t G_SysTick;
static uint8_t G_ExpectSysTick;

__C_task void main(void) {  
  SystemInit();
  
  while(1) {
    HEARTBEAT_ON();

    ButtonService();
    IRDrive();
    
    HEARTBEAT_OFF();
    SystemSleep();
  }
}

#pragma vector=TIMER0_COMPA_vect
__interrupt void SysTick_Handler() {

  G_SysTick++;
}

static void SystemInit() {
  CLKPR = MSK(CLKPCE);
  CLKPR = MSK(CLKPS0);
  
  MCUCR = MSK(SE);                      //enable sleep mode

  DDRD = HEARTBEAT_D | DEBUG_D;
  
  TCCR1A = 0; // set OC1A and OC1B on compare match, toggle when top
  TCCR1B = MSK(WGM13) | MSK(WGM12) | MSK(CS10); //set mode to CTC, ICR1 as top, no prescale
  ICR1 = 0x68;                          //set top as 104
  
  USISR = MSK(USISIF) | MSK(USIOIF);    // clears interrupts before turning on USI and enabling interrupts and clears counter
  USICR = MSK(USISIE) | MSK(USIWM1) | MSK(USICS1);        // turns on usi in twi mode
  PORTB = TWISCL_B;                     // when USI is enabled and output driver is enabled, the pin is driven open collector (low when port is 0)
  DDRB = TWISCL_B | IRLED1_B | IRLED2_B;// enable output driver for OC1A and OC1B;                      // enables output driver on SCL pin

  TCCR0A = MSK(WGM01);                  //set mode to CTC, top as OCR0A
  OCR0A = 0x7c;                         //set top as 124 
  TIMSK = MSK(OCIE0A);     //enables compare interrupt for TIM0&1
  TCCR0B = MSK(CS01) | MSK(CS00);       //divide CLK I/O by 64

  asm("SEI");
}

static void SystemSleep() {
  
  if(G_SysTick != G_ExpectSysTick) {
    PINB_Bit5 = 1;
  }
  
  while(G_SysTick == G_ExpectSysTick) {
    asm("SLEEP");
  }
  
  G_ExpectSysTick++;
}