#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdio.h>
#include <glib-object.h>
#include <lunaservice.h>
#include <luna-service2/lunaservice.h>
#include <pbnjson.h>
#include <pthread.h>
#include "../include/gpio_handle.h"

// 서비스 이름
#define SERVICE_NAME "com.app.rora.service.smarthome"

// Main loop for aliving background service
GMainLoop *gmainLoop;

LSHandle  *sh = NULL;
LSMessage *message;

// com.app.rora.service.smarthome 서비스 메소드 배열
LSMethod servicemethods[] = {
    {"home_led1_on", home_led1_on},
    {"home_led1_off", home_led1_off},
};

// 백그라운드 서비스 등록 및 초기화
int main(int argc, char* argv[])
{
    LSError lserror;
    LSHandle  *handle = NULL;
    bool bRetVal = FALSE;
    pthread_t threadId;

    LSErrorInit(&lserror);

    // GMainLoop 생성
    gmainLoop = g_main_loop_new(NULL, FALSE);

    bRetVal = LSRegister(SERVICE_NAME, &handle, &lserror);
    if (FALSE== bRetVal) {
        LSErrorFree( &lserror );
        return 0;
    }
    sh = LSMessageGetConnection(message);

    LSRegisterCategory(handle,"/",servicemethods, NULL, NULL, &lserror);
    LSGmainAttach(handle, gmainLoop, &lserror);

    gpio_init();    // gpio 초기화

    g_main_loop_run(gmainLoop);
    g_main_loop_unref(gmainLoop);

    return 0;
}