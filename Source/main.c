#include "util.h"
#include "buttons.h"
<<<<<<< HEAD
#include "IR.h"
#include "Outputs.h"
=======

uint8_t G_Status;
>>>>>>> 8e7c6cd3c930cec5d5344a5e4249ed6809862b67

#pragma vector=TIMER0_COMPA_vect
__interrupt void SysTick_Handler(void);
#pragma vector=TIMER1_COMPA_vect
__interrupt void IRTick_Handler(void);
#pragma inline=forced
static void SystemInit(void);
#pragma inline=forced
static void SystemSleep(void);

<<<<<<< HEAD
static uint8_t G_SysTick=0;
static uint8_t G_ExpectSysTick=0;
static uint16_t G_IRTick=0;
static uint8_t G_Sensors = 0;
static uint8_t G_Buttons = 0;
=======
static volatile uint8_t G_SysTick;
static uint8_t G_ExpectSysTick;
>>>>>>> 8e7c6cd3c930cec5d5344a5e4249ed6809862b67

__C_task void main(void) {  
  SystemInit();
  
  while(1) {
    
    HEARTBEAT_ON();

    G_Buttons = ButtonService();
    G_Sensors = IRService();
    
    OutputService(G_Buttons, G_Sensors);
    
    HEARTBEAT_OFF();
    SystemSleep();
  }
  
}

//output to mega: 19/17
#pragma vector=TIMER0_COMPA_vect
<<<<<<< HEAD
__interrupt void SysTick_Handler() {

  G_SysTick++;
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void IRTick_Handler() {
  
  G_IRTick++;
  if(G_IRTick == 999) {
    TCCR1A ^= (MSK(COM1A1) | MSK(COM1B1) | MSK(COM1A0) | MSK(COM1B0));
    if(TCCR1A == 0x0) {
      PORTB_Bit3 = 0;
      PORTB_Bit4 = 0;
    }
    G_IRTick=0;
  }
}

=======
__interrupt void SysTick_Handler(void) {
  G_SysTick++;
}

>>>>>>> 8e7c6cd3c930cec5d5344a5e4249ed6809862b67
static void SystemInit() {
  DDRD = HEARTBEATPIN;
  MCUCR = MSK(SE);                      //enable sleep mode
<<<<<<< HEAD
  TCCR0A = MSK(WGM01);                  //set mode to CTC, top as OCR0A
  OCR0A = 0x7c;                         //set top as 124 
  TIMSK = MSK(OCIE0A) | MSK(ICIE1);                  //enables compare interrupt
  TCCR0B = MSK(CS01) | MSK(CS00);       //divide CLK I/O by 64

  
  TCCR1A = MSK(COM1A1) | MSK(COM1B1) | MSK(COM1A0) | MSK(COM1B0); // set OC1A and OC1B on compare match, toggle when top
  DDRB = MSK(DDB3) | (DDB4) | MSK(DDB5);// enable output driver for OC1A and OC1B, and output SDA
  TCCR1B = MSK(WGM13) | MSK(WGM12) | MSK(CS10); //set mode to CTC, ICR1 as top, no prescale
  ICR1 = 0x34;                          //set top as 52
  
  USICR = MSK(USIWM1) | MSK(USICS1) | MSK(USICS0);//two-wire mode, with external clock on negative edge
        
=======
  
  USISR = MSK(USISIF) | MSK(USIOIF);    // clears interrupts before turning on USI and enabling interrupts and clears counter
  USICR = MSK(USISIE) | MSK(USIWM1) | MSK(USICS1);        // turns on usi in twi mode
  PORTB = TWISCL_B;                     // when USI is enabled and output driver is enabled, the pin is driven open collector (low when port is 0)
  DDRB = TWISCL_B;                      // enables output driver on SCL pin

  TCCR0A = MSK(WGM01);                  //
  OCR0A = 0x7c;                         //compare pin for 
  TIMSK = MSK(OCIE0A);
  TCCR0B = MSK(CS01) | MSK(CS00);
>>>>>>> 8e7c6cd3c930cec5d5344a5e4249ed6809862b67
  
  asm("SEI");
}

static void SystemSleep() {
  
  if(G_SysTick != G_ExpectSysTick) {
    asm("CLI");
    while(1);
  }
  
  while(G_SysTick == G_ExpectSysTick) {
    asm("SLEEP");
  }
  
  G_ExpectSysTick++;
}