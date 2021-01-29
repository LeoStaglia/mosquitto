//
// Created by luca on 17/12/18.
//

#include "handle_mqtt_plus_unsubscribe.h"
#include <malloc.h>
#include <string.h>
#include "json.h"
#include "http.h"

int mqtt_plus_unsubscribe(char *topic, const char *subscriberId){
    printf("mqtt_plus_unsubscribe\n");
    printf("Topic: %s , SubId: %s\n",topic,subscriberId);


    char* jsonString = "{\"subscriberId\" : \"%s\",\"topic\" : \"%s\" }";
    char* json_payload = (char*)malloc((strlen(jsonString) + strlen(topic)+ strlen(subscriberId))*sizeof(char));

    sprintf(json_payload, jsonString , subscriberId, topic);
    http_request("on_unsubscribe",json_payload);

    free(json_payload);
}
int mqtt_plus_disconnect(const char *subscriberId){
    printf("mqtt_plus_unsubscribe\n");
    printf("SubId: %s\n",subscriberId);


    char* jsonString = "{\"subscriberId\" : \"%s\" }";
    char* json_payload = (char*)malloc((strlen(jsonString) + strlen(subscriberId))*sizeof(char));

    sprintf(json_payload, jsonString , subscriberId);
    http_request("on_disconnect",json_payload);

    free(json_payload);
}
