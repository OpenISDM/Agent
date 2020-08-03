/*
Copyright (c) BiDaE Technology Inc. All rights reserved.

License:

    BiDaE SHAREWARE LICENSE
    Version 1.0, 31 July 2020

    Copyright (c) BiDaE Technology Inc. All rights reserved.
    The SOFTWARE implemented in the product is copyrighted and protected by 
    all applicable intellectual property laws worldwide. Any duplication of 
    the SOFTWARE other than for archiving or resetting purposes on the same 
    product without the written agreement from BiDaE Technology could be a 
    violation of law. For the avoidance of doubt, redistribution of this 
    SOFTWARE in source or binary form is prohibited. You agree to prevent 
    any unauthorized copying and redistribution of the SOFTWARE. 

    BiDaE Technology Inc. is the license steward. No one other than the 
    license steward has the right to modify or publish new versions of this 
    License. However, You may distribute the SOFTWARE under the terms of the 
    version of the License under which You originally received the Covered 
    Software, or under the terms of any subsequent version published by the 
    license steward.

    LIMITED WARRANTY:

    BiDaE Technology Inc. or its distributors, depending on which party sold 
    the SOFTWARE, warrants that the media on which the SOFTWARE is installed 
    will be free from defects in materials under normal and purposed use.

    BiDaE Technology Inc. or its distributor warrants, for your benefit alone, 
    that during the Warranty Period the SOFTWARE, shall operate substantially 
    in accordance with the functional specifications in the User's Manual. If, 
    during the Warranty Period, a defect in the SOFTWARE appears, You may 
    obtain a replacement of the SOFTWARE. Any replacement SOFTWARE will be 
    warranted for the remainder of the Warranty Period attached to the product.

    WHEN THE WARRANTY PERIOD HAS BEEN EXPIRED, THIS SOFTWARE IS PROVIDED 
    ''AS IS,'' AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
    PARTICULAR PURPOSE ARE DISCLAIMED. HENCEFORTH, IN NO EVENT SHALL BiDaE 
    TECHNOLOGY INC. OR ITS COLLABORATOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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