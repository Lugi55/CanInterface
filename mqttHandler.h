#ifndef MQTTHANDLER_H_
#define MQTTHANDLER_H_

#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "settings.h"

//-----------------------------------------------------------------------------------------------
//
// MQTT Paho includes
//
//-----------------------------------------------------------------------------------------------
#include "third_party/paho/MQTTPacket.h"
#include "third_party/paho/MQTTFormat.h"
#include "third_party/paho/MQTTSubscribe.h"

#include "utils/lwiplib.h"
#include "utils/uartstdio.h"
#include "driverlib/sysctl.h"

//-----------------------------------------------------------------------------------------------
//
// Max length values for buffers
//
//-----------------------------------------------------------------------------------------------
#define MAX_TOPIC_LENGTH    200
#define MAX_MESSAGE_LENGTH  200
#define MAX_PAYLOAD_LENGTH  200

//-----------------------------------------------------------------------------------------------
//
// Vars
//
//-----------------------------------------------------------------------------------------------
struct tcp_pcb* t_pcb;

//-----------------------------------------------------------------------------------------------
//
// Structs
//
//-----------------------------------------------------------------------------------------------
struct Mqtt_handler {
    int qos;
    int poll;
    bool connack;
};

struct Mqtt_subscribe {
    uint32_t id;
    char topic[MAX_TOPIC_LENGTH];
    int topiclen;
};

struct Mqtt_message {
    char topic[MAX_TOPIC_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
    int messagelen;
};

//-----------------------------------------------------------------------------------------------
//
// Signal for connection ready from main()
//
//-----------------------------------------------------------------------------------------------
extern volatile bool g_netcon_ready;

//-----------------------------------------------------------------------------------------------
//
// Prototypes
//
//-----------------------------------------------------------------------------------------------

static err_t mqtt_send_packet(unsigned char* buf, uint32_t buflen);
static void mqtt_terminate();

void mqtt_disconnect();
err_t mqtt_init(uint8_t IP_0, uint8_t IP_1, uint8_t IP_2, uint8_t IP_3);
err_t mqtt_subscribe(char* topic);
err_t mqtt_unsubscribe(char* topic);
err_t mqtt_publish(unsigned char *payload, int payloadlen,char *topic);
//-----------------------------------------------------------------------------------------------
// Callbacks
static err_t mqtt_connected_fn(void* arg, struct tcp_pcb* tpcb, err_t err);
static err_t mqtt_poll_fn(void* arg, struct tcp_pcb* tpcb);
static err_t mqtt_recved_fn(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err);

#endif
