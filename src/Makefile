CC = gcc
CFLAGS = -Wall -O1 -w -lpthread
OBJS = myThread.o mysem.o

myThread	: $(OBJS)
	$(CC) $(CFLAGS) -o myThread $(OBJS) 

myThread.o: myThread.c myThread.h
mysem.o: mysem.c mysem.h

clean:
	rm myThread
	rm mysem.o

