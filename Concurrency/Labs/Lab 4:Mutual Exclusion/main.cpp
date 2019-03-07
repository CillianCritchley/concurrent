#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
/*! \mainpage Mutual Exclusion
 * Uses a semaphore instance as a mutex to enforce mutual exclusion
*/

/*!
 *  The number of threads that are to be created
 */
static const int num_threads = 100;
/*!
 * to be shared among all threads and incremented without race conditions
 */
int sharedVariable=0;



/*! \brief increments a shared variable a number of times across multiple threads
 *
 * @param firstSem   A Semaphore instance
 * @param numUpdates The number of times the shared variable is to be incremented per thread
 *
 * This function is passed to a number of threads, each of which is to increment the sharedVariable within numUpdates
 *  times.
 */
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){

 
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    firstSem->Wait();
    sharedVariable++;
    firstSem->Signal();
  }

}

/*!
 * creates a num_threads number of threads. Assigns the updateTask function to each one, runs them and then
 * joins them to the main thread
 */
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  // Launch the threads
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  // Join the threads with the main thread
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
