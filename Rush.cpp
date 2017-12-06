/**
@file Rush.cpp
*/

//  Header Files  //////////////////////////////////////////////////////////////
#include "Rush.h"

/// since history is a static member variable, must be instatiated before being used
std::map<std::string, int> Board::history;


/**
 * Parameterized constructor
 * will setup a default board. It will set the total cars to 0.
 * @param defaultMax the number of cars
 */
Board::Board(int defaultMax) : totalCars(0) {

	boards = new Vehicle[defaultMax];
}

/**
 * Copy constructor
 * will create an exact copy of a board. It will call the assignment operator
 * function.
 * @param other reference to the board we will copy from
 */
Board::Board(const Board& other) : boards(NULL) {

	(*this) = other;
}

/**
 * Destructor
 * will delete all allocated memory of the board. Set boards to NULL.
 */
Board::~Board() {

	delete [] boards;
	boards = NULL;
}

/**
 * Assignment operator=
 * will set one board equal to another board. First it will check if the
 * board exists, if so delete and create a new board with the same size
 * as the board we are copying from. Set the total cars, then set each
 * element in the array to the other board's array. 
 * @param other reference to the board we will copy from
 * @return the reference to the board.
 */
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

/**
 * Loadcars 
 * will read in from the keyboard and store the information into struct
 * Vehicle boards. It will store the total number of cars, the length of
 * each car, the direction the car is facing, and the postition(row,col) 
 * that the car is located in.
 * @param numCars number of cars
 */
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

/**
 * Moveforward
 * will move a car forward if possible. First it will check what direction
 * the car is facing, either horizontal or verticle. Then it will check if
 * the position it will be moving will not fall off the board or run into 
 * a wall. Then it will then call isMove() to check that it won't run into
 * another car. Then it will increase it's movement position by 1.
 * @param  car car number
 * @return true or false.
 */
bool Board::moveForward(int car) {

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

/**
 * Movebackwards
 * will move a car backwards if possible. First it will check what direction
 * the car is facing, either horizontal or verticle. Then it will check if
 * the position it will be moving will not fall off the board or run into 
 * a wall. Then it will then call isMove() to check that it won't run into
 * another car. Then it will decrease it's movement position by 1.
 * @param  car car number
 * @return true or false.
 */
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

/**
 * Ismove
 * will check if a car can move forward. It will first find what direciton
 * it is facing, then it will iterate through the cars to make sure that
 * the car won't run into other cars. If so return false.
 * @param  row x position
 * @param  col y position
 * @return true or false
 */
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

/**
 * Solvedit
 * will solve the rushhour board. It will take the current board and 
 * push it onto a queue as well as insert the board into a map using
 * a string as the key and number of moves as the value. While the queue
 * greater than 0, it will first pop a board from the queue and do tests 
 * on it. It will find the number of moves and check if board is solved. If
 * not, the board will go into a loop where it will try to move a car forward
 * or backwards as long as it hasn't been in the map yet. If not, then insert
 * that board into the queue to do tests later on.
 * @return number of moves or -1 if didn't solve.
 */
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

/**
 * Solved
 * checks if the first car is at the edge of the board.
 * @return true or false
 */
bool Board::solved() const{
	return (boards[0].col + boards[0].length) == 6;
}

/**
 * Clear
 * resets the total number of cars.
 */
void Board::clear(){
	totalCars = 0;
}


/**
 * \brief Converts the board to a string of characters where each character is an encoding of a vehicle
 *
 * encodes a vehicle to one byte of information. First bit is whether the vehicle is vertical or
 * horizontal, next 3 bits are the row, next 3 are the column and the last bit is 0 if the car
 * is of length 2, 1 if the car is of length 3
 *
 * @param None
 * @return The board as a string
 * @pre board must have Vehicles in them and each vehicle must have all appropriate data
 * @post used to uniquely identify a board, used for mapping and remembering the board
 **/
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

/**
 * << operator
 * is used to print out the current information of the board. This was
 * used for debugging and is not used in the final product.
 */
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