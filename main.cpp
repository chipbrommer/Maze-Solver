/***************************************************************************************************
 *
 * Author: Chip Brommer
 * Date: September 13, 2018
 * Contact: Fredrick.Brommer@usm.edu
 *
 * Description: Create an A.I. Agent that can process a 10x10 maze.
 *
 ***************************************************************************************************/


#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>


//Defines for the number of rows and columns in the maze
#define arrayRows 10
#define arrayColumns 10

using namespace std;

//Defining a struct called "Point" to hold an x and y co-ordinate.
struct Point
{
    int x;
    int y;
};

//Data structure for the queue used in the searches
struct Node
{
    Point location;     //Holds the co-ordinated of a location
    Point parent;
    int distance;       //Holds the number of moves from entrance to exit
};

void welcomeMessage();                        //This is the welcome message for the program
void workHorse();     //This is the main function of the program that handles all the calls to each function.
void fileReader(char [][10], fstream&);       //This function reads the input file
void findEntrance(char [][10], fstream&);     //This function finds the "E" on the maze file
void findExit(char [][10], fstream&);         //This function finds the "X" on the maze file
void arrayTextPrinter(char [][10], fstream&); //This function prints an array to the user and a file
void breadthFirstSearch(char[][10], fstream&);//This function is the breadth first search function
void depthFirstSearch(char[][10], fstream&);  //This function is the depth first search functon
bool validMove(int, int);
int programEnd();                             //This is the exit message for the program

Point mazeEntrance = {0,0}; //Creates a struct of Point called mazeEntrance to hold the location of the Entrance
Point mazeExit = {0,0};     //Creates a struct of Point called mazeExit to hold the location of the Exit

int main()
{
    //Time based random number generator for the program.
    //This is in main so it only gets called once and starts upon program run.
    srand(time(NULL));
    
    //Calling the welcome message for the program
    welcomeMessage();

    //Calling the handling function
    workHorse();
    
    //Calling the closing procedure for the program.
    programEnd();
    
}

//-------------------------------------------------------------------------------------------------
//welcomeMessage - This function holds the welcome message for the program. Prints it to the
//                 console for the user.
//-------------------------------------------------------------------------------------------------
void welcomeMessage()
{
    cout << "\t\t\t\t\tWelcome to Chips Maze Solver\n\n";
}


//-------------------------------------------------------------------------------------------------
//workHorse - This function is where all the functions pertaining to the maze are called and
//            worked.
//-------------------------------------------------------------------------------------------------
void workHorse()
{
    //Initializing the 2D to 'A' in every slot.
    char mazeArray[arrayRows][arrayColumns];
    
    //Creating new txt file for console output
    fstream outputFile;
    outputFile.open("AI-Program1-Output.txt", fstream::out);
    
    //Calling the file reader to read in the txt file
    fileReader(mazeArray, outputFile);
    
    //Finding the entrance
    findEntrance(mazeArray, outputFile);
    
    //Finding the exit
    findExit(mazeArray, outputFile);
    
    //Copying the initial array into two duplicates
    char mazeArrayCopy[arrayRows][arrayColumns];
    char mazeArrayCopyTwo[arrayRows][arrayColumns];
    
    //Initializing the 2D to 'A' in every slot.
    for(int x = 0; x < arrayRows; x++)
    {
        for(int y = 0; y < arrayColumns; y++)
        {
            mazeArrayCopy[x][y] = mazeArray[x][y];
            mazeArrayCopyTwo[x][y] = mazeArray[x][y];
        }
    }
    
    //Calling the Breadth First Search Function
    breadthFirstSearch(mazeArray, outputFile);
    
    //Calling the Depth First Search Function
    depthFirstSearch(mazeArrayCopyTwo, outputFile);
    
    //Closing the output file
    outputFile.close();
    
}

