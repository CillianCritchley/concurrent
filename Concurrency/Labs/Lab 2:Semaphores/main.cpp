#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/*! \mainpage Semaphore
 * illustrates the use of mutex's to control flow of execution
*/



/*!
 * prints "i must print first" to the screen
 */

//! \brief prints "i must print first" to the screen
//! \param theSemaphore  A Semaphore instance
//! \param delay  a delay in seconds

void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}

//! \brief prints "this will appear second" after the print in taskOne has completed
//! \param theSemaphore  A Semaphore instance

void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/*!
   creates both threads and joins them to the main thread

*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  //< Launch the threads
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   //< Wait for the threads to finish
  threadOne.join();
  threadTwo.join();
  return 0;
}
