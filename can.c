
#include <can.h>




volatile bool g_bRXFlag = 0;
volatile bool g_bErrFlag = 0;

tCANMsgObject sCANMessage;
uint8_t pui8MsgData[8];
topic_t myTopic = {true,false,false,false};




void can_Init(uint32_t ui32SysClock){
    UARTprintf("canInit\n");
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_CAN0RX);
    GPIOPinConfigure(GPIO_PA1_CAN0TX);
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
    CANBitRateSet(CAN0_BASE, ui32SysClock, 250000);
    CANIntRegister(CAN0_BASE, can_IntHandler);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
    CANEnable(CAN0_BASE);
    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;
    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);
    sCANMessage.pui8MsgData = pui8MsgData;
}

void can_IntHandler(void){
    uint32_t ui32Status;
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
    if(ui32Status == CAN_INT_INTID_STATUS){
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
    }
    else if(ui32Status == 1){
        CANIntClear(CAN0_BASE, 1);
        CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);
        can_PrettyPrint();
        can_phraser();
    }
    else{
        UARTprintf("Spurious interrupt\n");
    }
}

static void can_PrettyPrint(){
    unsigned int uIdx;
    if(sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST){
        UARTprintf("CAN message loss detected\n");
    }
    UARTprintf("Msg ID=0x%08X len=%u data=0x %02X %02X %02X %02X %02X %02X %02X %02X\n", sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen, pui8MsgData[7], pui8MsgData[6], pui8MsgData[5], pui8MsgData[4], pui8MsgData[3], pui8MsgData[2], pui8MsgData[1], pui8MsgData[0]);
}

static void can_phraser(){
    char buffer[100];
    if(myTopic.Rx){
        sprintf(buffer,"{\"ID\":\"0x%08X\", \"len\":%u, \"data\":\"0x %02X %02X %02X %02X %02X %02X %02X %02X\"}",
                sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen, pui8MsgData[7], pui8MsgData[6], pui8MsgData[5], pui8MsgData[4], pui8MsgData[3], pui8MsgData[2], pui8MsgData[1], pui8MsgData[0]);
        mqtt_publish(buffer,strlen(buffer),"CAN/Rx");
    }
}





