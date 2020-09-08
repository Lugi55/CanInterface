

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
#include "driverlib/gpio.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "stdbool.h"
#include "mqttHandler.h"

#define BUFFER_FAIL     0
#define BUFFER_SUCCESS  1
#define BUFFER_SIZE     32

typedef enum {
    FIFO_FAIL,
    FIFO_SUCCESS
}eFifoStatus_t;

typedef struct{
    bool Rx;
    bool Temp1;
    bool Temp2;
    bool Temp3;
}sTopic_t;

typedef struct{
  tCANMsgObject sCANMessage[BUFFER_SIZE];
  uint8_t read;
  uint8_t write;
}sFifo_t;






//Global Methods
void can_IntHandler(void);
void can_Init(uint32_t ui32SysClock);
void can_Phraser(tCANMsgObject sCANMessage);
void can_PrettyPrint(tCANMsgObject sCANMessage);
eFifoStatus_t can_FifoPush(tCANMsgObject sCANMessage);
eFifoStatus_t can_FifoPop(tCANMsgObject *sCANMessage);
void can_SetLedRed(bool s);
void can_SetLedGreen1(bool s);
void can_SetLedGreen2(bool s);
void can_Enable(void);
void can_Disable(void);





#endif /* CAN_H_ */
