#ifndef RUSH_H
#define RUSH_H

using namespace std;


class Board{
public:
	Board();
	~Board();

	void clear();
	void insert(int cars);
	int solveIt(int cars);
	bool isSolved() const;
	void showStructure() const;

private:
	class Vehicle{
	public:
		int row;
		int col;
		char direction;
		int length;
		char name;
	};
	Vehicle *boards;
	int totalCars;
	/*
	bool moveForward(Board &board, Vehicle test);
	bool moveBackward(Board &board, Vehicle test);
	void solveIt(Board &board,int &cap, int moves, bool &solved);
	bool win(Board board);
	Vehicle array[6][6];
	*/
};

#endif