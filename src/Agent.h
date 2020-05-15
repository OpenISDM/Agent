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

      To Recieve the alert signal from LBeacon.

 Authors:

      Wayne Kang, biggkqq@gmail.com

*/

#ifndef LBEACON_H
#define LBEACON_H

/*
* INCLUDES
*/
#include "BeDIS.h"
#include "Version.h"

#define CONFIG_FILE_NAME "../config/conf.conf"

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
  EXTERNAL FUNCTIONS
*/

/*
  opendir:

      This function is called to open a specified directory.

  Parameters:

      dirname - the name of the directory to be opened.

  Return value:

      dirp - a pointer to the directory stream.
*/

#endif /* LBEACON_H */