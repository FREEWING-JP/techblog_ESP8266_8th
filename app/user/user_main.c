/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_main.c
 *
 * Description: entry file of user application
 *
 * Modification history:
 *     2014/1/1, v1.0 create this file.
*******************************************************************************/
#include "ets_sys.h"
#include "osapi.h"

#include "user_interface.h"

#include "user_devicefind.h"
#include "user_webserver.h"

#if ESP_PLATFORM
#include "user_esp_platform.h"
#endif

void user_rf_pre_init(void)
{
}


/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
	uart_div_modify(0, UART_CLK_FREQ / 115200);
	
    os_printf("SDK version:%s\n", system_get_sdk_version());
	
	uint32 num = 0;

#if ESP_PLATFORM
    /*Initialization of the peripheral drivers*/
    /*For light demo , it is user_light_init();*/
    /* Also check whether assigned ip addr by the router.If so, connect to ESP-server  */
    //user_esp_platform_init();
#endif
    /*Establish a udp socket to receive local device detect info.*/
    /*Listen to the port 1025, as well as udp broadcast.
    /*If receive a string of device_find_request, it rely its IP address and MAC.*/
    //user_devicefind_init();

    /*Establish a TCP server for http(with JSON) POST or GET command to communicate with the device.*/
    /*You can find the command in "2B-SDK-Espressif IoT Demo.pdf" to see the details.*/
    /*the JSON command for curl is like:*/
    /*3 Channel mode: curl -X POST -H "Content-Type:application/json" -d "{\"period\":1000,\"rgb\":{\"red\":16000,\"green\":16000,\"blue\":16000}}" http://192.168.4.1/config?command=light      */
    /*5 Channel mode: curl -X POST -H "Content-Type:application/json" -d "{\"period\":1000,\"rgb\":{\"red\":16000,\"green\":16000,\"blue\":16000,\"cwhite\":3000,\"wwhite\",3000}}" http://192.168.4.1/config?command=light      */
	user_light_init();
	
    user_webserver_init(SERVER_PORT);

	pwm_set_duty(10000, 0);
	
	pwm_start();
	/*
		user_light_init();
	user_light_set_period(1000);
	user_light_restart();
	
	for(;;){
		num++;
		
		if(num >= 22222){
			num = 0;
		}
		
		user_light_set_duty(num, 0);
		pwm_start();
		
		os_delay_us(100);
	}
	*/
	
}

