#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdio.h>
#include <glib-object.h>
#include <lunaservice.h>
#include <luna-service2/lunaservice.h>
#include <pbnjson.h>

// control the webOS smarthome in connected car with gpio pin
#define HOME_LED1 2

int gpio_init();
bool home_led1_on(LSHandle *sh, LSMessage *message, void *data);
bool home_led1_off(LSHandle *sh, LSMessage *message, void *data);