//-------------------------------------------------------------------------------------------------
//fileReader - This function will read the file and store it into the 2D array.
//-------------------------------------------------------------------------------------------------
void fileReader(char mazeArray[10][10], fstream& outputFile)
{
    //Variable to hold the user specified filename. 
    string filename;
    
    //This allows the user to select a specific file they would like to open
    //Useful incase they would prefer multiple mazes.
    cout << "Enter the name of the file you want to open.\n";
    cout << "This file must be a .txt format file.\n";
    cout << "Enter Here: ";
    cin >> filename;                         //recieving file name from user
    cout << endl;
    
    fstream mazeFile;                       //Creating the input file
    mazeFile.open(filename + ".txt");       //Opening the specified file by user + .txt format extension

    //If the file did open, reads in the file and stores it into the mazeArray
    if(mazeFile.is_open())
    {
        cout << "File Opened successfully!\n\n";
        cout << "Reading data from file...\n\n";
        
        for(int y = 0; y < arrayRows; y++)
        {
            for(int x = 0; x < arrayColumns; x++)
            {
                mazeFile >> mazeArray[x][y];
            }
        }
        
        //Notifying output file of the file opened.
        outputFile << "Output for maze file: " << filename << ".txt\n";
        
        //Closing the input file
        mazeFile.close();
        
        //Printing the new array
        arrayTextPrinter(mazeArray, outputFile);
        
    }
    else            //File was not found, did not open a file.
    {
        cout << "\t---File name supplied was not found---.\n";
        cout << "\t ---Check your files and try again---.\n";
        programEnd();
    }
}

//-------------------------------------------------------------------------------------------------
//findEntrance - This function will search the maze for the entrance and then store its location.
//-------------------------------------------------------------------------------------------------
void findEntrance(char Array[10][10], fstream& outputFile)
{
    //Bool to trigger if the entrance is found or not.
    bool entranceFound = false;
    
    //Checking each slot in the array for the entrance point.
    for(int rowCount = 0; rowCount < arrayRows; rowCount++)
    {
        for(int columnCount = 0; columnCount < arrayColumns; columnCount++)
        {
            //If statement to check the currentPoint location of the array for the searchedLetter
            if(Array[rowCount][columnCount] == 'E')
            {
                mazeEntrance.x = rowCount;        //Setting the row location
                mazeEntrance.y = columnCount;     //Setting the column location
                
                entranceFound = true;     //Setting the found boolean to true
                
                cout << "\nThe entrance is located at point (" << mazeEntrance.x + 1 << "," << mazeEntrance.y + 1 << ").\n\n";
                outputFile << "The entrance is located at point (" << mazeEntrance.x + 1 << "," << mazeEntrance.y + 1 << ").\n\n";
                
                break;          //Breaks out of the for loops
            }
        }
    }
    
    //If the entrance is not found
    if(entranceFound == false)
    {
        cout << "The entrance was not found.\n";
        cout << "Please link a new maze and try again.\n\n";
        
        //Calls the program end.
        programEnd();
    }
    
}

//-------------------------------------------------------------------------------------------------
//findExit - This function will search the maze for the exit and then store its location.
//-------------------------------------------------------------------------------------------------
void findExit(char Array[10][10], fstream &outputFile)
{
    bool exitFound = false;         //Bool to trigger if the exit is found or not.
    
    for(int rowCount = 0; rowCount < arrayRows; rowCount++)
    {
        for(int columnCount = 0; columnCount < arrayColumns; columnCount++)
        {
            //If statement to check the currentPoint location of the array for the searchedLetter
            if(Array[rowCount][columnCount] == 'X')
            {
                mazeExit.x = rowCount;        //Setting the row location
                mazeExit.y = columnCount;     //Setting the column location
                
                exitFound = true;     //Setting the found boolean to true
                
                cout << "The exit is located at point (" << mazeExit.x + 1 << "," << mazeExit.y + 1 << ").\n\n";
                outputFile << "The exit is located at point (" << mazeExit.x + 1 << "," << mazeExit.y + 1 << ").\n\n";
                
                break;                  //Breaks out of the for loops if the exit is found.
            }
        }
    }
    
    //If the exit was not found
    if(exitFound == false)
    {
        cout << "The exit was not found.\n";
        cout << "Please link a new maze and try again.\n\n";
        
        //Calls the program end
        programEnd();
    }
    
}

