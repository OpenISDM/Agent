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

ErrorCode Wifi_init(){
    /* Initialize the Wifi cinfig file */
    if(udp_initial(&udp_config, 9998)
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
    return_value = Wifi_init();
    if(return_value == WORK_SUCCESSFULLY){
      printf("Success!!\n");
      while(true){
        sPkt recv_queue = udp_getrecv(&udp_config);
        if(strlen(recv_queue. content)) {
          udp_addpkt(&udp_config, "127.0.0.1", 9997, 
               recv_queue.content, strlen(recv_queue.content));
        }else{
          sleep_t(NORMAL_WAITING_TIME_IN_MS);
        }
      }
    }else{
      printf("Wrong!!\n");
    }
    
}

