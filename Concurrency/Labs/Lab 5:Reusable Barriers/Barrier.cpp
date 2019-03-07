

/*!
 * \class Barrier
 *
 * A reusable barrier class implemented using Semaphores
 */
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>

/*!
 * Virtual destructor for the Barrier class
 */
Barrier::~Barrier() {}

/*!
 *
 * @param numThreads the number of threads which the barrier is intended to work with
 * @param sem1 a semaphore instance
 * @param sem2 a semaphore instance
 * @param mutex a semaphore instance to be used for mutual exclusion
 *
 *
 */
Barrier::Barrier(int numThreads) :numThreads(numThreads),
sem1(std::shared_ptr<Semaphore>(new Semaphore(0))),
sem2(std::shared_ptr<Semaphore>(new Semaphore(1))),
mutex(std::shared_ptr<Semaphore>(new Semaphore(1))){
}

/*!
 * Each thread calls this function and, having gained access to the mutex, increments the count variable to register
 * its presence. It checks to see if it is the last thread through. If not, it releases the mutex and proceeds to wait
 * on sem1 where it remains until the last thread has reached the critical section.  If it is the last thread through
 * it locks the second barrier (sem2) and opens the first (sem1).
 *
 * All threads at this point continue execution down towards the second barrier. Each thread grabs the mutex, decrements
 * the count variable to register that it has passed this point and checks to see if it is the last thread through.
 * If it is not, it releases the mutex and proceeds to wait on sem1 until the last thread through opens the barrier.
 * If it is the last thread through it locks the top barrier and then unlocks the bottom, allowing all threads to proceed
 * through the barriers again.
 */

void Barrier::wait() {

    mutex->Wait();
    count++;

    if(count == numThreads)
    {
        sem2->Wait();
        sem1->Signal();
    }
    mutex->Signal();


    sem1->Wait();
    sem1->Signal();

    mutex->Wait();

    count--;
    if (count == 0)
    {
        sem1->Wait();
        sem2->Signal();

    }
    mutex->Signal();

    sem2->Wait();
    sem2->Signal();

}
// 
