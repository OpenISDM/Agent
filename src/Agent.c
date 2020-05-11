/*
 Copyright (c) 2016 Academia Sinica, Institute of Information Science

 License:

      GPL 3.0 : The content of this file is subject to the terms and
      conditions defined in file 'COPYING.txt', which is part of this source
      code package.

 Project Name:

      BeDIS

 File Description:

      This file contains the programs executed by location beacons to
      support indoor poositioning and object tracking functions.

 File Name:

      Agent.c

 Version:

       1.0,  20200427

 Abstract:

      To Recieve the alert signal from LBeacon.

 Authors:

      Wayne Kang, biggkqq@gmail.com

*/

#include "Agent.h"
#include "zlog.h"

ErrorCode get_config(Config *config, char *file_name) {
    /* Return value is a struct containing all config information */
    int retry_times = 0;
    FILE *file = NULL;
    char config_message[CONFIG_BUFFER_SIZE];
    
    /* open the config files */
    retry_times = FILE_OPEN_RETRY;
    while(retry_times--){
        file = fopen(file_name, "r");

        if(NULL != file){
            break;
        }
    }

    if (NULL == file) {
        zlog_error(category_health_report,
                   "Error openning file");
        zlog_error(category_debug,
                   "Error openning file");
        return E_OPEN_FILE;
    }

    /* Keep reading each line and store into the config struct */

    /* item 1 */
    fetch_next_string(file, config_message, sizeof(config_message)); 
    config -> agent_port = atoi(config_message);
    
    /* item 2 */
    fetch_next_string(file, config_message, sizeof(config_message)); 
    config -> light_controller_port = atoi(config_message);
    
    fclose(file);

    return WORK_SUCCESSFULLY;
}

ErrorCode Wifi_init(){
    /* Initialize the Wifi cinfig file */
    if(udp_initial(&udp_config, g_config.agent_port)
                   != WORK_SUCCESSFULLY){
        /* Error handling TODO */
        return E_WIFI_INIT_FAIL;
    }
    return WORK_SUCCESSFULLY;
}

void Wifi_free(){

    /* Release the Wifi elements and close the connection. */
    udp_release( &udp_config);
    return (void)NULL; 
}

int main(int argc, char **argv) {
    ErrorCode return_value = WORK_SUCCESSFULLY;
    ErrorCode config_value = get_config(&g_config, CONFIG_FILE_NAME);
    return_value = Wifi_init();
    if(return_value == WORK_SUCCESSFULLY){
      while(true){
        sPkt recv_queue = udp_getrecv(&udp_config);
        
        if(strlen(recv_queue. content)) {
          udp_addpkt_without_encoding(&udp_config, "127.0.0.1", g_config.light_controller_port, recv_queue.content, strlen(recv_queue.content));
        }else{
          sleep_t(NORMAL_WAITING_TIME_IN_MS);
        }
      }
    }else{
      printf("Wrong!!\n");
    }
    
}

