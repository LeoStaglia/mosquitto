//
// Created by luca on 10/27/18.
//
#include <stdio.h>
#include <string.h>
#include "handle_mqtt_plus_subscribe.h"
#include "http.h"
#include "json.h"


int mqtt_plus_subscribe(char *topic, const char *subscriberId, int qos){
    printf("http_subscribes\n");
    int rc;

    char* jsonString = "{\"subscriberId\" : \"%s\",\"topics\": [ {\"topic\" : \"%s\" , \"qos\" : %d }]}";
    char* json_payload = (char*)malloc((strlen(jsonString) + strlen(topic)+ strlen(subscriberId)+sizeof(qos))*sizeof(char));

    sprintf(json_payload, jsonString , subscriberId, topic, qos);
    rc = http_request("on_subscribe",json_payload);

    /*json_value *topics = json_result->u.object.values[0].value;

    log__printf(NULL, MOSQ_LOG_INFO, "DENTRO PLUS SUB\n");

    int rc = topics->u.array.values[0]->u.object.values[0].value->u.integer;*/

    free(json_payload);
    return rc;

}