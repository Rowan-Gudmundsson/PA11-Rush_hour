#include <iostream>
#include "Rush.h"
#include <map>
#include <queue>
#include <string>

using namespace std;

Board::Board(){
	totalCars = 0;
}

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

bool Board::forward(int car){
	if(boards[car].direction == 'H'){
		if(boards[car].col + boards[car].length < BOARD_SIZE){
			if(isMove(boards[car].row,boards[car].col + boards[car].length)){
				boards[car].col++;
				return 1;
			}
		}
	}else{
		if(boards[car].row + boards[car].length < BOARD_SIZE){
			if(isMove(boards[car].row + boards[car].length,boards[car].col)){
				boards[car].row++;
				return 1;
			}
		}
	}
	return 0;
}

bool Board::backward(int car){

}

bool Board::isMove(int row, int col){
	for(int i = 0; i < totalCars; i++){
		for(int j = 0; j < boards[i].length; j++){
			if(boards[i].direction == 'H'){
				if(boards[i].row == row && (boards[i].col+j) == col){
					return 0;
				}
			}else{
				if((boards[i].row+j) == row && boards[i].col == col){
					return 0;
				}
			}
		}
	}
	return 1;
}

int Board::solveIt(int cars){
	int moves = 0;
	Board board;
	board.insert(cars);
	map<Board,int> graph;
	//graph.insert(pair<Board,int>(board,moves));

/*
	while(moves < 5){
		moves = graph.find(board)->second;
		if(board.isSolved()){
			return moves;
		}
		for(int i = 0; i < totalCars; i++){
			if(board.forward(i)){
				if(graph.count(board) == 0){
					graph.insert(pair<Board,int>(board,moves+1));
				}
			}
		}
	}
	*/
}

bool Board::isSolved() const{
	return (boards[0].col + boards[0].length) == 6;
}

void Board::clear(){
	totalCars = 0;
}