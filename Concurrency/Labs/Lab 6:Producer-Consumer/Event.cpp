//
// Created by Cillian o Criothaile  on 01/03/19.
// License MIT
//

/*! \class Event
 *
 * An event abstraction which creates and consumes character events
 *
 */
#include "Event.h"
#include <stdlib.h>
#include <iostream>

/*!
 * creates a random charcater and outputs it
 */
Event::Event(){
    eric = 'a'+rand()%26;
//    std::cout << "producing " << eric << std::endl;
    std::cout <<    eric ;
 };

/*!
 * Converts the created character of the event instance into uppercase
 */
bool Event::consume(){
    char betterEric = eric-32;
    std::cout << betterEric;
};
