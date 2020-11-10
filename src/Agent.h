/*
  2020 © Copyright (c) BiDaE Technology Inc. 
  Provided under BiDaE SHAREWARE LICENSE-1.0 in the LICENSE.

  Project Name:

      BeDIS 
      
  File Description:

    This file contains the programs executed by location beacons to
    support indoor poositioning and object tracking functions.

  File Name:

    Agent.h

  Version:

    1.0,  20200427

  Abstract:

    To Recieve the alert signal from server.

  Authors:

    Wayne Kang, biggkqq@gmail.com

*/

#ifndef AGENT_H
#define AGENT_H

/*
* INCLUDES
*/
#include "BeDIS.h"
#include "Version.h"

/* File path of the config file of the Agent */
#define CONFIG_FILE_NAME "../config/conf.conf"

/* File path of the logging file*/
#define LOG_FILE_NAME "../config/zlog.conf"

/* The lock file for Agent  */
#define AGENT_LOCK_FILE "../log/Agent.pid"

/* Time interval in seconds for reconnect to server */
#define INTERVAL_FOR_RECONNECT_SERVER_IN_SEC 30

typedef struct Config {
    
    /* The IP address of the server */
    char server_ip[NETWORK_ADDR_LENGTH];

    /* A port that the server are listening on and for agent to send to. */
    int server_port;
    
    /* A port for agent to send on */
    int agent_port;
    
    /* A port for internal light controller to send on */
    int light_controller_port;
} Config;

/*
  GLOBAL VARIABLES
*/

/* Struct for storing config information from the input file */
Config g_config;

/* The struct of UDP configuration */
sudp_config udp_config;

/*
  Wifi_init:

     This function initializes the Wifi's objects.

  Parameters:

     None

  Return value:

     ErrorCode - The error code for the corresponding error or successful

 */
ErrorCode Wifi_init();


/*
  Wifi_free:

     When called, this function frees the queue of the Wi-Fi pkts and sockets.

  Parameters:

     None

  Return value:

     None

*/
void Wifi_free();


/*
  single_running_instance:

      This function write a file lock to ensure that system has only one
      instance of running Agent.

  Parameters:
      file_name - the name of the lock file that specifies PID of running
                  Agent

  Return value:
      ErrorCode - indicate the result of execution, the expected return code
                  is WORK_SUCCESSFULLY

*/

ErrorCode single_running_instance(char *file_name);

/*
  send_join_request:

      This function sends join_request to server.

  Parameters:

      None

  Return value:

      ErrorCode - The error code for the corresponding error if the function
                  fails or WORK SUCCESSFULLY otherwise
*/

ErrorCode send_join_request();

#endif /* AGENT_H */