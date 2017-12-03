#include <iostream>
#include "Rush.h"
#include <map>

using namespace std;

Board::Board():totalCars(0){}
Board::~Board(){
	delete [] boards;
	boards = NULL;
}

void Board::insert(int cars){
	totalCars = cars;
	boards = new Vehicle [cars];
	for(int i = 0; i < cars; i++){
		cin >> boards[i].length
			>> boards[i].direction
			>> boards[i].row
			>> boards[i].col;
	}
}

int Board::solveIt(int cars){
	Board board;
	board.insert(cars);
	board.showStructure();
}

void Board::clear(){
	totalCars = 0;
}

void Board::showStructure() const{
	for(int i = 0; i < totalCars; i++){
		cout << boards[i].length << " "
		<< boards[i].direction << " "
		<< boards[i].row << " "
		<< boards[i].col << " "
		<< endl;
	}
}