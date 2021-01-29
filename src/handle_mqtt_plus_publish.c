//
// Created by luca on 10/28/18.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "handle_mqtt_plus_publish.h"
#include "http.h"

void mqtt_plus_publish(char* topic,const char *clientId,int qos, void* payload, long payloadlen){

    printf("mqtt_plus_publish\n");

    char* jsonString = "{\"clientId\" : \"%s\", \"topic\" : \"%s\" , \"qos\" : %d ,\"payload\" : \"%s\" }";
    char* json_payload = (char*)malloc((strlen(jsonString) + strlen(topic)+ strlen(clientId)+sizeof(qos)+payloadlen));

    printf("json_payload size: %d\n", payloadlen);
    printf("payload : %s",payload);

    sprintf(json_payload,jsonString,clientId,topic,qos,payload);

    printf("json_payload: %s\n",json_payload);

    http_request("on_publish",json_payload);

    free(json_payload);

}