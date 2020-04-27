/*
Copyright (c) 2016 Academia Sinica, Institute of Information Science

License:

    GPL 3.0 : The content of this file is subject to the terms and
    conditions defined in file 'COPYING.txt', which is part of this source
    code package.

Project Name:

    BeDIS

File Description:

    This header file contains declarations of variables, structs and
    functions and definitions of global variables used in the LBeacon.c file.

File Name:

    LBeacon.h

Version:

    2.0,  20190911

Abstract:

    BeDIS uses LBeacons to deliver 3D coordinates and textual
    descriptions of their locations to users' devices. Basically, a
    LBeacon is an inexpensive, Bluetooth Smart Ready device. The 3D
    coordinates and location description of every LBeacon are retrieved
    from BeDIS (Building/environment Data and Information System) and
    stored locally during deployment and maintenance times. Once
    initialized, each LBeacon broadcasts its coordinates and location
    description to Bluetooth enabled user devices within its coverage
    area.

Authors:

    Han Wang, hollywang@iis.sinica.edu.tw
    Jake Lee, jakelee@iis.sinica.edu.tw
    Joey Zhou, joeyzhou@iis.sinica.edu.tw
    Kenneth Tang, kennethtang@iis.sinica.edu.tw
    Chun Yu Lai, chunyu1202@gmail.com

*/

#ifndef LBEACON_H
#define LBEACON_H

/*
* INCLUDES
*/
#include "BeDIS.h"
#include "Version.h"


typedef struct Config {

    /* String representation of the area id of the beacon location */
    char area_id[CONFIG_BUFFER_SIZE];

    /* String representation of the X coordinate of the beacon location */
    char coordinate_X[CONFIG_BUFFER_SIZE];

    /* String representation of the Y coordinate of the beacon location */
    char coordinate_Y[CONFIG_BUFFER_SIZE];

    /* String representation of the Z coordinate of the beacon location */
    char coordinate_Z[CONFIG_BUFFER_SIZE];

    /* The expected lowest basement under ground in the world. This constant
    will be added to Z-coordinate (level information) gotten from input
    configuration file. This adjustment helps us to have positive number in the
    config data structure and lets Z-coordinate occupy only 2 bytes in UUID.
    */
    int lowest_basement_level;

    /* String representation of the universally unique identifer */
    char uuid[CONFIG_BUFFER_SIZE];

    /* The dongle used to advertise */
    int advertise_dongle_id;

    /* Time interval in units of 0.625ms between advertising by a LBeacon */
    int advertise_interval_in_units_0625_ms;

    /* The rssi value used to advertise */
    int advertise_rssi_value;

    /* The dongle used to scan */
    int scan_dongle_id;
    
    /* Time interval in units of 0.625ms between scanning by a LBeacon */
    int scan_interval_in_units_0625_ms;

    /* The required signal strength */
    int scan_rssi_coverage;

    /* The list of all acceptable mac address prefixes */
    struct List_Entry mac_prefix_list_head;

    /* The IPv4 network address of the gateway */
    char gateway_addr[NETWORK_ADDR_LENGTH];

    /* The UDP port of gateway connection*/
    int gateway_port;

    /* The IPv4 network address of LBeacon */
    char local_addr[NETWORK_ADDR_LENGTH];

    /* The UDP port for LBeacon to listen and receive UDP from gateway*/
    int local_client_port;

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