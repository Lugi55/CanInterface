

#ifndef SENSOR_H_
#define SENSOR_H_

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

void sensor_canInit(uint32_t ui32SysClock);
void sensor_canDisable();
void senosr_canEnable();
void sensor_canWrite();



#endif /* SENSOR_H_ */
