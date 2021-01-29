//
// Created by luca on 07/01/19.
//
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "handle_mqtt_plus_publish.h"
#include "http.h"
#include "handle_mqtt_plus_sys.h"

void mqtt_plus_sys_subscribe(char *topic, const char *subscriberId, int qos){
    printf("http_sys_subscribes\n");
    json_value *json_result = NULL;

    char* jsonString = "{\"subscriberId\" : \"%s\",\"topics\": [ {\"topic\" : \"%s\" , \"qos\" : %d }]}";
    char* json_payload = (char*)malloc((strlen(jsonString) + strlen(topic)+ strlen(subscriberId)+sizeof(qos))*sizeof(char));

    sprintf(json_payload, jsonString , subscriberId, topic, qos);
    json_result=http_request("on_sys_subscribe",json_payload);


    free(json_payload);
    return;
}