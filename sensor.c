
#include "sensor.h"



void sensor_canInit(uint32_t ui32SysClock){
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
    CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
    CANEnable(CAN0_BASE);
}

void sensor_canDisable(){
    CANDisable(CAN0_BASE);
}

void sensor_canEnable(){
    CANEnable(CAN0_BASE);

}

void sensor_canWrite(){
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;

    pui8MsgData = (uint8_t *)&ui32MsgData;

    ui32MsgData = 0;
    sCANMessage.ui32MsgID = 1;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;
    UARTprintf("Sending msg: 0x%02X %02X %02X %02X", pui8MsgData[0], pui8MsgData[1], pui8MsgData[2], pui8MsgData[3]);
    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
}

void sensor_canEnableRx(){

}
