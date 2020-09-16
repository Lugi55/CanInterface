/*
 * parser.c
 *
 *  Created on: 12.09.2020
 *      Author: Heimgartner
 */

#include "parser.h"

sFrames_t myFrames = {false,false,false,false,false,false,false,false,false,false,false,false};
s0x1E3_Frame_t s0x1E3_Frame;
s0x2E3_Frame_t s0x2E3_Frame;
s0x3E3_Frame_t s0x3E3_Frame;
s0x4E3_Frame_t s0x4E3_Frame;
sModule_t sModule1;
sModule_t sModule2;
sModule_t sModule3;
sModule_t sModule4;
sModule_t sModule5;
sModule_t sModule6;
sModule_t sModule7;


//////////////////////
//set Frames
//////////////////////
void parser_setFrames(sFrames_t sFrames){
    myFrames = sFrames;
    UARTprintf("CANRX:\t\t%d\n1E3:\t\t%d\n2E3:\t\t%d\n3E3:\t\t%d\n4E3:\t\t%d\nModule1:\t%d\nModule2:\t%d\nModule3:\t%d\nModule4:\t%d\nModule5:\t%d\nModule6:\t%d\nModule7:\t%d\n",
               myFrames.CANRX, myFrames._0x1E3_Frame, myFrames._0x2E3_Frame, myFrames._0x3E3_Frame, myFrames._0x4E3_Frame,
               myFrames._MMS_Module_1, myFrames._MMS_Module_2, myFrames._MMS_Module_3, myFrames._MMS_Module_4, myFrames._MMS_Module_5, myFrames._MMS_Module_6, myFrames._MMS_Module_7);
}

//////////////////////
//uint8_t to Float
//////////////////////
float byte2float(uint8_t x) {
    return x / 255.0e7;
}

//////////////////////
//init all Frames
//////////////////////
void parser_Init(){
    parser_Init1E3Frame();
    parser_Init2E3Frame();
    parser_Init3E3Frame();
    parser_Init4E3Frame();
    parser_InitModuleFrame(&sModule1, 1);
    parser_InitModuleFrame(&sModule2, 2);
    parser_InitModuleFrame(&sModule3, 3);
    parser_InitModuleFrame(&sModule4, 4);
    parser_InitModuleFrame(&sModule5, 5);
    parser_InitModuleFrame(&sModule6, 6);
    parser_InitModuleFrame(&sModule7, 7);
    UARTprintf("Init parser");
}

