#ifndef UTIL_H__
#define UTIL_H__

#include <iotiny2313a.h>
#include <stdint.h>

SFR_B(USIBR, 0x00)

#define MSK(BIT)       (1u << BIT)
#define HEARTBEAT_ON()  (PORTD_Bit4 = 1)
#define HEARTBEAT_OFF() (PORTD_Bit4 = 0)
#define DEBUG_ON()      (PORTD_Bit5 = 1)
#define DEBUG_OFF()     (PORTD_Bit5 = 0)

extern uint8_t G_Status;

#define BUTTON1_FLAG    MSK(0)
#define BUTTON2_FLAG    MSK(1)
#define BUTTON3_FLAG    MSK(2)
#define BUTTON4_FLAG    MSK(3)
#define IR1_FLAG        MSK(4)
#define IR2_FLAG        MSK(5)
#define IR3_FLAG        MSK(6)
#define IR4_FLAG        MSK(7)

// PORT B
#define BUTTON1B        MSK(0)
#define BUTTON2B        MSK(1)
#define BUTTON3B        MSK(2)
#define IRLED1_B        MSK(3)
#define IRLED2_B        MSK(4)
#define TWISDA_B        MSK(5)
#define TWISCL_B        MSK(7)

// PORT D
#define SENSOR1_D       MSK(0)
#define SENSOR2_D       MSK(1)
#define SENSOR3_D       MSK(2)
#define SENSOR4_D       MSK(3)
#define HEARTBEAT_D     MSK(4)
#define DEBUG_D         MSK(5)
#define BUTTON1D        MSK(6)

#endif