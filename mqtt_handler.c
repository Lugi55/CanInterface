#include "mqtt_handler.h"
#include "io.h"

//-----------------------------------------------------------------------------------------------
//
// Initialising structs
//
//-----------------------------------------------------------------------------------------------
struct Mqtt_message* mqtt_msg;
struct Mqtt_handler mqtt_han = { 0, 0, false };
struct Mqtt_subscribe mqtt_sub = { 0, {0}, 0 };

//-----------------------------------------------------------------------------------------------
//
// Initialising MQTT connection
//
//-----------------------------------------------------------------------------------------------
err_t mqtt_init(uint8_t IP_0, uint8_t IP_1, uint8_t IP_2, uint8_t IP_3) {
    err_t err;
    // Checking if DHCP connection is ready
    if (!g_netcon_ready) {
        return ERR_CONN;
    }

    // Transform broker IP address
    struct ip_addr broker_ip;
    IP4_ADDR(&broker_ip, IP_0, IP_1, IP_2, IP_3);

    // Opening TCP connection and connecting to broker
    t_pcb = tcp_new();
    err = tcp_bind(t_pcb, IP_ADDR_ANY, 187);
    err = tcp_connect(t_pcb, &broker_ip, 1883, mqtt_connected_fn);

    if (err != ERR_OK)
        UARTprintf("ERROR: Could not open TCP connection.\n");
    else
        UARTprintf("Connecting TCP...\n");
    return err;
}

//-----------------------------------------------------------------------------------------------
//
// Disconnecting by sending a DISCONNECT to broker and terminating the TCP connection
//
//-----------------------------------------------------------------------------------------------
void mqtt_disconnect() {
    unsigned char buf[200];
    int buflen = sizeof(buf);
    int len;

    len = MQTTSerialize_disconnect(buf, buflen);

    mqtt_send_packet(buf, len);
    mqtt_terminate();
}

//-----------------------------------------------------------------------------------------------
//
// Sending MQTT packet over TCP
//
//-----------------------------------------------------------------------------------------------
static err_t mqtt_send_packet(unsigned char* buf, uint32_t buflen) {
    err_t err;
    int retries = 0;

    // Stop if there is no connection
    if (t_pcb == NULL) return ERR_CLSD;

    // Check if there is enough buffer space
    if (tcp_sndbuf(t_pcb)) {
        // Retry until enough space is available or max retries are exceeded
        do {
            err = tcp_write(t_pcb, buf, buflen, 1);
            retries++;
        } while (retries < MAX_SEND_RETRIES && err == ERR_MEM);
        err = tcp_output(t_pcb);
        return err;
    }

    return ERR_BUF;
}

//-----------------------------------------------------------------------------------------------
//
// Subscribing to given topic
//
//-----------------------------------------------------------------------------------------------
err_t mqtt_subscribe(char* topic) {
    err_t err;

    // Checking if CONNACK has been received
    if (mqtt_han.connack && t_pcb != NULL) {
        unsigned char buf[200];
        int buflen = sizeof(buf);
        int msglen;

        // Initialising MQTT SUBSCRIBE packet
        MQTTString topicString = MQTTString_initializer;
        topicString.cstring = topic;

        UARTprintf("Subscribing to %s.\n", topic);
        msglen = MQTTSerialize_subscribe(buf, buflen, 0, 1, 1, &topicString, &mqtt_han.qos);
        mqtt_send_packet(buf, msglen);

        err = 0;
    } else return -1;

    return err;
}

//-----------------------------------------------------------------------------------------------
//
// Closing connection
//
//-----------------------------------------------------------------------------------------------
static void mqtt_terminate()
{
    mqtt_han.connack = false;
    // Stop if there is no connection
    if (t_pcb == NULL) return;

    // Resetting all callbacks and closing connection
    tcp_recv(t_pcb, NULL);
    tcp_poll(t_pcb, NULL, 0);
    tcp_arg(t_pcb, NULL);
    tcp_close(t_pcb);
    t_pcb = NULL;
    UARTprintf("MQTT connection closed.\n");
}

