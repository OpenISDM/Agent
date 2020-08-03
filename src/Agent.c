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

int main(int argc, char **argv) {
    ErrorCode return_value = WORK_SUCCESSFULLY;
    ErrorCode config_value = get_config(&g_config, CONFIG_FILE_NAME);
    ready_to_work = true;
    struct sigaction sigint_handler;
    /* Register handler function for SIGINT signal */
    sigint_handler.sa_handler = ctrlc_handler;
    sigemptyset(&sigint_handler.sa_mask);
    sigint_handler.sa_flags = 0;

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
        
    while(ready_to_work){
        
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

