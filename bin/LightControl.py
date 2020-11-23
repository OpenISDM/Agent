import serial
import socket
import time
import sys
sys.path.append("/home/bedis/Agent/config/")
import conf

INDEX_SOURCE_TYPE 	= 0
INDEX_PACKET_TYPE 	= 1
INDEX_API_VERSION       = 2
INDEX_MODE 	        = 3
INDEX_DURATION 		= 4

FROM_SERVER = str(2)

FIRE_ALARM  = str(7)

ALARM_TYPE_NONE = 0
ALARM_TYPE_LIGHT = 1
ALARM_TYPE_SOUND = 2
ALARM_TYPE_LIGHT_SOUND = 3

def alert_operation(mode, duration):
	if(mode == ALARM_TYPE_NONE):
                conn.write('FQ')
        elif(mode == ALARM_TYPE_LIGHT):
		conn.write('RO')
                if(duration > 0):
      		    time.sleep(duration)
		    conn.write('FQ')
	elif(mode == ALARM_TYPE_SOUND):
		conn.write('1P')
                if(duration > 0):
		    time.sleep(duration)
		    conn.write('FQ')
	elif(mode == ALARM_TYPE_LIGHT_SOUND):
		conn.write('RO1P')
                if(duration > 0):
		    time.sleep(duration)
		    conn.write('FQ')
	else: 
		print('unrecognized mode')

#setup serial port
conn = serial.Serial('/dev/ttyUSB0',timeout=.2)
time.sleep(3)
conn.write('FQ')

# setup UDP client port
serverAddressPort   = ("127.0.0.1", conf.light_controller_port)
bufferSize  = 1024
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(serverAddressPort)

while True:
	bytesAddressPair = sock.recvfrom(bufferSize)
	message = bytesAddressPair[0]
	address = bytesAddressPair[1]
	API_ver = None
	splitted_message = message.split(';')
	if(splitted_message[INDEX_SOURCE_TYPE] == str(FROM_SERVER)):
	    if(splitted_message[INDEX_PACKET_TYPE] == str(FIRE_ALARM)):
		API_ver = splitted_message[INDEX_API_VERSION]
                mode = int(splitted_message[INDEX_MODE])
		duration = int(splitted_message[INDEX_DURATION])
		alert_operation(mode, duration)
	        time.sleep(0.3)
        else:
            print('Unknow request', message)
