# test file to send packet via UDP

import socket


msgFromClient       = "39DBB1F0E0737A05E538CDE000AEFC640336E10428B1F3DD396BD76A2355E3E5A86AEE61F0E0FACC69A280DAC0DE8DF1C84C32684D01EE04F40EEF5E018CB332FEF31956194179BDC28E94E20B70BC1C;lala"

bytesToSend         = str.encode(msgFromClient)

serverAddressPort   = ("140.109.22.5", 9998)

bufferSize          = 1024

 

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

import time

# Send to server using created UDP socket

UDPClientSocket.sendto(bytesToSend, serverAddressPort)

 

# msgFromServer = UDPClientSocket.recvfrom(bufferSize)

 

# msg = "Message from Server {}".format(msgFromServer[0])

# print(msg)