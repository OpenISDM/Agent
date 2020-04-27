# LBeacon
#---------------------------------------------------------------------------
CC = gcc -std=gnu99 -O3
OBJS = LinkedList.o Mempool.o thpool.o UDP_API.o pkt_Queue.o BeDIS.o Agent.o
LIB = -L /usr/local/lib
INC = -I ../import

#---------------------------------------------------------------------------
all: Agent
Agent: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o Agent $(INC) $(LIB) -lpthread -lzlog -lEncrypt
	

Agent.o: 
	$(CC) Agent.c Agent.h $(INC) $(LIB) -c
BeDIS.o: 
	$(CC) $(CFLAGS) ../import/BeDIS.c -c
LinkedList.o:  
	$(CC) ../import/LinkedList.c $(LIB) -c
pkt_Queue.o: 
	$(CC) ../import/pkt_Queue.c  -c
UDP_API.o: 
	$(CC) $(CFLAGS) ../import/UDP_API.c -c
Mempool.o: 
	$(CC) ../import/Mempool.c  $(LIB) -c
thpool.o: 
	$(CC) ../import/thpool.c  $(LIB) -c
clean:
	find . -type f | xargs touch
	@rm -rf *.o *.h.gch *.log *.log.0 *.txt LBeacon
