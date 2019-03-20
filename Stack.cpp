//
//  Stack.cpp
//  CSC 412 - MazeSolver
//
//  Created by Chip Brommer on 9/22/18.
//  Copyright © 2018 Chip Brommer. All rights reserved.
//

#include <iostream>
#include <cassert>

#include "Stack.hpp"

using namespace std;

//Initializing the stack and setting the top to null
void Stack::initializeStack()
{
    stackTop = NULL;
}

//Bool to check is the stack is empty
bool Stack::isEmptyStack()
{
    return(stackTop == 0);
}

//Bool to check is the stack is full
bool Stack::isFullStack()
{
    return(stackTop == maxStackSize);
}

//Pushes a new Point onto the stack.
void Stack::push(Point newItem)
{
    if(!isFullStack())
    {
        list[stackTop] = newItem;
        
        stackTop++;
    }
}

//Returns the top Point off the stack
Point Stack::top()
{
    assert(stackTop != 0);
    
    return list[stackTop - 1];
}

//Pops the top Point off the stack
void Stack::pop()
{
    if (!isEmptyStack())
    {
        stackTop--;
    }
}

 //Destructor
Stack::~Stack()
{
    //deallocate the memory occupied by the array
    delete [] list;
}

//Constructor with a specified stacksize
Stack::Stack(int stackSize)
{
    if (stackSize <= 0)
    {
        cout << "Size of the array to hold the stack must "
        << "be positive." << endl;
        
        maxStackSize = 10;
    }
    else
    {
        //Setting the stack size to the parameter amount.
        maxStackSize = stackSize;
    }
    
    stackTop = 0;                    //set stackTop to 0
    list = new Point[maxStackSize];  //create the array to hold the stack elements
}

