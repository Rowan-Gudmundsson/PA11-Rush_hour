//  Header Description/Support  ////////////////////////////////////////////////
/**
@file rush.h
@author Ashlee Ladouceur
@author Rowan Rundmunsson
@author Spencer Rohlfing
*/
#ifndef RUSH_H
#define RUSH_H

#include <iostream>
using namespace std;

//  Car Class  /////////////////////////////////////////////////////////////////

class Car
{
   public:
      bool operator<(const Car& other) const;
      bool operator!=(const Car& other) const;
      friend istream& operator>>(istream &is, Car &inCar);
      int length;
      char orientation;
      int row;
      int col;
};

//  Board Class  ///////////////////////////////////////////////////////////////
class Board
{
   public:
      Board();
      Board(const Board &other);
      Board& operator=(const Board& other);
      ~Board();

      void loadCars(int inNumCars);
      int getNumCars() const;
      void clear();
      bool moveForward(int index);
      bool moveBack(int index);
      bool isClearSpace(int row, int col) const;
      bool solved() const;
      bool operator<(const Board& other) const;

   private:
      Car *cars;
      int numCars;
};
#endif