//-------------------------------------------------------------------------------------------------
//arrayTextPrinter - Prints the array to the user and to a text file
//-------------------------------------------------------------------------------------------------
void arrayTextPrinter(char Array[10][10], fstream &outputFile)
{
    for (int c = 0; c < arrayColumns; c++)
    {
        cout << "\t" << c+1;
        outputFile << "\t" << c+1;
    }
    
    cout << endl;
    outputFile << endl;
    
    for(int a = 0; a < arrayColumns; a++)
    {
        for(int b = 0; b < arrayRows; b++)
        {
            if (b == 0)
            {
                cout << a+1 << "\t";
                outputFile << a+1 << "\t";
            }
            
            cout << Array[a][b] << "\t";                  //Printing number to console
            outputFile << Array[a][b] << "\t";            //Printing number to txt file
        }
        
        cout << endl;                                     //ends the line to go to the next row
        outputFile << endl;                               //ends the line to go to the next row
    }
}

//-------------------------------------------------------------------------------------------------
//programEnd - Prompts the user to enter any key to close the program, then ends the program.
//-------------------------------------------------------------------------------------------------
int programEnd()
{
    cout << "\nPress any key to end...";
    cin.get();
    cin.get();
    exit(0);        //Same as return 0, but causes immediate exit.
}

