
#include <can.h>

volatile bool g_bErrFlag = 0;
tCANMsgObject sCANMessage;
uint8_t *pui8MsgData;


void can_Init(uint32_t ui32SysClock){
    UARTprintf("canInit\n");
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_CAN0RX);
    GPIOPinConfigure(GPIO_PA1_CAN0TX);
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
    CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
    CANIntRegister(CAN0_BASE, CANIntHandler);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
    CANEnable(CAN0_BASE);
}

void can_Disable(){
    CANDisable(CAN0_BASE);
}

void can_Enable(){
    CANEnable(CAN0_BASE);
}

void can_Write(uint64_t ui64MsgData, uint32_t ui32MsgID, uint32_t ui32MsgIDMask){
    pui8MsgData = (uint8_t *)&ui64MsgData;
    sCANMessage.ui32MsgID = ui32MsgID;
    sCANMessage.ui32MsgIDMask = ui32MsgIDMask;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;
    UARTprintf("Sending msg: 0x");
    uint8_t n = 0;
    for(n=0;n<sizeof(pui8MsgData);n++){
        UARTprintf("02X \n", pui8MsgData[n]);
    }
    UARTprintf("\n");
    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
    ui32MsgData++;
}


void CANIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        g_bErrFlag = 1;
        UARTprintf("CanHandler: Error have occured\n");
    }

    else if(ui32Status == 1)
    {
        CANIntClear(CAN0_BASE, 1);
        g_bErrFlag = 0;
        UARTprintf("CanHandler: No Error\n");
    }

    else
    {
        UARTprintf("unexpected interrupt\n")
    }

}

void sensor_canEnableRx(){

}
