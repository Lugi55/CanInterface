

#ifndef CAN_H_
#define CAN_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "drivers/pinout.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "stdbool.h"
#include "mqttHandler.h"


typedef struct{
    bool Rx;
    bool Temp1;
    bool Temp2;
    bool Temp3;
}topic_t;


static void can_phraser(void);
static void can_PrettyPrint(void);

void can_Init(uint32_t ui32SysClock);
void can_IntHandler(void);
void can_Receive(void);





#endif /* CAN_H_ */
