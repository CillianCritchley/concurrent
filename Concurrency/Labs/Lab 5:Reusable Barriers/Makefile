
CC=g++
CFLAGS= -std=c++11 -pthread

SIMPLE: main.cpp
	g++ -std=c++11 -pthread main.cpp Semaphore.cpp Barrier.cpp -o reuseableBarrier
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o
	$(CC) -o reuseableBarrier main.o Semaphore.cpp Barrier.cpp $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -Wall
DEBUG: ALL

CLEAN:
	rm *.o
