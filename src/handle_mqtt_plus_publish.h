//
// Created by luca on 10/28/18.
//

#include <stdbool.h>

typedef struct list_node{
    const char *topic;
    char *payload;
    struct list_node *next;
}publish_list;


void mqtt_plus_publish(char* topic,const char *clientId,int qos, void* payload,long payloadlen);

extern bool is_distributed_pub;