//////////////////////
//init 1e3 struct
//////////////////////
void parser_Init1E3Frame(){
    strcpy(s0x1E3_Frame.AEC_State.RELAY.topicString, "CAN/AEC/State/RELAY");
    s0x1E3_Frame.AEC_State.RELAY.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_State.Low_Voltage_Warning.topicString, "CAN/AEC/State/Low_Voltage_Warning");
    s0x1E3_Frame.AEC_State.Low_Voltage_Warning.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_State.High_Voltage_Warning.topicString, "CAN/AEC/State/High_Voltage_Warning");
    s0x1E3_Frame.AEC_State.High_Voltage_Warning.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_State.Open_Relay_Crash.topicString, "CAN/AEC/State/Open_Relay_Crash");
    s0x1E3_Frame.AEC_State.Open_Relay_Crash.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_State.Open_Relay_Error.topicString, "CAN/AEC/State/Open_Relay_Error");
    s0x1E3_Frame.AEC_State.Open_Relay_Error.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_SoC_pct.topicString, "CAN/AEC/SoC_pct");
    s0x1E3_Frame.AEC_SoC_pct.type = UINT;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_NO_ERROR.topicString, "CAN/AEC/Errors/ERR_NO_ERROR");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_NO_ERROR.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_SELFTEST.topicString, "CAN/AEC/Errors/ERR_SELFTEST");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_SELFTEST.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_CURRENT.topicString, "CAN/AEC/Errors/ERR_OVER_CURRENT");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_CURRENT.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_VOLTAGE.topicString, "CAN/AEC/Errors/ERR_OVER_VOLTAGE");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_VOLTAGE.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_UNDER_VOLTAGE.topicString, "CAN/AEC/Errors/ERR_UNDER_VOLTAGE");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_UNDER_VOLTAGE.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_DIGOVLD.topicString, "CAN/AEC/Errors/ERR_DIGOVLD");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_DIGOVLD.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_UNDER_TEMPERATURE.topicString, "CAN/AEC/Errors/ERR_OVER_UNDER_TEMPERATURE");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_UNDER_TEMPERATURE.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_PARAMINIT.topicString, "CAN/AEC/Errors/ERR_PARAMINIT");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_PARAMINIT.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_COMMUNICATION.topicString, "CAN/AEC/Errors/ERR_COMMUNICATION");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_COMMUNICATION.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_HVIL.topicString, "CAN/AEC/Errors/ERR_HVIL");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_HVIL.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Plus.topicString, "CAN/AEC/Errors/ERR_Contactor_Plus");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Plus.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Minus.topicString, "CAN/AEC/Errors/ERR_Contactor_Minus");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Minus.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Pre_Charge.topicString, "CAN/AEC/Errors/ERR_Contactor_Pre_Charge");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Pre_Charge.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_CELL_DELTA.topicString, "CAN/AEC/Errors/ERR_CELL_DELTA");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_CELL_DELTA.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_and_Module_Errors.ERR_Service.topicString, "CAN/AEC/Errors/ERR_Service");
    s0x1E3_Frame.AEC_and_Module_Errors.ERR_Service.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_NO_ERROR.topicString, "CAN/AEC/Warnings/ERR_NO_ERROR");
    s0x1E3_Frame.AEC_Warnings.ERR_NO_ERROR.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_SELFTEST.topicString, "CAN/AEC/Warnings/ERR_SELFTEST");
    s0x1E3_Frame.AEC_Warnings.ERR_SELFTEST.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_OVER_CURRENT.topicString, "CAN/AEC/Warnings/ERR_OVER_CURRENT");
    s0x1E3_Frame.AEC_Warnings.ERR_OVER_CURRENT.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_OVER_VOLTAGE.topicString, "CAN/AEC/Warnings/ERR_OVER_VOLTAGE");
    s0x1E3_Frame.AEC_Warnings.ERR_OVER_VOLTAGE.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_UNDER_VOLTAGE.topicString, "CAN/AEC/Warnings/ERR_UNDER_VOLTAGE");
    s0x1E3_Frame.AEC_Warnings.ERR_UNDER_VOLTAGE.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_DIGOVLD.topicString, "CAN/AEC/Warnings/ERR_DIGOVLD");
    s0x1E3_Frame.AEC_Warnings.ERR_DIGOVLD.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_OVER_UNDER_TEMPERATURE.topicString, "CAN/AEC/Warnings/ERR_OVER_UNDER_TEMPERATURE");
    s0x1E3_Frame.AEC_Warnings.ERR_OVER_UNDER_TEMPERATURE.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_PARAMINIT.topicString, "CAN/AEC/Warnings/ERR_PARAMINIT");
    s0x1E3_Frame.AEC_Warnings.ERR_PARAMINIT.type = BOOL;
    strcpy(s0x1E3_Frame.AEC_Warnings.ERR_COMMUNICATION.topicString, "CAN/AEC/Warnings/ERR_COMMUNICATION");
    s0x1E3_Frame.AEC_Warnings.ERR_COMMUNICATION.type = BOOL;
    strcpy(s0x1E3_Frame.Error_from_Node_ID.topicString,"CAN/AEC/Error_from_Node_ID");
    s0x1E3_Frame.Error_from_Node_ID.type = UINT;
    strcpy(s0x1E3_Frame.AEC_Voltage_V.topicString,"CAN/AEC/AEC_Voltage_V");
    s0x1E3_Frame.AEC_Voltage_V.type = UINT;
}

