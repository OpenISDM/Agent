/*
Copyright (c) 2016 Academia Sinica, Institute of Information Science

License:

    GPL 3.0 : The content of this file is subject to the terms and
    conditions defined in file 'COPYING.txt', which is part of this source
    code package.

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

typedef struct Config {
    int agent_port;
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

#endif /* AGENT_H */