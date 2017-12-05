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
#include "Rush.h"
#include "Timer.h"
using namespace std;

//  Global Constants  //////////////////////////////////////////////////////////
//const int MAX_CARS = 18; /**< The maximum number of cars allowed for the game */

//  Function Prototypes  ///////////////////////////////////////////////////////
int solveIt(Board &gameBoard);

//  Main Function  /////////////////////////////////////////////////////////////
int main()
{
   
   // initialize variables
   int numCars, scenario, numMoves;
   
   // initialize game board
   
   // get input number of cars for first scenario (prime loop)
   cin >> numCars;

   // loop until user ends program (inputs 0 or > MAX_CARS for number of cars)
   // increment scenario number
   for(scenario = 1; numCars > 0 && numCars <= MAX_CARS; scenario++)
   {
      Timer t;
      Board gameBoard;
      double totalT= 0;

      // load cars into board
      gameBoard.loadCars(numCars);
      t.start();
      // solve
      numMoves = gameBoard.solveIt();
      t.stop();
      totalT+= t.getElapsedTime();
      // print results
      cout << "Scenario " << scenario << " requires " << numMoves << " moves" << endl;
      // get input number of cars for next scenario
      cout << totalT << std::endl;
      cin >> numCars;
   }
   

   // end program
   return 0;
}