//
//  Queue.hpp
//  CSC 412 - MazeSolver
//
//  Created by Chip Brommer on 9/22/18.
//  Copyright © 2018 Chip Brommer. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>

// e.g. position [3][5] in an array would have row 3, col 5
struct Point {
    int x;
    int y;
};

//A class that contains a series of Locations
class Queue {
public:
    //Constructor. maxlen must be as large as the total number
    // of Locations that will ever be entered into this Queue.
    Queue(int maxlen);
    
    //Destructor
    ~Queue();
    
    //Insert a new Location at the end/back of our list
    void add(Point loc);
    
    //Return and "remove" the oldest Location not already extracted
    Point remove();
    
    //Is this Queue empty?
    bool isEmpty();
    
    //Member variables of an Queue, for implementation:
private:
    Point* contents; //Pointer to dynamically-allocated array
    int tail; // how many Locations were added so far?
    int head; // how many Locations were extracted so far?
};

#endif /* Queue_hpp */