//////////////////////
//init 2e3 struct
//////////////////////
void parser_Init2E3Frame(){
    strcpy(s0x2E3_Frame.System_Maximum_String_Cell_Voltage_V.topicString,"CAN/AEC/System_Maximum_String_Cell_Voltage_V");
    s0x2E3_Frame.System_Maximum_String_Cell_Voltage_V.type = FLOAT;
    strcpy(s0x2E3_Frame.System_Minimum_String_Cell_Voltage_V.topicString,"CAN/AEC/System_Minimum_String_Cell_Voltage_V");
    s0x2E3_Frame.System_Minimum_String_Cell_Voltage_V.type = FLOAT;
    strcpy(s0x2E3_Frame.System_Heater_Status.topicString,"CAN/AEC/System_Heater_Status");
    s0x2E3_Frame.System_Heater_Status.type = BOOL;
    strcpy(s0x2E3_Frame.AEC_SoH_pct.topicString,"CAN/AEC/SoH_pct");
    s0x2E3_Frame.AEC_SoH_pct.type = UINT;
    strcpy(s0x2E3_Frame.Hottest_Module_Temperature_C.topicString,"CAN/AEC/Hottest_Module_Temperature_C");
    s0x2E3_Frame.Hottest_Module_Temperature_C.type = INT;
    strcpy(s0x2E3_Frame.Coldest_Module_Temperature_C.topicString,"CAN/AEC/Coldest_Module_Temperature_C");
    s0x2E3_Frame.Coldest_Module_Temperature_C.type = INT;
    strcpy(s0x2E3_Frame.AEC_SW_Version.topicString,"CAN/AEC/SW_Version");
    s0x2E3_Frame.AEC_SW_Version.type = UINT;
    strcpy(s0x2E3_Frame.AEC_Relays_Status.topicString,"CAN/AEC/Relays_Status");
    s0x2E3_Frame.AEC_Relays_Status.type = BOOL;
}


//////////////////////
//init 3e3 struct
//////////////////////
void parser_Init3E3Frame(){
    strcpy(s0x3E3_Frame.AEC_Remaining_Capacity_Amp.topicString,"CAN/AEC/Remaining_Capacity_Amp");
    s0x3E3_Frame.AEC_Remaining_Capacity_Amp.type = UINT;
    strcpy(s0x3E3_Frame.AEC_Time_Remaining_mins.topicString,"CAN/AEC/Time_Remaining_mins");
    s0x3E3_Frame.AEC_Time_Remaining_mins.type = UINT;
    strcpy(s0x3E3_Frame.AEC_Lifetime_Charged_kWh.topicString,"CAN/AEC/Lifetime_Charged_kWh");
    s0x3E3_Frame.AEC_Lifetime_Charged_kWh.type = UINT;
    strcpy(s0x3E3_Frame.ISO_Monitor_kOhm.topicString,"CAN/AEC/ISO_Monitor_kOhm");
    s0x3E3_Frame.ISO_Monitor_kOhm.type = UINT;
}

//////////////////////
//init 4e3 struct
//////////////////////
void parser_Init4E3Frame(){
    strcpy(s0x4E3_Frame.AEC_Permitted_Charge_Current_Amp.topicString,"CAN/AEC/Permitted_Charge_Current_Amp");
    s0x4E3_Frame.AEC_Permitted_Charge_Current_Amp.type = INT;
    strcpy(s0x4E3_Frame.AEC_Permitted_Discharge_Current_Amp.topicString,"CAN/AEC/Permitted_Discharge_Current_Amp");
    s0x4E3_Frame.AEC_Permitted_Discharge_Current_Amp.type = INT;
    strcpy(s0x4E3_Frame.AEC_Alive_Counter.topicString,"CAN/AEC/Alive_Counter");
    s0x4E3_Frame.AEC_Alive_Counter.type = UINT;
    strcpy(s0x4E3_Frame.AEC_Current_Amp.topicString,"CAN/AEC/Current_Amp");
    s0x4E3_Frame.AEC_Current_Amp.type = FLOAT;
}

