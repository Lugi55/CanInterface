
#include <can.h>

//////////////////////
//Modul variables
//////////////////////
uint8_t pui8MsgData[8];
tCANMsgObject sCANMessage;
sTopic_t myTopic = {.Rx=false,.Temp1=false,.Temp2=false,.Temp3=false};
sFifo_t myFifo = {.read=0,.write=0};
char stingBuffer[100];
volatile bool g_bRXFlag = 0;
volatile bool g_bErrFlag = 0;

//////////////////////
//Init Can Pheripherel
//////////////////////
void can_Init(uint32_t ui32SysClock){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_0);
    GPIOPinConfigure(GPIO_PA0_CAN0RX);
    GPIOPinConfigure(GPIO_PA1_CAN0TX);
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
    CANBitRateSet(CAN0_BASE, ui32SysClock, 250000);
    CANIntRegister(CAN0_BASE, can_IntHandler);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;
    sCANMessage.pui8MsgData = pui8MsgData;
    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);
    UARTprintf("canInit\n");
}

//////////////////////
//ISR for CAN
//////////////////////
void can_IntHandler(void){
    uint32_t ui32Status;
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
    if(ui32Status == CAN_INT_INTID_STATUS){
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
    }
    else if(ui32Status == 1){
        CANIntClear(CAN0_BASE, 1);
        CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);
        if(can_FifoPush(sCANMessage)==FIFO_FAIL){
            can_SetLedRed(true);
            UARTprintf("FIFO overflow\n");
        }
    }
    else{
        UARTprintf("Spurious interrupt\n");
    }
}


//////////////////////
//print CAN MSG UART
//////////////////////
void can_PrettyPrint(tCANMsgObject sCANMessage){
    if(sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST){
        UARTprintf("CAN message loss detected\n");
    }
    UARTprintf("Msg ID=0x%08X len=%u", sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen);
    UARTprintf(" data=0x %02X %02X %02X %02X", pui8MsgData[7], pui8MsgData[6], pui8MsgData[5], pui8MsgData[4]);
    UARTprintf(" %02X %02X %02X %02X\n", pui8MsgData[3], pui8MsgData[2], pui8MsgData[1], pui8MsgData[0]);
}


//////////////////////
//decode CAN MSG
//////////////////////
void canPhraser(tCANMsgObject sCANMessage){
    if(myTopic.Rx){
        //sprintf(buffer,"{\"ID\":\"0x%08X\", \"len\":%u, \"data\":\"0x %02X %02X %02X %02X %02X %02X %02X %02X\"}",
        //       sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen, pui8MsgData[7], pui8MsgData[6], pui8MsgData[5], pui8MsgData[4], pui8MsgData[3], pui8MsgData[2], pui8MsgData[1], pui8MsgData[0]);
        //mqtt_publish(buffer,strlen(buffer),"CAN/Rx");
    }
}

//////////////////////
//enable CAN
//////////////////////
void can_Enable(void){
    CANEnable(CAN0_BASE);
    UARTprintf("canEnable\n");
}

//////////////////////
//disable CAN
//////////////////////
void can_Disable(void){
    CANDisable(CAN0_BASE);
    UARTprintf("canDisable\n");
}


//////////////////////
//fifo push CAN MSG
//////////////////////
eFifoStatus_t can_FifoPush(tCANMsgObject sCANMessage){
  if ( ( myFifo.write + 1 == myFifo.read ) ||
       ( myFifo.read == 0 && myFifo.write + 1 == BUFFER_SIZE ) )
    return FIFO_FAIL; // voll

  myFifo.sCANMessage[myFifo.write] = sCANMessage;
  myFifo.write++;
  if (myFifo.write >= BUFFER_SIZE)
      myFifo.write = 0;
  return FIFO_SUCCESS;
}

//////////////////////
//fifo pop CAN MSG
//////////////////////
eFifoStatus_t can_FifoPop(tCANMsgObject *sCANMessage){
  if (myFifo.read == myFifo.write)
    return FIFO_FAIL;

  *sCANMessage = myFifo.sCANMessage[myFifo.read];
  myFifo.read++;
  if (myFifo.read >= BUFFER_SIZE)
    myFifo.read = 0;
  return FIFO_SUCCESS;
}

//////////////////////
//Set Red LED
//////////////////////
void can_SetLedGreen2(bool s){
    if(s==true){
        GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, GPIO_PIN_0);
    }
    else{
        GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, 0x0);
    }

}

//////////////////////
//Set Green LED1
//////////////////////
void can_SetLedRed(bool s){
    if(s==true){
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
    }
    else{
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x0);
    }

}

//////////////////////
//Set Green LED2
//////////////////////
void can_SetLedGreen1(bool s){
    if(s==true){
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
    }
    else{
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x0);
    }
}




