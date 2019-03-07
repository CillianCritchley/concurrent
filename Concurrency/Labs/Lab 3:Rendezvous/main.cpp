#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \mainpage Rendezvous
 * Uses semaphores to implement a rendezvous
*/



//! \brief displays a message that is split in to 2 sections to show how a rendezvous works
//! \param firstSem  A Semaphore instance
//! \param secondSem  A Semaphore instance
//! \param delay  a delay in seconds
//!
//! outputs a message to announce its arrival at the rendezvous point, then waits on the secondSem semaphore
//! until taskTwo has signalled on it, meaning both tasks may continue execution
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  firstSem->Signal();
  secondSem->Wait();
  std::cout << "Task One has left!"<<std::endl;
}

//! \brief displays a message that is split in to 2 sections to show how a rendezvous works
//! \param firstSem  A Semaphore instance
//! \param secondSem  A Semaphore instance
//! \param delay  a delay in seconds
//!
//! outputs a message to announce its arrival at the rendezvous point, then waits on the firstSem semaphore
//! until taskOne has signalled on it, meaning both tasks may continue execution
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  secondSem->Signal();
  firstSem->Wait();

  std::cout << "Task Two has left "<<std::endl;
}

//! creates two threads and joins them to the main thread
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  // Launch the threads
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
