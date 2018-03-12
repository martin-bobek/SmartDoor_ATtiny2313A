#ifndef UTIL_H__
#define UTIL_H__

#include <iotiny2313a.h>
#include <stdint.h>

SFR_B(USIBR, 0x00)

#define MSK(BIT)       (1u << BIT)
#define HEARTBEAT_ON()  (PORTD_Bit4 = 1)
#define HEARTBEAT_OFF() (PORTD_Bit4 = 0)

//pin11-b1
//pin 14-b2
//pin13-b3
//pin12-b4

extern uint8_t G_Status;

#define BUTTON1_FLAG    MSK(0)
#define BUTTON2_FLAG    MSK(1)
#define BUTTON3_FLAG    MSK(2)
#define BUTTON4_FLAG    MSK(3)

// PORT B
#define BUTTON1B        MSK(0)
#define BUTTON2B        MSK(1)
#define BUTTON3B        MSK(2)
#define TWISDA_B        MSK(5)
#define TWISCL_B        MSK(7)

// PORT D
#define BUTTON1D        MSK(6)

#define HEARTBEATPIN    MSK(4)
#endif