//////////////////////
//init module
//////////////////////
void parser_InitModuleFrame(sModule_t *sModule, uint8_t number){
    char buffer[50];
    sprintf(buffer, "CAN/Module%d/Maximum_String_Cells_Voltage_V",number);
    strcpy(sModule->Module_Maximum_String_Cells_Voltage_V.topicString,buffer);
    sModule->Module_Maximum_String_Cells_Voltage_V.type = UINT;
    sprintf(buffer, "CAN/Module%d/Minimum_String_Cells_Voltage_V",number);
    strcpy(sModule->Module_Minimum_String_Cells_Voltage_V.topicString,buffer);
    sModule->Module_Minimum_String_Cells_Voltage_V.type = UINT;
    sprintf(buffer, "CAN/Module%d/Errors/ERR_NO_ERROR",number);
    strcpy(sModule->MMS_Errors.ERR_NO_ERROR.topicString,buffer);
    sModule->MMS_Errors.ERR_NO_ERROR.type = BOOL;
    sprintf(buffer, "CAN/Module%d/Errors/ERR_NO_ERROR",number);
    strcpy(sModule->MMS_Errors.ERR_CHIPSYS.topicString,buffer);
    sModule->MMS_Errors.ERR_CHIPSYS.type = BOOL;
    sprintf(buffer, "CAN/Module%d/Errors/ERR_OVER_CURRENT",number);
    strcpy(sModule->MMS_Errors.ERR_OVER_CURRENT.topicString,buffer);
    sModule->MMS_Errors.ERR_OVER_CURRENT.type = BOOL;
    sprintf(buffer, "CAN/Module%d/Errors/ERR_OVER_VOLTAGE",number);
    strcpy(sModule->MMS_Errors.ERR_OVER_VOLTAGE.topicString,buffer);
    sModule->MMS_Errors.ERR_OVER_VOLTAGE.type = BOOL;
    sprintf(buffer, "CAN/Module%d/Errors/ERR_UNDER_VOLTAGE",number);
    strcpy(sModule->MMS_Errors.ERR_UNDER_VOLTAGE.topicString,buffer);
    sModule->MMS_Errors.ERR_UNDER_VOLTAGE.type = BOOL;
    sprintf(buffer,"CAN/Module%d/Errors/ERR_OVER_UNDER_TEMPERATURE",number);
    strcpy(sModule->MMS_Errors.ERR_OVER_UNDER_TEMPERATURE.topicString,buffer);
    sModule->MMS_Errors.ERR_OVER_UNDER_TEMPERATURE.type = BOOL;
    sprintf(buffer,"CAN/Module%d/Errors/ERR_COMM_COMMON",number);
    strcpy(sModule->MMS_Errors.ERR_COMM_COMMON.topicString,buffer);
    sModule->MMS_Errors.ERR_COMM_COMMON.type = BOOL;
    sprintf(buffer,"CAN/Module%d/Heater_Status",number);
    strcpy(sModule->Module_Heater_Status.topicString,buffer);
    sModule->Module_Heater_Status.type = BOOL;
    sprintf(buffer,"CAN/Module%d/Maximum_Module_Temperature_C",number);
    strcpy(sModule->Maximum_Module_Temperature_C.topicString,buffer);
    sModule->Maximum_Module_Temperature_C.type = INT;
    sprintf(buffer,"CAN/Module%d/Minimum_Module_Temperature_C",number);
    strcpy(sModule->Minimum_Module_Temperature_C.topicString,buffer);
    sModule->Minimum_Module_Temperature_C.type = INT;
    sprintf(buffer,"CAN/Module%d/MMS_Voltage_mV",number);
    strcpy(sModule->MMS_Voltage_mV.topicString,buffer);
    sModule->MMS_Voltage_mV.type = UINT;
}

