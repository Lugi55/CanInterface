/*
 * publisher.c
 *
 *  Created on: 16.09.2020
 *      Author: Heimgartner
 */

#include "publisher.h"

char buffer[20];

void publisher_publishTopicList(sTopic_t *psTopic,uint16_t len){
    int i;
    for(i=0;i<len;i++){
        switch(psTopic->type){
            case INT:
                sprintf(buffer,"%d",psTopic->data.s);
                mqtt_publish(buffer, strlen(buffer), psTopic->topicString);
                break;
            case UINT:
                sprintf(buffer,"%u",psTopic->data.u);
                mqtt_publish(buffer, strlen(buffer), psTopic->topicString);
                break;
            case FLOAT:
                sprintf(buffer,"%f",psTopic->data.f);
                mqtt_publish(buffer, strlen(buffer), psTopic->topicString);
                break;
            case BOOL:
                if(psTopic->data.b == true){
                    mqtt_publish("true", 4, psTopic->topicString);
                }
                break;
            default:
                UARTprintf("data type for publish not known\n");
                can_SetLedRed(true);
        }
        psTopic++;
    }


}

void publisher_publishRX(tCANMsgObject sCANMessage){
    char buffer[100];
    sprintf(buffer,"{\"ID\":\"0x%08X\", \"len\":%u, \"data\":\"0x %02X %02X %02X %02X %02X %02X %02X %02X\"}",
           sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen, sCANMessage.pui8MsgData[7], sCANMessage.pui8MsgData[6], sCANMessage.pui8MsgData[5], sCANMessage.pui8MsgData[4], sCANMessage.pui8MsgData[3], sCANMessage.pui8MsgData[2], sCANMessage.pui8MsgData[1], sCANMessage.pui8MsgData[0]);
    mqtt_publish(buffer,strlen(buffer),"CAN/Rx");
}


