#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdio.h>
#include <glib-object.h>
#include <lunaservice.h>
#include <luna-service2/lunaservice.h>
#include <pbnjson.h>
#include <wiringPi.h>
#include <unistd.h>
#include "../include/gpio_handle.h"
#include <pthread.h>

int gpio_init()
{
    LSError lserror;
    //LSHandle *handle;
    if(wiringPiSetup() == -1)
        return 1;
        
    //setup HOME LED
    pinMode(HOME_LED1, OUTPUT);
    
    return 0;
}

bool home_led1_on(LSHandle *sh, LSMessage *message, void *data)
{
    LSError lserror;
    JSchemaInfo schemaInfo;
    jvalue_ref parsed = {0}, value = {0}, led_request = {0};
    jvalue_ref jobj = {0}, jreturnValue = {0};
    const char *led_request_str = NULL;

    LSErrorInit(&lserror);

    // Initialize schema
    jschema_info_init (&schemaInfo, jschema_all(), NULL, NULL);

    // get message from LS2 and parsing to make object
    parsed = jdom_parse(j_cstr_to_buffer(LSMessageGetPayload(message)), DOMOPT_NOOPT, &schemaInfo);

    if (jis_null(parsed)) {
        j_release(&parsed);
        return true;
    }

    /**
     * JSON create test
     */
    jobj = jobject_create();
    if (jis_null(jobj)) {
        j_release(&jobj);
        return true;
    }

    if(wiringPiSetup() == -1)
        return 1;
        
    digitalWrite(HOME_LED1, HIGH);
    
    jreturnValue = jboolean_create(TRUE);
    jobject_set(jobj, j_cstr_to_buffer("returnValue"), jreturnValue);

    LSMessageReply(sh, message, jvalue_tostring_simple(jobj), &lserror);

    j_release(&parsed);

    return true;
}


bool home_led1_off(LSHandle *sh, LSMessage *message, void *data)
{
    LSError lserror;
    JSchemaInfo schemaInfo;
    jvalue_ref parsed = {0}, value = {0}, led_request = {0};
    jvalue_ref jobj = {0}, jreturnValue = {0};
    const char *led_request_str = NULL;

    LSErrorInit(&lserror);

    // Initialize schema
    jschema_info_init (&schemaInfo, jschema_all(), NULL, NULL);

    // get message from LS2 and parsing to make object
    parsed = jdom_parse(j_cstr_to_buffer(LSMessageGetPayload(message)), DOMOPT_NOOPT, &schemaInfo);

    if (jis_null(parsed)) {
        j_release(&parsed);
        return true;
    }

    /**
     * JSON create test
     */
    jobj = jobject_create();
    if (jis_null(jobj)) {
        j_release(&jobj);
        return true;
    }

    if(wiringPiSetup() == -1)
        return 1;
        
    digitalWrite(HOME_LED1, LOW);
    
    jreturnValue = jboolean_create(TRUE);
    jobject_set(jobj, j_cstr_to_buffer("returnValue"), jreturnValue);
        
    LSMessageReply(sh, message, jvalue_tostring_simple(jobj), &lserror);

    j_release(&parsed);

    return true;
}
