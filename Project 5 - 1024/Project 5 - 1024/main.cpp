//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
/*  Running program looks like:

	 Dale Reed
	 UIC CS 141, Spring 2019
	 Welcome to 1024.
	 This program is based off of Gabriele Cirulli's game online at
	 bit.ly/great2048

	 For each move enter a direction as a letter key, as follows:
		 W
	   A S D
	 where A=left,W=up, D=right and S=down.

	 After a move, when two identical valued tiles come together they
	 join to become a new single tile with the value of the sum of the
	 two originals. This value gets added to the score.  On each move
	 one new randomly chosen value of 2 or 4 is placed in a random open
	 square.  User input of x exits the game.

	 Game ends when you reach 1024.

	 Score: 0
	 .     4     .     .

	 .     .     .     .

	 .     .     4     .

	 .     .     .     .

	 1. Your move: a

	 Score: 0
	 4     .     .     .

	 .     .     .     .

	 4     .     .     .

	 .     .     2     .

	 2. Your move: a
	 .
	 .
	 .
*/

#include <iostream>     // For cin, cout, endl
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
using namespace std;    // So we don't need std:: in front of every cin, cout, and endl

const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
	cout << "Welcome to 1024. \n"
		<< "  \n"
		<< "For each move enter a direction as a letter key, as follows: \n"
		<< "    W    \n"
		<< "  A S D  \n"
		<< "where A=left,W=up, D=right and S=down. \n"
		<< "  \n"
		<< "After a move, when two identical valued tiles come together they    \n"
		<< "join to become a new single tile with the value of the sum of the   \n"
		<< "two originals. This value gets added to the score.  On each move    \n"
		<< "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
		<< "square.  User input of x exits the game.                            \n"
		<< "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece(int board[], int squaresPerSide)
{
	// Randomly choose a piece to be placed (2 or 4)
	int pieceToPlace = 2;
	if (rand() % 2 == 1) {
		pieceToPlace = 4;
	}

	// Find an unoccupied square that currently has a 0
	int index;
	do {
		index = rand() % (squaresPerSide*squaresPerSide);
	} while (board[index] != 0);

	// board at position index is blank, so place piece there
	board[index] = pieceToPlace;
}//end placeRandomPiece()

//-----------------------------------------------------------------------------------
void displayAsciiBoard(int board[], int squaresPerSide, int score)
{
	int i;
	cout << "Score: " << score << endl;
	cout << setw(8);
	for (i = 1; i < (squaresPerSide * squaresPerSide) + 1; i++)
	{

		if (board[i - 1] == 0)
		{
			cout << ".";
		}
		else
		{
			cout << board[i - 1];
		}
		if (i % squaresPerSide == 0)
		{
			cout << endl;
			if (i != squaresPerSide * squaresPerSide)
			{
				cout << "                   " << endl;
				cout << setw(8);
			}
		}
		else
		{
			cout << setw(6);
		}
	}
}

//-------------------------------------------------------------------------------------
// Initializes the board to 0
void initializeBoard(int board[], int squaresPerSide, int value)
{
	int i;
	for (i = 0; i < squaresPerSide * squaresPerSide; i++)
	{
		board[i] = value;
	}
}

//------------------------------------------------------------------------------------
// Creates a copy of the board
void copyBoard(int sourceBoard[], int board2[], int squaresPerSide)
{
	int i;
	for (i = 0; i < squaresPerSide * squaresPerSide; i++)
	{
		board2[i] = sourceBoard[i];
	}
}

//-------------------------------------------------------------------------------------
// Moves all pieces to the left
// User input is: 'a'
void slideLeft(int board[], int squaresPerSide, int &score)
{
	// Slide the values to the left
	for (int current = 0; current < squaresPerSide * squaresPerSide; current++)
	{
		if (board[current] != 0)
		{
			while (current % squaresPerSide != 0
				&& board[current - 1] == 0
				&& current <= squaresPerSide * squaresPerSide)
			{
				board[current - 1] = board[current];
				board[current] = 0;
				current -= (current + 1);
			}
		}
	}
	// If the adjacent values to the left are the same then merge
	for (int current = 0; current < squaresPerSide * squaresPerSide; current++)
	{
		if (board[current] == board[current - 1] && current % squaresPerSide != 0)
		{
			board[current - 1] += board[current];
			board[current] = 0;
			score += board[current - 1];
		}
	}
	// Shift values to the left again to avoid merging all values to the left if applicable
	for (int current = 0; current < squaresPerSide * squaresPerSide; current++)
	{
		if (board[current] != 0)
		{
			while (current % squaresPerSide != 0
				&& board[current - 1] == 0
				&& current <= squaresPerSide * squaresPerSide)
			{
				board[current - 1] = board[current];
				board[current] = 0;
				current -= (current + 1);
			}
		}
	}
}