//////////////////////
//parse CanMsg
//////////////////////
void parser_parseCanMsg(tCANMsgObject sCANMessage){
    if(myFrames.CANRX){
        publisher_publishRX(sCANMessage);
    }
    switch(sCANMessage.ui32MsgID){
        case 0x1E3:
            if(myFrames._0x1E3_Frame){
                UARTprintf("1E3\n");
                parser_parse1E3(sCANMessage);
                publisher_publishTopicList((sTopic_t *)&s0x1E3_Frame,sizeof(s0x1E3_Frame)/sizeof(sTopic_t));
            }
            break;
        case 0x2E3:
            if(myFrames._0x2E3_Frame){
                UARTprintf("2E3\n");
                parser_parse2E3(sCANMessage);
                publisher_publishTopicList((sTopic_t *)&s0x2E3_Frame,sizeof(s0x2E3_Frame)/sizeof(sTopic_t));
            }
            break;
        case 0x3E3:
            if(myFrames._0x3E3_Frame){
                UARTprintf("3E3\n");
                parser_parse3E3(sCANMessage);
                publisher_publishTopicList((sTopic_t *)&s0x3E3_Frame,sizeof(s0x3E3_Frame)/sizeof(sTopic_t));
            }
            break;
        case 0x4E3:
            if(myFrames._0x4E3_Frame){
                UARTprintf("4E3\n");
                parser_parse4E3(sCANMessage);
                publisher_publishTopicList((sTopic_t *)&s0x4E3_Frame,sizeof(s0x4E3_Frame)/sizeof(sTopic_t));
            }
            break;
        case 0x181:
            if(myFrames._MMS_Module_1){
                UARTprintf("Module1\n");
                parser_parseModule(sCANMessage,&sModule1);
                publisher_publishTopicList((sTopic_t *)&sModule1,sizeof(sModule1)/sizeof(sTopic_t));
            }
            break;
        case 0x182:
            if(myFrames._MMS_Module_2){
                UARTprintf("Module2\n");
                parser_parseModule(sCANMessage,&sModule2);
                publisher_publishTopicList((sTopic_t *)&sModule2,sizeof(sModule2)/sizeof(sTopic_t));
            }
            break;
        case 0x183:
            if(myFrames._MMS_Module_3){
                UARTprintf("Module3\n");
                parser_parseModule(sCANMessage,&sModule3);
                publisher_publishTopicList((sTopic_t *)&sModule3,sizeof(sModule3)/sizeof(sTopic_t));
            }
            break;
        case 0x184:
            if(myFrames._MMS_Module_4){
                UARTprintf("Module4\n");
                parser_parseModule(sCANMessage,&sModule4);
                publisher_publishTopicList((sTopic_t *)&sModule4,sizeof(sModule4)/sizeof(sTopic_t));
            }
            break;
        case 0x185:
            if(myFrames._MMS_Module_5){
                UARTprintf("Module5\n");
                parser_parseModule(sCANMessage,&sModule5);
                publisher_publishTopicList((sTopic_t *)&sModule5,sizeof(sModule5)/sizeof(sTopic_t));
            }
            break;
        case 0x186:
            if(myFrames._MMS_Module_6){
                UARTprintf("Module6\n");
                parser_parseModule(sCANMessage,&sModule6);
                publisher_publishTopicList((sTopic_t *)&sModule6,sizeof(sModule6)/sizeof(sTopic_t));
            }
            break;
        case 0x187:
            if(myFrames._MMS_Module_7){
                UARTprintf("Module7\n");
                parser_parseModule(sCANMessage,&sModule7);
                publisher_publishTopicList((sTopic_t *)&sModule7,sizeof(sModule7)/sizeof(sTopic_t));
            }
            break;
        default:
            UARTprintf("unexpected CAN ID\n");
            can_SetLedRed(true);
            break;
    }
}

