// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>
Barrier::~Barrier() {}

Barrier::Barrier(int numThreads) :numThreads(numThreads),
sem1(std::shared_ptr<Semaphore>(new Semaphore(0))),
sem2(std::shared_ptr<Semaphore>(new Semaphore(1))),
mutex(std::shared_ptr<Semaphore>(new Semaphore(1))){
}


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
// Barrier.cpp ends here
