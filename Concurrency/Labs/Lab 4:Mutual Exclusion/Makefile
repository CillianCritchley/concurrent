
CC=g++
CFLAGS= -std=c++11 -pthread 

SIMPLE: main.cpp
	g++ -std=c++11 -pthread main.cpp Semaphore.cpp -o Mutex
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)



CLEAN:
	rm *.o
