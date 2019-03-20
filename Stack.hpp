//
//  stackADT.cpp
//  CSC 412 - MazeSolver
//
//  Created by Chip Brommer on 9/30/18.
//  Copyright © 2018 Chip Brommer. All rights reserved.
//

#ifndef H_Stack
#define H_Stack

#include "Queue.hpp"

//A class that contains a series of Points
class Stack
{
public:
    //Method to initialize the stack to an empty state.
    void initializeStack();
  
    //Function to determine whether the stack is empty.
    bool isEmptyStack();
    
    //Function to determine whether the stack is full.
    bool isFullStack();
    
    //Function to push a new Point on to the stack.
    void push(Point);
    
    //Function to return the top element of the stack.
    Point top();
    
    //Function to remove the top element of the stack.
    void pop();
    
    //Create an array of the size stackSize to hold
    //the stack elements. The default stack size is 10.
    Stack(int stackSize = 10);
    
        //destructor
    ~Stack();
    
private:
    int maxStackSize; //variable to store the maximum stack size
    int stackTop;     //variable to point to the top of the stack
    Point *list;
};

#endif
