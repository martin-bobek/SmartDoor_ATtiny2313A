#ifndef UTIL_H__
#define UTIL_H__

#include "iotiny2313a.h"
#include "stdint.h"

#define MSK(BIT)       (1u << BIT)
//pin11-b1
//pin 14-b2
//pin13-b3
//pin12-b4

#define HEARTBEAT_ON()  (PORTD_Bit4 = 1)
#define HEARTBEAT_OFF() (PORTD_Bit4 = 0)

#define BUTTON1B        MSK(0)
#define BUTTON2B        MSK(1)
#define BUTTON3B        MSK(2)    
#define BUTTON1D        MSK(6)

#define HEARTBEATPIN    MSK(4)
#endif