//-------------------------------------------------------------------------------------------------
//depthFirstSearch - This function used a Depth First searching type function to find the end
//                   of the maze.
//--------------------------------------------------------------------------------------------------
void depthFirstSearch(char mazeArray[arrayRows][arrayColumns], fstream& outputFile)
{
    //Starting timer
    auto start = chrono::system_clock::now();
    
    //Header for the display and the output file
    cout << "\t\tDepth First Search\n";
    cout << "\t\t__________________\n";
    outputFile << "\t\tDepth First Search\n";
    outputFile << "\t\t__________________\n";
    
    //Holds the found bool for the entrance and exit.
    bool found = false;
    
    //Array to hold only the path taken.
    char pathTakenArray[arrayRows][arrayColumns];
    
    //Filling the pathTakenArray with empty characters
    for( int u = 0; u < arrayRows; u++)
    {
        for( int h = 0; h < arrayColumns; h++)
        {
            pathTakenArray[u][h] = ' ';
        }
    }
    
    //Dynamic declaration of 2D arrays
    bool** visitedArray = new bool*[arrayColumns];
    Point** pointArray = new Point*[arrayColumns];
    
    //This struct will hold a temporary location to act as north, east, south, west from the currentPoint point.
    Point tempPoint;
    
    //This struct will hold the currentPoint point that is currently being checked.
    Point currentPoint;
    
    //This point will serve as a tester for the while loop
    Point testPoint;
    
    //Counter for the while loop.
    int counter = 0;
    
    //Allocation rows within the 2D arrays.
    for(int z = 0; z < arrayRows; z++)
    {
        visitedArray[z] = new bool[arrayRows];
        pointArray[z] = new Point[arrayRows];
    }
    
    //Setting all locations inside the visited array to false.
    for(int x = 0; x < arrayRows; x++)
    {
        for(int y = 0; y < arrayColumns; y++)
        {
            visitedArray[x][y] = false;
        }
    }
    
    //Creates the new linked list stack
    stack<Point> dfsStack;
    
    //pushing the mazeEntrance onto the stack
    dfsStack.push(mazeEntrance);
    
    //While loop to find the exit for the maze
    while(!dfsStack.empty())
    {
        //Gets the currentPoint location based on the front location in the queue
        currentPoint = dfsStack.top();
        testPoint = dfsStack.top();
        
        //Checking the north coordinate, if spot is visited, and if it is a wall
        if( currentPoint.y < arrayRows &&
           currentPoint.x - 1 < arrayColumns &&
           currentPoint.y >= 0 &&
           currentPoint.x - 1 >= 0 &&
           visitedArray[currentPoint.x - 1][currentPoint.y] == false &&
           mazeArray[currentPoint.x - 1][currentPoint.y] != 'W')
        {
            //Checking to see if the exit is at this location
            if(currentPoint.x - 1 == mazeExit.x && currentPoint.y == mazeExit.y)
            {
                //Setting found bool to true and breaking out of the loop
                found = true;
                pathTakenArray[mazeExit.x][mazeExit.y] = '*';
                break;
            }
            
            //Setting the temporary location from the currentPoint locaion
            tempPoint.x = currentPoint.x - 1;
            tempPoint.y = currentPoint.y;
            
            //Adding the temporary point to the queue
            dfsStack.push(tempPoint);
            
            //Setting the currentPoint location in the visitedArray to true
            visitedArray[currentPoint.x - 1][currentPoint.y] = true;
            
            //Setting the pointArray location to the data of the currentPoint
            pointArray[currentPoint.x - 1][currentPoint.y] = currentPoint;
            
            //Reseting the counter to 0;
            counter = 0;
        }
        
        //Checking the east coordinate, if spot is visited, and if it is a wall
        if( currentPoint.y + 1 < arrayColumns &&
           currentPoint.x < arrayRows &&
           currentPoint.y + 1 >= 0 &&
           currentPoint.x >= 0 &&
           visitedArray[currentPoint.x][currentPoint.y + 1] == false &&
           mazeArray[currentPoint.x][currentPoint.y + 1] != 'W')
        {
            //Checking to see if the exit is at this location
            if(currentPoint.x == mazeExit.x && currentPoint.y + 1 == mazeExit.y)
            {
                //Setting found bool to true and breaking out of the loop
                found = true;
                pathTakenArray[mazeExit.x][mazeExit.y] = '*';
                break;
            }
            
            //Setting the temporary location from the currentPoint locaion
            tempPoint.x = currentPoint.x;
            tempPoint.y = currentPoint.y + 1;
            
            //Adding the temporary point to the queue
            dfsStack.push(tempPoint);
            
            //Setting the currentPoint location in the visitedArray to true
            visitedArray[currentPoint.x][currentPoint.y + 1] = true;
            
            //Setting the pointArray location to the data of the currentPoint
            pointArray[currentPoint.x][currentPoint.y + 1] = currentPoint;
            
            //Reseting the counter to 0;
            counter = 0;
        }
        
        //Checking the west coordinate, if spot is visited, and if it is a wall
        if( currentPoint.y - 1 < arrayColumns &&
           currentPoint.x < arrayRows &&
           currentPoint.y - 1 >= 0 &&
           currentPoint.x >= 0 &&
           visitedArray[currentPoint.x][currentPoint.y - 1] == false &&
           mazeArray[currentPoint.x][currentPoint.y - 1] != 'W')
        {
            //Checking to see if the exit is at this location
            if(currentPoint.x == mazeExit.x && currentPoint.y + 1 == mazeExit.y)
            {
                //Setting found bool to true and breaking out of the loop
                found = true;
                pathTakenArray[mazeExit.x][mazeExit.y] = '*';
                break;
            }
            
            //Setting the temporary location from the currentPoint locaion
            tempPoint.x = currentPoint.x;
            tempPoint.y = currentPoint.y - 1;
            
            //Adding the temporary point to the queue
            dfsStack.push(tempPoint);
            
            //Setting the currentPoint location in the visitedArray to true
            visitedArray[currentPoint.x][currentPoint.y - 1] = true;
            
            //Setting the pointArray location to the data of the currentPoint
            pointArray[currentPoint.x][currentPoint.y - 1] = currentPoint;
            
            //Reseting the counter to 0;
            counter = 0;
        }
        
        //Checking the south coordinate, if spot is visited, and if it is a wall
        if( currentPoint.y < arrayRows &&
           currentPoint.x + 1 < arrayColumns &&
           currentPoint.y >= 0 &&
           currentPoint.x + 1 >= 0 &&
           visitedArray[currentPoint.x + 1][currentPoint.y] == false &&
           mazeArray[currentPoint.x + 1][currentPoint.y] != 'W')
        {
            //Checking to see if the exit is at this location
            if(currentPoint.x + 1 == mazeExit.x && currentPoint.y == mazeExit.y)
            {
                //Setting found bool to true and breaking out of the loop if exit is found
                found = true;
                pathTakenArray[mazeExit.x][mazeExit.y] = '*';
                break;
            }
            
            //Setting the temporary location from the currentPoint locaion
            tempPoint.x = currentPoint.x + 1;
            tempPoint.y = currentPoint.y;
            
            //Adding the temporary point to the queue
            dfsStack.push(tempPoint);
            
            //Setting the currentPoint location in the visitedArray to true
            visitedArray[currentPoint.x + 1][currentPoint.y] = true;
            
            //Setting the pointArray location to the data of the currentPoint
            pointArray[currentPoint.x + 1][currentPoint.y] = currentPoint;
            
            //Reseting the counter to 0;
            counter = 0;
        }
        
        //If the testPoint is equal to the currentPoint being checked inside the while loop,
        //and if the while loop as iterated 3 times with the same point, pops the top off
        //the stack and continues the while loop until the exit is found.
        //This insures that the maze never gets stuck.
        if(testPoint.x == currentPoint.x && testPoint.y == currentPoint.y && counter == 3)
        {
            dfsStack.pop();
            counter = 0;
        }
        
        //Increminting the counter for the loop.
        counter++;
    }
    
    //backtracking to add '*' to the shortest path
    while (mazeArray[arrayRows][arrayColumns] != mazeArray[mazeEntrance.x][mazeEntrance.y])
    {
        mazeArray[currentPoint.x][currentPoint.y] = '*';
        pathTakenArray[currentPoint.x][currentPoint.y] = '*';
        currentPoint = pointArray[currentPoint.x][currentPoint.y];
        
        //If the currentPoint is the entrance point, start with an arrow.
        if (currentPoint.x == mazeEntrance.x && currentPoint.y == mazeEntrance.y)
        {
            pathTakenArray[currentPoint.x][currentPoint.y] = '>';
            break;
        }
    }
    
    //Stopping timer
    auto end = chrono::system_clock::now();
    
    //Getting the total elapsed time: End time - Start time = Total time elapsed.
    chrono::duration<double> elapsedTime = (end - start);
    
    //Notifying user of the time it took to complete the sorting.
    cout << "\nDepth First Search Elapsed time: " << elapsedTime.count() << "s\n\n";
    outputFile << "\nDepth First Search Elapsed time: " << elapsedTime.count() << "s\n\n";
    
    //Printing only the path
    cout << "This is the path taken.\n";
    outputFile << "This is the path taken.\n";
    arrayTextPrinter(pathTakenArray, outputFile);
    cout << endl << endl;
    outputFile << endl << endl;
    
    //Printing the combined path with maze
    cout << "This is the path inside the maze.\n";
    outputFile << "This is the path inside the maze.\n";
    arrayTextPrinter(mazeArray, outputFile);
    cout << endl << endl;
    outputFile << endl << endl;
    
    //Deallocating the memory on the heap for the arrays
    for (int i = 0; i > arrayRows; i++)
    {
        delete [] pointArray[i];
        delete [] visitedArray[i];
        
    }
    
    //Deallocating the 2D arrays
    delete [] pointArray;
    delete [] visitedArray;
}

