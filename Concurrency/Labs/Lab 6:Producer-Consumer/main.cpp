//
// Created by Cillian o Criothaile  on 01/03/19.
// License MIT
//
#include "Event.h"
#include "SafeBuffer.h"
#include <iostream>
#include <thread>
#include <vector>

/*! \mainpage producer Consumer
 * A producer consumer implementation using semaphores
*/

/*! the number of threads to be created */
static const int num_threads = 100;
/*! the number of times the producer will create and add an event to the buffer */
int numLoops = 4;



/*!
 *
 * @param theBuffer a SafeBuffer instance
 * @param numLoops the number of times an event is to be created and added to the buffer
 *
 * Each time the loop runs an event is created and pushed to the buffer
 */
// create event returns an event, not an int.
void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
//    Event e= createEvent(i);
    Event e;
    //this returns an int, might have to check if the buffer is full before pushing
    theBuffer->push(e);
  }
  

}

/*!
 *
* @param theBuffer a SafeBuffer instance
 * @param numLoops the number of times an event is to be removed from the buffer
 *
 * Each time the loop runs an event is to be taken from the buffer and then consumed
 */

void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
//    std::shared_ptr<Event> e= theBuffer->pop();
    Event e= theBuffer->pop();
    e.consume();
  }
  

}


/*!
 *  creates a vector of threads for producers and for consumers of size num_threads.
 *  Creates a Safebuffer instance to store events.
 *  creates and adds producer and consumer threads to their respective vectors and then joins them to the main thread
 */
int main(void){

//  std::vector<std::thread> vt(num_threads);
  std::vector<std::thread> producers(num_threads);
  std::vector<std::thread> consumers(num_threads);
  std::shared_ptr<SafeBuffer> aBuffer( new SafeBuffer());
  /**< Launch the threads  */
  for(std::thread& p: producers){
    p=std::thread(producer,aBuffer,numLoops);
  }
  for(std::thread& c: consumers){
        c=std::thread(consumer,aBuffer,numLoops);
    }
  /**< Join the threads with the main thread */
  for (auto& p :producers){
      p.join();
  }

  for(auto& c: consumers)
  {
      c.join();
  }

  std::cout << std::endl;
  return 0;
}
