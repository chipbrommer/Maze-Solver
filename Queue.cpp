//
//  Queue.cpp
//  CSC 412 - MazeSolver
//
//  Created by Chip Brommer on 9/22/18.
//  Copyright © 2018 Chip Brommer. All rights reserved.
//

#include "Queue.hpp"

//Constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
Queue::Queue(int maxlen)
{
    contents = new Point[maxlen];
    head = 0;
    tail = 0;
}

//Destructor
Queue::~Queue()
{
    delete[] contents;
}

//Insert a new Location at the end/back of our list
void Queue::add(Point loc)
{
    //set the value of contents at index 'tail' to loc
    contents[tail] = loc;
    tail++; //increment tail
}

//Return and "remove" the oldest Location not already extracted
Point Queue::remove()
{
    //create new object 'l' that contains location at index 'head'
    Point l = contents[head];
    head++; //increment head
    return l;
}

// Is this Queue empty?
bool Queue::isEmpty()
{
    return head == tail;
}
