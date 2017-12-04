#ifndef RUSH_H
#define RUSH_H

using namespace std;

const int BOARD_SIZE = 6;

class Board{
public:
	Board();
	~Board();

	//bool operator<(const Board &other) const{
	//	return boards < other.boards;
	//}
	void clear();
	void insert(int cars);
	int solveIt(int cars);
	bool forward(int carNumber);
	bool backward(int carNumber);
	bool isMove(int row, int col);
	bool isSolved() const;

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
};

#endif