//////////////////////
//decode CAN MSG
//////////////////////
void parser_parse1E3(tCANMsgObject sCANMessage){
    union16_t myUnion16;
    (sCANMessage.pui8MsgData[0] & 0x01) ? (s0x1E3_Frame.AEC_State.RELAY.data.u = true) : (s0x1E3_Frame.AEC_State.RELAY.data.u = false);
    (sCANMessage.pui8MsgData[0] & 0x02) ? (s0x1E3_Frame.AEC_State.Low_Voltage_Warning.data.u = true) : (s0x1E3_Frame.AEC_State.Low_Voltage_Warning.data.u = false);
    (sCANMessage.pui8MsgData[0] & 0x03) ? (s0x1E3_Frame.AEC_State.High_Voltage_Warning.data.u = true) : (s0x1E3_Frame.AEC_State.High_Voltage_Warning.data.u = false);
    (sCANMessage.pui8MsgData[0] & 0x08) ? (s0x1E3_Frame.AEC_State.Open_Relay_Crash.data.u = true) : (s0x1E3_Frame.AEC_State.Open_Relay_Crash.data.u = false);
    (sCANMessage.pui8MsgData[0] & 0x40) ? (s0x1E3_Frame.AEC_State.Open_Relay_Error.data.u = true) : (s0x1E3_Frame.AEC_State.Open_Relay_Error.data.u = false);
    s0x1E3_Frame.AEC_SoC_pct.data.u = sCANMessage.pui8MsgData[1];
    (sCANMessage.pui8MsgData[2] == 0x00 && sCANMessage.pui8MsgData[3] == 0x00) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_NO_ERROR.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_NO_ERROR.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x01) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_SELFTEST.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_SELFTEST.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x02) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_CURRENT.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_CURRENT.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x04) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_VOLTAGE.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_VOLTAGE.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x08) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_UNDER_VOLTAGE.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_UNDER_VOLTAGE.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x10) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_DIGOVLD.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_DIGOVLD.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x20) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_UNDER_TEMPERATURE.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_OVER_UNDER_TEMPERATURE.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x40) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_PARAMINIT.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_PARAMINIT.data.u = false);
    (sCANMessage.pui8MsgData[2] & 0x80) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_COMMUNICATION.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_COMMUNICATION.data.u = false);
    (sCANMessage.pui8MsgData[1] & 0x01) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_HVIL.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_HVIL.data.u = false);
    (sCANMessage.pui8MsgData[3] & 0x02) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Plus.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Plus.data.u = false);
    (sCANMessage.pui8MsgData[3] & 0x04) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Minus.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Minus.data.u = false);
    (sCANMessage.pui8MsgData[3] & 0x08) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Pre_Charge.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Contactor_Pre_Charge.data.u = false);
    (sCANMessage.pui8MsgData[3] & 0x10) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_CELL_DELTA.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_CELL_DELTA.data.u = false);
    (sCANMessage.pui8MsgData[3] & 0x20) ? (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Service.data.u = true) : (s0x1E3_Frame.AEC_and_Module_Errors.ERR_Service.data.u = false);
    (sCANMessage.pui8MsgData[4] == 0x00) ? (s0x1E3_Frame.AEC_Warnings.ERR_NO_ERROR.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_NO_ERROR.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x01) ? (s0x1E3_Frame.AEC_Warnings.ERR_SELFTEST.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_SELFTEST.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x02) ? (s0x1E3_Frame.AEC_Warnings.ERR_OVER_CURRENT.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_OVER_CURRENT.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x04) ? (s0x1E3_Frame.AEC_Warnings.ERR_OVER_VOLTAGE.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_OVER_VOLTAGE.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x08) ? (s0x1E3_Frame.AEC_Warnings.ERR_UNDER_VOLTAGE.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_UNDER_VOLTAGE.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x10) ? (s0x1E3_Frame.AEC_Warnings.ERR_DIGOVLD.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_DIGOVLD.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x20) ? (s0x1E3_Frame.AEC_Warnings.ERR_OVER_UNDER_TEMPERATURE.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_OVER_UNDER_TEMPERATURE.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x40) ? (s0x1E3_Frame.AEC_Warnings.ERR_PARAMINIT.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_PARAMINIT.data.u = false);
    (sCANMessage.pui8MsgData[4] & 0x80) ? (s0x1E3_Frame.AEC_Warnings.ERR_COMMUNICATION.data.u = true) : (s0x1E3_Frame.AEC_Warnings.ERR_COMMUNICATION.data.u = false);
    s0x1E3_Frame.Error_from_Node_ID.data.u = sCANMessage.pui8MsgData[5];
    myUnion16.u8[0] = sCANMessage.pui8MsgData[6];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[7];
    s0x1E3_Frame.AEC_Voltage_V.data.u = (float) myUnion16.u16 * 0.25;
}

//////////////////////
//decode 2E3 Frame
//////////////////////
void parser_parse2E3(tCANMsgObject sCANMessage){
    s0x2E3_Frame.System_Maximum_String_Cell_Voltage_V.data.f = (float)sCANMessage.pui8MsgData[0]*0.02;
    s0x2E3_Frame.System_Minimum_String_Cell_Voltage_V.data.f = (float)sCANMessage.pui8MsgData[1]*0.02;
    (sCANMessage.pui8MsgData[2]) ? (s0x2E3_Frame.System_Heater_Status.data.b = true) : (s0x2E3_Frame.System_Heater_Status.data.b = false);
    s0x2E3_Frame.AEC_SoH_pct.data.u = sCANMessage.pui8MsgData[3];
    s0x2E3_Frame.Hottest_Module_Temperature_C.data.s = sCANMessage.pui8MsgData[4];
    s0x2E3_Frame.Coldest_Module_Temperature_C.data.s = sCANMessage.pui8MsgData[5];
    s0x2E3_Frame.AEC_SW_Version.data.u = sCANMessage.pui8MsgData[6];
    (sCANMessage.pui8MsgData[7] & 0x01) ? (s0x2E3_Frame.AEC_Relays_Status.data.u = true) : (s0x2E3_Frame.AEC_Relays_Status.data.u = false);
}

