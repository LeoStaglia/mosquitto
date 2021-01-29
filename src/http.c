#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <curl/curl.h>
#include <mosquitto.h>

#include "json.h"
#include "http.h"
#include "mosquitto_broker_internal.h"

#define WS_ADDRESS "localhost/"
#define WS_PORT 8080

char* webserver_port;

struct MemoryStruct {
    char *memory;
    size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


int http_request(char* request_type,char* json_payload){

  CURL *curl;
  CURLcode res;
  struct MemoryStruct data;
  struct curl_slist *headers =NULL;
  char* mosquitto_string = "mosquitto: %s";
  char* mosquitto_header = (char*)malloc(strlen(mosquitto_string)+strlen(request_type)*sizeof(char));

  data.memory = malloc(1);
  data.size = 0;

  printf("Json payload %s\n", json_payload );
  printf("Porta HTTP: %s\n", webserver_port);

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if(curl){
    curl_easy_setopt(curl,CURLOPT_URL,WS_ADDRESS);
    curl_easy_setopt(curl,CURLOPT_PORT, atoi(webserver_port));
    curl_easy_setopt(curl,CURLOPT_POST,1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);

    sprintf(mosquitto_header,mosquitto_string,request_type);

    printf("request typr %s\n", mosquitto_header );

    headers = curl_slist_append(headers, mosquitto_header);
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
  }


  res = curl_easy_perform(curl);
  printf("HTTP request sent, res code: %d\n",res);


  log__printf(NULL, MOSQ_LOG_INFO, "Payload: %s, Request result: %d, Port: %s", json_payload, res, webserver_port);

  int value;

  if(res == CURLE_OK){
    long response_code;
    char* ct;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE,&ct);
    if (response_code== 200) {
      value = res;
    }
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();
  free(mosquitto_header);
  return value;
}
