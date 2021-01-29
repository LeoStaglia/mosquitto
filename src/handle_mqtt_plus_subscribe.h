//
// Created by luca on 10/27/18.
//

#include "mosquitto_broker_internal.h"

typedef struct topics_list{
    char* topic;
    struct topics_list *next;
}list_node;

int mqtt_plus_subscribe(char *topic, const char *subscriberId, int qos);

extern bool is_distributed_sub;

