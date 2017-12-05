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
#include <map>
#include <queue>
#include <string>

const int BOARD_SIZE = 6;
const int MOVE_CAP = 10;
const int MAX_CARS = 18;

#define VH_BIT 1 << 7

class Board{
public:
	Board(int defaultMax = MAX_CARS);
	Board(const Board&);
	~Board();

	Board& operator = (const Board&);

	void clear();
	void loadCars(int);
	int solveIt();
	bool moveForward(int);
	bool moveBack(int);
	bool isMove(int row, int col);
	bool solved() const;
	std::string toString() const;

	friend std::ostream& operator << (std::ostream&, const Board&);
	
private:

	struct Vehicle {

		int row;
		int col;
		char direction;
		int length;
		char name;
	};

	static std::map<std::string, int> history;

	std::queue<Board> todo;

	Vehicle* boards;
	int totalCars;
};

#endif //RUSH_H
