/*
 * parser.h
 *
 *  Created on: 12.09.2020
 *      Author: Heimgartner
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <driverlib/can.h>
#include <can.h>
#include <publisher.h>
#include <datatypes.h>


void parser_Init(void);
void parser_Init1E3Frame(void);
void parser_Init2E3Frame(void);
void parser_Init3E3Frame(void);
void parser_Init4E3Frame(void);
void parser_InitModuleFrame(sModule_t *sModule, uint8_t number);
void parser_parseCanMsg(tCANMsgObject sCANMessage);
void parser_parseNode(tCANMsgObject sCANMessage);
void parser_setFrames(sFrames_t sFrames);
void parser_parse1E3(tCANMsgObject sCANMessage);
void parser_parse2E3(tCANMsgObject sCANMessage);
void parser_parse3E3(tCANMsgObject sCANMessage);
void parser_parse4E3(tCANMsgObject sCANMessage);
void parser_parseModule(tCANMsgObject sCANMessage, sModule_t *sModule);


#endif /* PARSER_H_ */
