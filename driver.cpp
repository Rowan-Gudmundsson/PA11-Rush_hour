//  Program Description/Support  ///////////////////////////////////////////////
/**
@file main.cpp
@author Ashlee Ladouceur
@author Rowan Gudmundsson
@author Spencer Rohlfing
@version 1.0
@brief This program will solve the game Rush Hour. It calculates
the smallest number of moves required to solve input traffic configurations.
A branch and bound method is implemented to calculate complex solutions
efficiently.
@details Game boards of any difficulty can be solved, as long as they have less
than 18 cars. Game boards that use a truck as the main car can also be solved.
@date Sunday, December 3rd, 2017
*/

/**
@mainpage
This program will solve the game Rush Hour. It calculates
the smallest number of moves required to solve input traffic configurations.
A branch and bound method is implemented to calculate complex solutions
efficiently.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of our knowledge.
*/

//  Header Files  //////////////////////////////////////////////////////////////
#include <iostream>
#include <queue>
#include <map>
#include <ctime>
#include "rush.h"
#include "timer.h"
using namespace std;

//  Global Constants  //////////////////////////////////////////////////////////
const int MAX_CARS = 18; /**< The maximum number of cars allowed for the game */

//  Function Prototypes  ///////////////////////////////////////////////////////
int solveIt(Board &gameBoard);

//  Main Function  /////////////////////////////////////////////////////////////
int main()
{
   Timer t;

   // initialize variables
   int numCars, scenario, numMoves;
   double totalT= 0;

   // initialize game board
   Board gameBoard;

   // get input number of cars for first scenario (prime loop)
   cin >> numCars;

   // loop until user ends program (inputs 0 or > MAX_CARS for number of cars)
   // increment scenario number
   for(scenario = 1; numCars > 0 && numCars <= MAX_CARS; scenario++)
   {
      // load cars into board
      gameBoard.loadCars(numCars);
      t.start();
      // solve
      numMoves = solveIt(gameBoard);
      t.stop();
      totalT+= t.getElapsedTime();
      // print results
      cout << "Scenario " << scenario << " requires " << numMoves << " moves" << endl;
      // get input number of cars for next scenario
      cin >> numCars;
   }
   cout << totalT;

   // end program
   return 0;
}

//  Supporting Function Implementation  ////////////////////////////////////////

/**
 * This function will find the solution to the input game board, using a
 * breadth-first search with pruning (branch and bound).
 *
 * This function contains a loop that will check if a solution has been found,
 * and if so, the number of moves required to solve is returned. If a solution
 * was not found, the function attempts to move each car (branch) and see if a
 * solution was found resulting from the latest move. The function will not
 * continue searching for solutions on a game board that has already been
 * searched (bound).
 *
 * @param gameBoard   the game board to solve
 * @return This function will return the least number of moves required to solve
 * the game. If a solution is not found, -1 is returned.
 * @exception None
 *
 */
int solveIt(Board &gameBoard)
{
   // initialize function
   // initialize variables
   int numCars= gameBoard.getNumCars();
   int numMoves= 0;

   // initialize todo queue, and history map
   queue<Board> todo;
   map<Board,int> history;

   // insert first board into todo, and history with numMoves
   todo.push(gameBoard);
   history.insert(pair<Board,int>(gameBoard, numMoves));

   // loop while todo is not empty (solution still possible)
   while(!todo.empty())
   {
      // load board from todo
      gameBoard= todo.front();
      todo.pop();
      // get number of moves for loaded board (second of pair)
      numMoves= history.find(gameBoard)->second;
      // if board is solved
      if(gameBoard.solved())
      {
         // return number of moves
         return numMoves;
      }
      // loop for numCars
      for(int j= 0; j < numCars; j++)
      {
         // if car at index can move forward
         if(gameBoard.moveForward(j))
         {
            // if board is not in history (bound)
            if(history.count(gameBoard) == 0)
            {
               // insert board into todo, and history with numMoves + 1
               todo.push(gameBoard);
               history.insert(pair<Board,int>(gameBoard, numMoves + 1));
            }
            // move car back
            gameBoard.moveBack(j);
         }
         // if car at index can move back
         if(gameBoard.moveBack(j))
         {
            // if board is not in history (bound)
            // "history.find( gameBoard ) == history.end" not working
            if(history.count(gameBoard) == 0)
            {
               // insert board into todo, and history with numMoves + 1
               todo.push(gameBoard);
               history.insert(pair<Board,int>(gameBoard, numMoves + 1));
            }
            // move car forward
            gameBoard.moveForward(j);
         }
      }
   }
   // return -1 for not solved
   return -1;
}
