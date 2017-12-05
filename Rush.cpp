#include "Rush.h"

std::map<std::string, int> Board::history;

Board::Board(int defaultMax) : totalCars(0) {

	boards = new Vehicle[defaultMax];
}

Board::Board(const Board& other) {

	boards = NULL;
	(*this) = other;
}

Board::~Board(){
	delete [] boards;
	boards = NULL;
}

Board& Board::operator = (const Board& other) {

	if(boards != NULL)	
		delete [] boards;

	boards = new Vehicle[other.totalCars];
	totalCars = other.totalCars;

	for(int i = 0; i < other.totalCars; ++i) {

		boards[i] = other.boards[i];
	}

	return (*this);
}
void Board::loadCars(int numCars){

	if(boards != NULL)
		delete [] boards;

	boards = new Vehicle[numCars];

	totalCars = numCars;

	for(int i = 0; i < numCars; i++) {
		std::cin >> boards[i].length
			>> boards[i].direction
			>> boards[i].row
			>> boards[i].col;
	}
}

bool Board::moveForward(int car){

	//Board newBoard = (*this);

	if(boards[car].direction == 'H'){

		if(boards[car].col + boards[car].length < BOARD_SIZE){

			if(isMove(boards[car].row,boards[car].col + boards[car].length)){

				boards[car].col++;
				return true;
			}
		}
	}
	else {

		if(boards[car].row + boards[car].length < BOARD_SIZE){

			if(isMove(boards[car].row + boards[car].length,boards[car].col)){

				boards[car].row++;
				return true;
			}
		}
	}
	return false;
}

bool Board::moveBack(int car){

	//Board newBoard = (*this);

	if(boards[car].direction == 'H'){

		if(boards[car].col - 1 >= 0){

			if(isMove(boards[car].row,boards[car].col - 1)){

				boards[car].col--;
				return true;
			}
		}
	}
	else {

		if(boards[car].row - 1 >= 0){

			if(isMove(boards[car].row - 1 ,boards[car].col)){

				boards[car].row--;
				return true;
			}
		}
	}

	return false;
}

bool Board::isMove(int row, int col){

	for(int i = 0; i < totalCars; i++){
		for(int j = 0; j < boards[i].length; j++){
			if(boards[i].direction == 'H'){
				if(boards[i].row == row && (boards[i].col+j) == col){
					return false;
				}
			}else{
				if((boards[i].row+j) == row && boards[i].col == col){
					return false;
				}
			}
		}
	}
	return true;
}

int Board::solveIt()
{
   // initialize function
   // initialize variables
   int numMoves = 0;

   Board& gameBoard = (*this);
   // insert first board into todo, and history with numMoves
   todo.push(gameBoard);
   history.insert(std::pair<std::string, int>(gameBoard.toString(), numMoves));

   // loop while todo is not empty (solution still possible)
   while(todo.size() > 0)
   {
      // load board from todo
      gameBoard = todo.front();
      todo.pop();

      // get number of moves for loaded board (second of pair)
      numMoves = history.find(gameBoard.toString())->second;
      // if board is solved
      if(gameBoard.solved())
      {
         // return number of moves
         return numMoves;
      }
      // loop for numCars
      for(int j= 0; j < totalCars; j++)
      {
         // if car at index can move forward
         if(gameBoard.moveForward(j))
         {
            // if board is not in history (bound)
            //if(history.count(gameBoard.toString()) == 0)
            if(!gameBoard.solved()) {
            	if(history.find(gameBoard.toString()) == history.end())
            	{
               		// insert board into todo, and history with numMoves + 1
               		todo.push(gameBoard);
               		history.insert(std::pair<std::string ,int>(gameBoard.toString(), numMoves + 1));
            	}
        	}
        	else
        		return numMoves + 1;
            // move car back
            gameBoard.moveBack(j);
         }
         // if car at index can move back
         if(gameBoard.moveBack(j))
         {
            // if board is not in history (bound)
            // "history.find( gameBoard ) == history.end" not working
            if(!gameBoard.solved()) {
            	
            	if(history.find(gameBoard.toString()) == history.end())
            	{
               		// insert board into todo, and history with numMoves + 1
               		todo.push(gameBoard);
               		history.insert(std::pair<std::string, int>(gameBoard.toString(), numMoves + 1));
            	}
        	}
        	else
        		return numMoves + 1;
            // move car forward
            gameBoard.moveForward(j);
         }
      }
   }
   // return -1 for not solved
   return -1;
}

bool Board::solved() const{
	return (boards[0].col + boards[0].length) == 6;
}

void Board::clear(){
	totalCars = 0;
}

std::string Board::toString() const {

	std::string boardyString;
	char data;

	for(int i = 0; i < totalCars; ++i) {

		data = 0;
		if(boards[i].direction == 'V')
			data |= VH_BIT;
		if(boards[i].length == 3)
			data |= 1;

		data |= boards[i].col << 4;
		data |= boards[i].row << 1;

		boardyString += data;
	}

	return boardyString;
}

std::ostream& operator << (std::ostream& strm, const Board& board) {

	//strm << board.totalCars << std::endl;

	for(int i = 0; i < board.totalCars; ++i) {

		strm << "(" << board.boards[i].row << ", " << board.boards[i].col << ") ";
	}
	strm << std::endl;
	if(board.solved())
		strm << "Solved.";
	else
		strm << "Not Solved.";

	return strm;
}