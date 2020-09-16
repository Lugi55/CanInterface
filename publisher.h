/*
 * publisher.h
 *
 *  Created on: 16.09.2020
 *      Author: Heimgartner
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <driverlib/can.h>
#include <parser.h>
#include <datatypes.h>



void publisher_publishTopicList(sTopic_t *psTopic,uint16_t len);
void publisher_publishRX(tCANMsgObject sCANMessage);


#endif /* PUBLISHER_H_ */