//////////////////////
//decode CAN MSG
//////////////////////
void parser_parse3E3(tCANMsgObject sCANMessage){
    union16_t myUnion16;
    myUnion16.u8[0] = sCANMessage.pui8MsgData[0];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[1];
    s0x3E3_Frame.AEC_Remaining_Capacity_Amp.data.f = (float)myUnion16.u16 * 0.1;
    myUnion16.u8[0] = sCANMessage.pui8MsgData[2];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[3];
    s0x3E3_Frame.AEC_Time_Remaining_mins.data.u = myUnion16.u16;
    myUnion16.u8[0] = sCANMessage.pui8MsgData[4];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[5];
    s0x3E3_Frame.AEC_Lifetime_Charged_kWh.data.u = myUnion16.u16;
    myUnion16.u8[0] = sCANMessage.pui8MsgData[6];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[7];
    s0x3E3_Frame.ISO_Monitor_kOhm.data.u = myUnion16.u16;
}

//////////////////////
//decode CAN MSG
//////////////////////
void parser_parse4E3(tCANMsgObject sCANMessage){
    union16_t myUnion16;
    myUnion16.u8[0] = sCANMessage.pui8MsgData[0];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[1];
    s0x4E3_Frame.AEC_Permitted_Charge_Current_Amp.data.s = myUnion16.s16;
    myUnion16.u8[0] = sCANMessage.pui8MsgData[2];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[3];
    s0x4E3_Frame.AEC_Permitted_Discharge_Current_Amp.data.s = myUnion16.s16;
    s0x4E3_Frame.AEC_Alive_Counter.data.u = sCANMessage.pui8MsgData[4];
    myUnion16.u8[0] = sCANMessage.pui8MsgData[5];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[6];
    s0x4E3_Frame.AEC_Current_Amp.data.f = (float)myUnion16.s16 * 0.25;
}

//////////////////////
//decode CAN MSG
//////////////////////
void parser_parseModule(tCANMsgObject sCANMessage, sModule_t *sModule){
    union16_t myUnion16;
    sModule->Module_Maximum_String_Cells_Voltage_V.data.f = 0.02*byte2float(sCANMessage.pui8MsgData[0]);
    sModule->Module_Minimum_String_Cells_Voltage_V.data.f = 0.02*byte2float(sCANMessage.pui8MsgData[1]);
    (sCANMessage.pui8MsgData[2] == 0x00) ? (sModule->MMS_Errors.ERR_NO_ERROR.data.b = true) : (sModule->MMS_Errors.ERR_NO_ERROR.data.b = false);
    (sCANMessage.pui8MsgData[2] & 0x01) ? (sModule->MMS_Errors.ERR_CHIPSYS.data.b = true) : (sModule->MMS_Errors.ERR_CHIPSYS.data.b = false);
    (sCANMessage.pui8MsgData[2] & 0x02) ? (sModule->MMS_Errors.ERR_OVER_CURRENT.data.b = true) : (sModule->MMS_Errors.ERR_OVER_CURRENT.data.b = false);
    (sCANMessage.pui8MsgData[2] & 0x04) ? (sModule->MMS_Errors.ERR_OVER_VOLTAGE.data.b = true) : (sModule->MMS_Errors.ERR_OVER_VOLTAGE.data.b = false);
    (sCANMessage.pui8MsgData[2] & 0x08) ? (sModule->MMS_Errors.ERR_UNDER_VOLTAGE.data.b = true) : (sModule->MMS_Errors.ERR_UNDER_VOLTAGE.data.b = false);
    (sCANMessage.pui8MsgData[2] & 0x20) ? (sModule->MMS_Errors.ERR_OVER_UNDER_TEMPERATURE.data.b = true) : (sModule->MMS_Errors.ERR_OVER_UNDER_TEMPERATURE.data.b = false);
    (sCANMessage.pui8MsgData[2] & 0x80) ? (sModule->MMS_Errors.ERR_COMM_COMMON.data.b = true) : (sModule->MMS_Errors.ERR_COMM_COMMON.data.b = true);
    (sCANMessage.pui8MsgData[3] == 0x01) ? (sModule->Module_Heater_Status.data.b = true) : (sModule->Module_Heater_Status.data.b = true);
    sModule->Maximum_Module_Temperature_C.data.s = sCANMessage.pui8MsgData[4];
    sModule->Minimum_Module_Temperature_C.data.s = sCANMessage.pui8MsgData[5];
    myUnion16.u8[0] = sCANMessage.pui8MsgData[6];
    myUnion16.u8[1] = sCANMessage.pui8MsgData[7];
    sModule->MMS_Voltage_mV.data.u = myUnion16.u16;
}