//-------------------------------------------------------------------------------------
// Moves all pieces to the right
// User input is: 'd'
void slideRight(int board[], int squaresPerSide, int &score)
{
	int i, j;
	// Iterate through entire board. Values of i in this loop are 3,7,11,15
	for (i = squaresPerSide - 1; i < squaresPerSide * squaresPerSide; i = i + squaresPerSide)
	{
		for (j = i - 1; (j + 1) % squaresPerSide > 0; j--)
		{
			// Current value: starting at one value to the left of limit; Continues until next limit
			int current = j;
			// Limit value: edge case values on the right side: 3,7,11,15
			int limit = i;

			while (current < limit && board[current + 1] == 0)
			{
				// swap with the piece to the right
				board[current + 1] = board[current];
				board[current] = 0;
				current++;
			}

			// Check if the piece and its right neighbor are the same value.
			// If they are then add both values to the new index
			if (board[current + 1] == board[current] && board[current + 1] != 0 && current < limit)
			{
				board[current + 1] = board[current + 1] + board[current];
				board[current] = 0;
				score += board[current + 1];
				continue;
			}
		}
	}

}

//----------------------------------------------------------------------------------------------------
// Moves all pieces upward
// User input is: 'w'
void slideUp(int board[], int squaresPerSide, int &score)
{
	// Shift all values upward
	for (int current = 0; current < squaresPerSide * squaresPerSide; current++)
	{
		if (board[current] != 0)
		{
			while (current >= squaresPerSide
				&& board[current - squaresPerSide] == 0
				&& current <= squaresPerSide * squaresPerSide)
			{
				board[current - squaresPerSide] = board[current];
				board[current] = 0;
				current = current - (squaresPerSide + 1);
			}
		}
	}
	// If values upward are the same value then merge the values
	for (int current = 0; current < (squaresPerSide * squaresPerSide); current++)
	{
		if (board[current] == board[current - squaresPerSide] && current >= squaresPerSide)
		{
			board[current - squaresPerSide] += board[current];
			board[current] = 0;
			score += board[current - squaresPerSide];
		}
	}
	// Shift values upward again to avoid merging all values at once
	for (int current = 0; current < squaresPerSide * squaresPerSide; current++)
	{
		if (board[current] != 0)
		{
			while (current >= squaresPerSide
				&& board[current - squaresPerSide] == 0
				&& current <= squaresPerSide * squaresPerSide)
			{
				board[current - squaresPerSide] = board[current];
				board[current] = 0;
				current = current - (squaresPerSide + 1);
			}
		}
	}
}

//-------------------------------------------------------------------------------------
// Moves all pieces downward
// User input is: 's'
void slideDown(int board[], int squaresPerSide, int &score)
{
	// Slide the values of the board downward
	for (int current = (squaresPerSide * squaresPerSide - 1); current >= 0; current--)
	{
		if (board[current] != 0)
		{
			while (current < (squaresPerSide * squaresPerSide - squaresPerSide)
				&& board[current + squaresPerSide] == 0
				&& current <= squaresPerSide * squaresPerSide)
			{
				board[current + squaresPerSide] = board[current];
				board[current] = 0;
				current = current + (squaresPerSide + 1);
			}
		}
	}
	// If any adjacent values when going down are the same, then merge
	for (int current = (squaresPerSide * squaresPerSide - 1); current >= 0; current--)
	{
		if (board[current] == board[current + squaresPerSide]
			&& current < (squaresPerSide * squaresPerSide - squaresPerSide))
		{
			board[current + squaresPerSide] += board[current];
			board[current] = 0;
			score += board[current + squaresPerSide];
		}
	}
	// Shift downward again to avoid merging all values at once
	for (int current = (squaresPerSide * squaresPerSide - 1); current >= 0; current--)
	{
		if (board[current] != 0) {
			while (current < (squaresPerSide * squaresPerSide - squaresPerSide)
				&& board[current + squaresPerSide] == 0
				&& current <= squaresPerSide * squaresPerSide)
			{
				board[current + squaresPerSide] = board[current];
				board[current] = 0;
				current = current + (squaresPerSide + 1);
			}
		}
	}
}


//--------------------------------------------------------------------------------------
// Sets the piece value where user wants
void setPiece(int board[], int index, int value)
{
	board[index] = value;
}

//----------------------------------------------------------------------------------------
// Return the exponent value
int raiseToThePowerOf(int square, int powerOf)
{
	int exponent = 1;
	for (int i = 1; i <= powerOf; i++)
	{
		exponent = exponent * square;
	}
	return exponent;
}