//Function to check if the move in the search is a valid move.
//Move must be within bounds of the maze.
//Not less than value 0 and no more than value 10
bool validMove(int row, int col)
{
    //Returns true if row number and column number
    //is in the scope of the maze
    return (row >= 0) && (row < arrayRows) &&
    (col >= 0) && (col < arrayColumns);
}

//-------------------------------------------------------------------------------------------------
//breadthFirstSearch - This function used a Breadth First searching type function to find the end
//                     of the maze.
//--------------------------------------------------------------------------------------------------
void breadthFirstSearch(char mazeArray[arrayRows][arrayColumns], fstream& outputFile)
{
    //Starting timer
    auto start = chrono::system_clock::now();
    
    //Array to hold only the path taken.
    char pathTakenArray[arrayRows][arrayColumns];
    memset(pathTakenArray, ' ', sizeof pathTakenArray);
    
    //Array to overlay the path taken ontop of the original maze
    char pathInMaze[arrayRows][arrayColumns];
    for(int d = 0; d < arrayRows; d++)
    {
        for(int f = 0; f < arrayColumns; f++)
        {
            pathInMaze[d][f] = mazeArray[d][f];
        }
    }

    //Created the visited array
    bool visited[arrayRows][arrayColumns];
    memset(visited, false, sizeof visited);
    
    //Setting the entrance location to true.
    visited[mazeEntrance.x][mazeEntrance.y] = true;
    
    //Creating the queue
    queue<Node> BFSqueue;
    
    //Setting the start of the Node to the entrance of the maze
    //and then pushing that node onto the queue
    Node entrance = {mazeEntrance, {-1,-1}, 0};
    BFSqueue.push(entrance);
    
    //Header for the display and the output file
    cout << "\t\tBeardth First Search\n";
    cout << "\t\t____________________\n";
    outputFile << "\t\tBreadth First Search\n";
    outputFile << "\t\t____________________\n";
    
    //While loop for the BFS starting from the mazeEntrance Point
    while (!BFSqueue.empty())
    {
        //Setting the 4 possible moves that are move-able from each point.
        //North, East, South, West
        int rowNumber[] = {-1, 0, 1, 0};
        int colNumber[] = {0, 1, 0, -1};
        
        //Setting the currentNode we are checking to the front of the queue
        //Then getting the coordinated of that point from its set location
        Node currentNode = BFSqueue.front();
        Point currentPoint = currentNode.location;
        
        //Checking to see if we have reached the exit of the maze
        //If it is, return the number of moves.
        if (currentPoint.x == mazeExit.x && currentPoint.y == mazeExit.y)
        {
            //Stopping timer
            auto end = chrono::system_clock::now();
            
            //Getting the total elapsed time: End time - Start time = Total time elapsed.
            chrono::duration<double> elapsedTime = (end - start);
            
            //Notifying user of the time it took to complete the sorting.
            cout << "\nBreadth First Search Elapsed time: " << elapsedTime.count() << "s\n\n";
            outputFile << "\nBreadth First Search Elapsed time: " << elapsedTime.count() << "s\n\n";
            
            cout << "Total number of moves: " << currentNode.distance << endl << endl;
            
            arrayTextPrinter(pathInMaze, outputFile);
        }
        
        //If the currentPoint we are checking is not the exit of the maze
        //pop off the front cell in the queue and queue its possible moves.
        BFSqueue.pop();
        
        for (int move = 0; move < 4; move++)
        {
            //Checking the next move from our possible moves
            int row = currentPoint.x + rowNumber[move];
            int col = currentPoint.y + colNumber[move];
            
            //If the move is a valid move(withing the scope of the maze
            //and if the space is not visited already and if the point
            //is not a wall
            if(validMove(row, col) &&
               !visited[row][col] &&
               mazeArray[row][col] != 'W' )
            {
                //Marking the point as visited
                visited[row][col] = true;
                
                //Creating a temp node to store the row and column of
                //the next move, and incrementing the number of moves
                //we have made by 1
                Node temp = {{row,col}, {currentPoint.x, currentPoint.y}, currentNode.distance + 1};
                cout << "checking (" << temp.location.x << "," << temp.location.y << ") with parent (" << currentPoint.x << "," << currentPoint.y << ")" << " move # " << currentNode.distance + 1 << endl;
                
                //Printing the path
                if(temp.distance == currentNode.distance + 1 )
                {
                    pathInMaze[currentPoint.x][currentPoint.y] = '*';
                    pathTakenArray[currentPoint.x][currentPoint.y] = '*';
                }
                
                //Pushing the temp node onto the queue
                BFSqueue.push(temp);
            }
        }
    }
}
