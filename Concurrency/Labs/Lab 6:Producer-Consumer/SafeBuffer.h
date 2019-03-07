//
// Created by Cillian o Criothaile  on 01/03/19.
// License MIT
//

#pragma once
#include "Event.h"
#include "Semaphore.h"
#include <vector>

class SafeBuffer{
private:
    /* vector of events to stored the added events */
    std::vector<Event> theData;
    /* Semaphore instance to be used as a mutex */
    std::shared_ptr<Semaphore> theMutex;
    /* Semaphore instance to signal between producers and consumers */
    std::shared_ptr<Semaphore> theSemaphore;
public:
    SafeBuffer();
    int push(Event);
    Event pop();
};


