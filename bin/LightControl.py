import serial
import socket
import time
import sys
sys.path.append("../config/")
import conf

FROM_SOURCE_TYPE 	= 0
FIRE_ALARM 		= 1
API_VERSION 	        = 2
MODE 			= 3
DURATION 		= 4

FROM_SERVER = str(2)
FIRE_ALARM = str(7)

def get_host_ip():
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		s.connect(('8.8.8.8',80))
		ip = s.getsockname()[0]
	finally:
		s.close()
	return ip
def alert_operation(mode, duration):
	if(mode == 1):
		conn.write('RO')
		time.sleep(duration)
		conn.write('FQ')
	elif(mode == 2):
		conn.write('1P')
		time.sleep(duration)
		conn.write('FQ')
	elif(mode == 3):
		conn.write('RO1P')
		time.sleep(duration)
		conn.write('FQ')
	else: 
		print('unrecognized mode')

#setup serial port
conn = serial.Serial('/dev/ttyUSB0',timeout=.2)
time.sleep(3)
conn.write('FQ')

# setup UDP client port
IP = get_host_ip()
serverAddressPort   = ("127.0.0.1", conf.light_controller_port)
bufferSize  = 1024
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(serverAddressPort)
print('Start UDP Server Listening at port: {}'.format(IP))

while True:
	bytesAddressPair = sock.recvfrom(bufferSize)
	message = bytesAddressPair[0]
	address = bytesAddressPair[1]
	API_ver = None
	splitted_message = message.split(';')
	if(splitted_message[FROM_SOURCE_TYPE] != str(FROM_SERVER)):
		print('Data aren\'t from Server')
		continue
	elif(splitted_message[FIRE_ALARM] != str(FIRE_ALARM)):
		print('FIRE_ALARM Error')
		continue
	else:
		API_ver = splitted_message[API_VERSION]
                mode = int(splitted_message[MODE])
		duration = int(splitted_message[DURATION])
		alert_operation(mode, duration)
	        time.sleep(0.3)