//-----------------------------------------------------------------------------------------------
//
// AUFGABE
//
//-----------------------------------------------------------------------------------------------
err_t mqtt_unsubscribe(char* topic) {
    ////////////////////////////////////////
    // HIER DEN UNSUBSCRIBE CODE EINFÜGEN //
    ////////////////////////////////////////
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Callback functions
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Called after successful connection
//
//-----------------------------------------------------------------------------------------------
static err_t mqtt_connected_fn(void *arg, struct tcp_pcb *tpcb, err_t err) {
    unsigned char buf[200];
    uint32_t buflen = sizeof(buf);

    UARTprintf("TCP Connection established.\n");

    // Set TCP callback functions
    // Polling every 100ms
    tcp_poll(tpcb, mqtt_poll_fn, 2);
    tcp_recv(tpcb, mqtt_recved_fn);

    // Initialising new MQTT packet with paho
    MQTTPacket_connectData packet = MQTTPacket_connectData_initializer;
    packet.clientID.cstring = username;
    packet.password.cstring = password;
    packet.keepAliveInterval = KEEPALIVE;
    packet.cleansession = 1;

    UARTprintf("Connecting to broker...\n");

    // Generating MQTT message with paho and sending it
    uint32_t len = MQTTSerialize_connect(buf, buflen, &packet);
    err_t _err;
    _err = mqtt_send_packet(buf, len);

    return _err;
}

//-----------------------------------------------------------------------------------------------
//
// Polling and sending PINGREQ to broker after reaching KEEPALIVE limit
//
//-----------------------------------------------------------------------------------------------
static err_t mqtt_poll_fn(void* arg, struct tcp_pcb* tpcb) {
    // Check if max poll count has been exceeded
    if(mqtt_han.poll > KEEPALIVE) {
        unsigned char buf[200];
        uint32_t buflen = sizeof(buf);
        uint32_t len;

        // Sending PINGREQ to broker
        len = MQTTSerialize_pingreq(buf, buflen);
        mqtt_send_packet(buf, len);

        mqtt_han.poll = 0;
    }

    mqtt_han.poll++;
}

//-----------------------------------------------------------------------------------------------
//
// Callback after receiving a packet. Handling all types of MQTT messages
//
//-----------------------------------------------------------------------------------------------
static err_t mqtt_recved_fn(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err) {
    // Terminating connection if there is no payload -> indicating a disconnect
    if (p == NULL) {
        mqtt_terminate();
        return ERR_OK;
    }

    // Send TCP confirmation
    tcp_recved(tpcb, p->len);

    unsigned char buf[200];
    int buflen = sizeof(buf);
    int len = 0;

    unsigned char *payload = (unsigned char *) p->payload;
    uint32_t payloadlen = sizeof(payload);

    // Extracting message type from header
    uint8_t type = payload[0];

    // We only need the first 4 bits of the header, so let's bit shift a little
    type = type >> 4;

    switch (type) {
        case CONNACK:
            mqtt_han.connack = true;
            UARTprintf("CONNACK received\n");
            //mqtt_subscribe("sensor/temp");
            break;

        case PUBLISH:
            UARTprintf("PUBLISH received\n");

            unsigned char dup;
            int qos;
            unsigned char retained;
            unsigned short msgid;
            int payloadlen_in;
            unsigned char* payload_in;
            MQTTString receivedTopic;

            // Reading received packet
            MQTTDeserialize_publish(&dup, &qos, &retained, &msgid, &receivedTopic, &payload_in, &payloadlen_in, payload, payloadlen);

            // Copying relevant information, 0 needed for string termination after data
            payload_in[payloadlen_in] = 0;
            strcpy(mqtt_msg->message, (const char*)payload_in);

            strncpy(mqtt_msg->topic, receivedTopic.lenstring.data, receivedTopic.lenstring.len);
            mqtt_msg->topic[receivedTopic.lenstring.len] = 0;

            UARTprintf("Topic: %s\n", mqtt_msg->topic);
            UARTprintf("Message: %s\n", mqtt_msg->message);

            io_set_display(NULL, mqtt_msg->topic, mqtt_msg->message);

            if (mqtt_han.qos == 1) {
                // For QoS == 1 we need to send a PUBACK back
                len = MQTTSerialize_puback(buf, buflen, msgid);
                mqtt_send_packet(buf, len);
                UARTprintf("Sending PUBACK...\n");
            } else if (mqtt_han.qos == 2) {
                // For QoS == 2 we need to send a PUBREC back
                len = MQTTSerialize_ack(buf, buflen, PUBREC, dup, msgid);
                mqtt_send_packet(buf, len);
                UARTprintf("Sending PUBREC...\n");
            }
            break;

        case PUBACK:
            UARTprintf("PUBACK received.\n");
            break;

        case PUBREC:
            UARTprintf("PUBREC received.\n");
            break;

        case PUBREL:
            UARTprintf("PUBREL received.\n");
            if (mqtt_han.qos == 2) {
                len = MQTTSerialize_pubcomp(buf, buflen, msgid);
                mqtt_send_packet(buf, len);
                UARTprintf("Sending PUBCOMP...\n");
            }
            break;

        case PUBCOMP:
            UARTprintf("PUBCOMP received.\n");
            break;

        case SUBSCRIBE:
            UARTprintf("SUBSCRIBE received.\n");
            break;

        case SUBACK:
            UARTprintf("SUBACK received.\n");
            break;

        case UNSUBSCRIBE:
            UARTprintf("UNSUBSCRIBE received.\n");
            break;

        case UNSUBACK:
            UARTprintf("UNSUBACK received.\n");
            break;

        case PINGREQ:
            UARTprintf("PINGREQ received.\n");
            break;

        case PINGRESP:
            UARTprintf("PINGRESP received.\n");
            break;

        case DISCONNECT:
            UARTprintf("DISCONNECT received.\n");
            break;

        default:
            UARTprintf("Not a MQTT message.\n");
            break;
    }

    // Resetting TCP buffer
    pbuf_free(p);

    return ERR_OK;
}