//-----------------------------------------------------------------------------------------
// Tests to see if the game has every piece filled
// If it does then the function will return true
bool gameNotFinished(int board[], int squaresPerSide)
{
	// Check if the board is full
	int notZero = 0;   // Used to count if there are any empty values
	for (int i = 0; i < squaresPerSide * squaresPerSide; i++)
	{
		if (board[i] != 0)
		{
			++notZero;
		}

	}

	// If full then end the game
	if (notZero == squaresPerSide * squaresPerSide)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------
int main()
{
	int score = 0;
	int squaresPerSide = 4;        // User will enter this value.  Set default to 4
	int board[MaxBoardSize * MaxBoardSize];          // space for largest possible board
	int previousBoard[MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
													  //    if a move changed the board.

	int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
	char userInput = ' ';                  // handles user input
	int move = 1;                          // user move counter

	int userChoiceIndex;   // setPiece value: Used for choice of index
	int userValue;        // setPiece value: Used ofr choice of value in userChoiceIndex

	int powerOf;  // Used to determine the the power maxTileValue will be raised to

	// Display the instructions of the game
	displayInstructions();

	// Get the board size, create and initialize the board, and set the max tile value depending on board size
	// Initialize the board
	initializeBoard(board, squaresPerSide, 0);

	// Place the initial starting random pieces
	placeRandomPiece(board, squaresPerSide);
	placeRandomPiece(board, squaresPerSide);

	// Display at what value does the game end at
	cout << "Game ends when you reach " << maxTileValue << "." << endl << endl;

	// Infinite loop to run program until user selects exit, board is full, or max tile value is reached
	// Iterates until all pieces on the board are non-zero
	while (gameNotFinished(board, squaresPerSide) != true)
	{
		// Display the text-based board
		displayAsciiBoard(board, squaresPerSide, score);

		// Make a copy of the board.  After we then attempt a move, the copy will be used to
		// verify that the board changed, which only then allows randomly placing an additional
		// piece on the board and updating the move number.
		copyBoard(board, previousBoard, squaresPerSide);

		// Prompt for and handle user input
		cout << move << ". Your move: " << endl << endl;
		cin >> userInput;
		switch (userInput) {
			// Case for exiting the game
		case 'x':
			cout << endl << "Thanks for playing. Exiting program... \n";
			exit(0);
			break;
			// Case for individually setting a value on the board
		case 'p':
			cin >> userChoiceIndex >> userValue;
			setPiece(board, userChoiceIndex, userValue);
			continue;
			break;
			// Case for resetting the board
		case 'r':
			cout << "Resetting board" << endl << endl;
			cout << "Enter the size board you want, between 4 and 12: ";

			// User choice of new squaresPerSide
			cin >> squaresPerSide;

			// Determine the difference first, then call the function to raise it
			powerOf = squaresPerSide - 4;

			// Output of new value of MaxTileStartValue
			cout << endl << "Game ends when you reach "
				<< raiseToThePowerOf(2, powerOf) * MaxTileStartValue << "." << endl;

			// Initialize the new board
			initializeBoard(board, squaresPerSide, 0);

			// Place new random value, and start over moves & score
			placeRandomPiece(board, squaresPerSide);
			score = 0;
			move = 0;
			break;

			// Left move
		case 'a':
			slideLeft(board, squaresPerSide, score);
			break;
			// Upward move
		case 'w':
			slideUp(board, squaresPerSide, score);
			break;
			// Right move
		case 'd':
			slideRight(board, squaresPerSide, score);
			break;
			// Downward move
		case 's':
			slideDown(board, squaresPerSide, score);
			break;
		default:
			cout << "Invalid input, please retry.";
			//continue;
			break;
		}//end switch( userInput)

		// If the move resulted in pieces changing position, then it was a valid move
		// so place a new random piece (2 or 4) in a random open square and update the move number.
		for (int i = 0; i < squaresPerSide * squaresPerSide; i++)
		{
			if (board[i] != previousBoard[i])
			{
				placeRandomPiece(board, squaresPerSide);
				move++;
				break;
			}
		}

		// See if we're done.  If so, display the final board and break.
		for (int i = 0; i < squaresPerSide * squaresPerSide; i++)
		{
			if (board[i] == maxTileValue)
			{
				cout << "Congratulations!  You made it to " << maxTileValue << "!!!" << endl;
				displayAsciiBoard(board, squaresPerSide, score);
				exit(0);
			}
		}

		//system("clear");   // Clear the screen in UNIX / Codio.  Should be "cls" on windows.
							 //     May not work in default Mac Xcode configuration, or some other environments.
	}//end while( true)

	// Display the final boards and messages
	displayAsciiBoard(board, squaresPerSide, score);
	cout << move << ". Your move: " << endl;
	cout << "No more available moves.  Game is over." << endl;
	displayAsciiBoard(board, squaresPerSide, score);

	return 0;
}//end main()