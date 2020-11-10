/*
  2020 © Copyright (c) BiDaE Technology Inc. 
  Provided under BiDaE SHAREWARE LICENSE-1.0 in the LICENSE.

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

      To Recieve the alert signal from server.

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
    memcpy(config->area_id, config_message, sizeof(config->area_id));
    
    zlog_debug(category_debug, "area_id = [%s]", config->area_id);
    
    /* item 2 */
    fetch_next_string(file, config_message, sizeof(config_message)); 
    memcpy(config->serial_id, config_message, sizeof(config->serial_id));
    
    zlog_debug(category_debug, "serial_id = [%s]", config->serial_id);
    
    /* item 3 */
    fetch_next_string(file, config_message, sizeof(config_message)); 
    memcpy(config->server_ip, config_message, sizeof(config->server_ip));
    
    /* item 4 */
    fetch_next_string(file, config_message, sizeof(config_message)); 
    config -> server_port = atoi(config_message);
    
    /* item 5 */
    fetch_next_string(file, config_message, sizeof(config_message)); 
    config -> agent_port = atoi(config_message);
    
    /* item 6 */
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

ErrorCode single_running_instance(char *file_name){
    int retry_times = 0;
    int lock_file = 0;
    struct flock fl;

    retry_times = FILE_OPEN_RETRY;
    while(retry_times--){
        lock_file = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);

        if(-1 != lock_file){
            break;
        }
    }

    if(-1 == lock_file){
        zlog_error(category_health_report,
            "Unable to open lock file");
        zlog_error(category_debug,
            "Unable to open lock file");
        return E_OPEN_FILE;
    }

    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    if(fcntl(lock_file, F_SETLK, &fl) == -1){
        zlog_error(category_health_report, "Unable to lock file");
        zlog_error(category_debug, "Unable to lock file");
        close(lock_file);
        return E_OPEN_FILE;
    }

    char pids[10];
    snprintf(pids, sizeof(pids), "%d\n", getpid());
    if((size_t)write(lock_file, pids, strlen(pids)) != strlen(pids)){

        zlog_error(category_health_report,
                   "Unable to write pid into lock file");
        zlog_error(category_debug,
                   "Unable to write pid into lock file");
        close(lock_file);

        return E_OPEN_FILE;
    }

    return WORK_SUCCESSFULLY;
}


ErrorCode send_join_request(){
    char message[WIFI_MESSAGE_LENGTH];
    int ret_val = 0;

    memset(message, 0, sizeof(message));

    sprintf(message, "%d;%d;%d;%s;%s;", from_agent, 
                                  request_to_join, 
                                  BOT_SERVER_API_VERSION_LATEST,
                                  g_config.area_id,
                                  g_config.serial_id);

    udp_addpkt( &udp_config, 
                g_config.server_ip, 
                g_config.server_port,
                message,
                sizeof(message));

    return WORK_SUCCESSFULLY;
}

int main(int argc, char **argv) {
    ErrorCode return_value = WORK_SUCCESSFULLY;
    ErrorCode config_value = WORK_SUCCESSFULLY;
    ready_to_work = true;
    struct sigaction sigint_handler;
    /* Register handler function for SIGINT signal */
    sigint_handler.sa_handler = ctrlc_handler;
    sigemptyset(&sigint_handler.sa_mask);
    sigint_handler.sa_flags = 0;
    int last_join_request_time = 0;
    int current_time;

    /* Initialize the application log */
    if (zlog_init(LOG_FILE_NAME) == 0) {

        category_health_report =
            zlog_get_category(LOG_CATEGORY_HEALTH_REPORT);

        if (!category_health_report) {
            zlog_fini();
        }

        category_debug =
            zlog_get_category(LOG_CATEGORY_DEBUG);

        if (!category_debug) {
            zlog_fini();
        }
    }
    
    /* Ensure there is only single running instance */
    return_value = single_running_instance(AGENT_LOCK_FILE);
    if(WORK_SUCCESSFULLY != return_value){
        zlog_error(category_health_report,
                   "Error openning lock file");
        zlog_error(category_debug,
                   "Error openning lock file");
        return E_OPEN_FILE;
    }
    
    zlog_info(category_health_report,
              "Agent process is launched...");
    zlog_info(category_debug,
              "Agent process is launched...");
    
    config_value = get_config(&g_config, CONFIG_FILE_NAME);
    
    if (-1 == sigaction(SIGINT, &sigint_handler, NULL)) {
        zlog_error(category_health_report,
                   "Error registering signal handler for SIGINT");
        zlog_error(category_debug,
                   "Error registering signal handler for SIGINT");
    }
    
    return_value = Wifi_init();
    
    if(return_value != WORK_SUCCESSFULLY){
        zlog_error(category_health_report,
                   "Unable to initialize network");
        zlog_error(category_debug,
                   "Unable to initialize network");
                   
        return E_WIFI_INIT_FAIL;
    }
        
    last_join_request_time = 0;
        
    while(ready_to_work){
        
        current_time = get_clock_time();
        if( current_time - last_join_request_time >
            INTERVAL_FOR_RECONNECT_SERVER_IN_SEC ){

            zlog_info(category_debug,
                      "Send requets_to_join to server again");

            if(WORK_SUCCESSFULLY == send_join_request()){
                last_join_request_time = current_time;
            }
        }
        
        sPkt recv_queue = udp_getrecv(&udp_config);
        
        if(strlen(recv_queue.content)) {
            zlog_debug(category_debug, 
                       "received message = [%s]",
                       recv_queue.content);
                           
            udp_addpkt_without_encoding(&udp_config, 
                                        "127.0.0.1", 
                                        g_config.light_controller_port, 
                                        recv_queue.content, 
                                        strlen(recv_queue.content));
        }else{
            sleep_t(NORMAL_WAITING_TIME_IN_MS);
        }
    }
}

