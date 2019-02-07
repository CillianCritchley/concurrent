#Joseph Kehoe 13/9/2017
#First simple Makefile
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.


CC=g++
CFLAGS= -std=c++11 -pthread

SIMPLE: main.cpp
	g++ -std=c++11 -pthread main.cpp Semaphore.cpp Barrier.cpp -o semprog -Wall



CLEAN:
	rm *.o
