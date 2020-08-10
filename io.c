//*****************************************************************************
//
// io.c - I/O routines for the enet_io example application.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "utils/ustdlib.h"

#include "driverlib/rom_map.h"

#include "io.h"
#include "drivers/pinout.h"
#include <drivers/CFAF128128B0145T.h>
#include "mqtt_handler.h"

//*****************************************************************************
//
// Hardware connection for the user LED.
//
//*****************************************************************************
#define LED_PORT_BASE GPIO_PORTN_BASE
#define LED_PIN GPIO_PIN_1

//*****************************************************************************
//
// The system clock speed.
//
//*****************************************************************************
extern uint32_t g_ui32SysClock;

char old_ip[16] = {0};
char old_topic[MAX_TOPIC_LENGTH] = {0};
char old_message[MAX_MESSAGE_LENGTH] = {0};

//*****************************************************************************
//
// Initialize the IO used in this demo
//
//*****************************************************************************
void io_init(uint32_t g_ui32SysClock) {
    old_ip[0] = 0;
    old_topic[0] = 0;
    old_message[0] = 0;
    PinoutSet(true, false);

    // Enable peripherals:
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);        // enable GPIO Port N (LED1, LED2)

    // Check if the peripheral access is enabled. (Wait for GPIOx module to become ready)
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) { }

    CFAF128128B0145T_init(2, g_ui32SysClock, 20000000);
}

//*****************************************************************************
//
// Display IP, latest topic and latest message.
//
//*****************************************************************************
void io_set_display(char* ip, char* topic, char* message) {
    //Show DHCP Address on LCD screen
    if (ip != NULL) {
        strcpy(old_ip, ip);
    }
    if (topic != NULL) {
        strcpy(old_topic, topic);
    }
    if (message != NULL) {
        strcpy(old_message, message);
    }
    CFAF128128B0145T_clear(CFAF128128B0145T_color_black);

    CFAF128128B0145T_text(10, 10, "DHCP Address: ", CFAF128128B0145T_color_cyan, CFAF128128B0145T_color_black, 1, 1);
    CFAF128128B0145T_text(10, 20, old_ip, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

    CFAF128128B0145T_text(10, 35, "Latest Topic: ", CFAF128128B0145T_color_cyan, CFAF128128B0145T_color_black, 1, 1);
    CFAF128128B0145T_text(10, 45, topic, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);

    CFAF128128B0145T_text(10, 60, "Latest Message: ", CFAF128128B0145T_color_cyan, CFAF128128B0145T_color_black, 1, 1);
    CFAF128128B0145T_text(10, 70, message, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
}
