#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>
/*! \mainpage Reusable Barriers
 * A reuseable barerier implementation using semaphores
*/

/*!
 * the number of threads to be created
 */
static const int num_threads = 100;



/*! \brief Threads meet at barriers which do not open until all threads are waiting there
 *
 * @param theBarrier  The Barrier instance which the threads must wait at
 * @param numLoops the number of times the threads must complete the round trip
 *
 * The threads meet at the first barrier and proceed once all threads are waiting there.
 * Each thread outputs the Character A as well as the current index of the loop being iterated over.
 * They meet again at a second barrier and proceed once all threads have reached it.
 * Each thread outputs the Character B as well as the current index of the loop being iterated over.
 * The threads continue through the loop until they reach and wait at the first Barrier again.
 */
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task
    theBarrier->wait();
    std::cout << "A"<< i;
    //Barrier
    theBarrier->wait();
//    Do second half of task
    std::cout<< "B" << i;
  }
  

}

/*!
 *  creates a vector of threads and a Barrier instance, both of size num_threads.
 *  Assigns the barrierTask function to each thread for 10 iterations, then runs and joins each thread to the main
 *  thread.
 */

int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(barrierTask,aBarrier,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << std::endl ;
  return 0;
}
