//
// Created by Cillian o Criothaile  on 01/03/19.
// License MIT
//
#include "SafeBuffer.h"

/*! \class SafeBuffer
 *
 * A buffer which producers and consumers and push and consume events to/from respectively
 *
 */


/*!
 * Create a buffer instance
 */
SafeBuffer::SafeBuffer() {
    // should use make shared instead here
    theMutex = std::shared_ptr<Semaphore>(new Semaphore(1));
//    theSemaphore = std::shared_ptr<Semaphore>(new Semaphore(0));
    theSemaphore = std::make_shared<Semaphore>(0);

//    theMutex= new Semaphore(1);
};

/*!
 *
 * @param newEric the character to be added to the buffer
 * @return  the size of the buffer
 *
 * The thread being executed waits on the mutex and if permitted to proceed pushes newEric to the vector of events.
 * It then releases the mutex and signals to the consumer that an item exists on the buffer
 */
int SafeBuffer::push(Event newEric) {
    theMutex->Wait();
    theData.push_back(newEric);
    int size=theData.size();
    theMutex->Signal();
    theSemaphore->Signal();
    return size;
} //push

/*!
 *
 * @return an event instance
 *
 * The thread being executed waits on the signalling semaphore to ensure that no attempt is made to consume from an empty buffer.
 * If an item exists in the buffer the thread waits on the mutex, takes the event from the vector of events and then
 * releases the mutex. The event is then returned to the caller.
 */
Event SafeBuffer::pop() {
    theSemaphore->Wait();
    theMutex->Wait();
    Event e=theData.back();
    theData.pop_back();
    theMutex->Signal();
    return e;
} //pop