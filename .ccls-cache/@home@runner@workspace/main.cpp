#include <iostream>
using namespace std;

//Constants
const int SIZE = 3;
const char EMPTY = '*';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

//Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void displayBoard(const char board[SIZE][SIZE]);
void placeToken(char token, char board[SIZE][SIZE]);
void getLocation(int &row, int &col, const char board[SIZE][SIZE]);
string getBoardState(char token, const char board[SIZE][SIZE]);
string checkForWinner(char token, const char board[SIZE][SIZE]);

int main() {
  char board[SIZE][SIZE];
  string boardState = "Play";

  initializeBoard(board);
  displayBoard(board);

  while (boardState == "Play") {
    placeToken(PLAYER1, board);
    displayBoard(board);
    boardState = getBoardState(PLAYER1, board);
    if (boardState != "Play") break;

    placeToken(PLAYER2, board);
    displayBoard(board);
    boardState = getBoardState(PLAYER2, board);
  }
  if (boardState == "X_WIN") {
    cout << "Player 1 (X) wins!\n";
    } else if (boardState == "O_WIN") {
      cout << "Player 2 (O) wins!\n";
    } else if (boardState == "TIE") {
      cout << "The game is a tie.\n";
    }
  return 0;
  }

//Initialize the board with '*'
void initializeBoard (char board[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++)
  for (int j = 0; j < SIZE; j++)   
    board[i][j] = EMPTY;  
}

//Display the current board state
void displayBoard(const char board[SIZE][SIZE]) {
  cout << "\n 1 2 3\n";
  for (int i = 0; i < SIZE; i++) {
    cout << i + 1 << " ";
    for (int j = 0; j < SIZE; j++) {
      cout << board[i][j] << " ";
    }
    cout << "\n";
    }
  }
//Handles placing a player's token on the board
void placeToken(char token, char board[SIZE][SIZE]) {
  int row, col;
  getLocation(row, col, board);
  board[row][col] = token;
  }

//Gets valid row and column from the user
void getLocation(int &row, int &col, const char board[SIZE][SIZE]) {
  bool valid = false;
  while (!valid) {
    cout << "Enter row and column (1-3) for your move: ";
    cin >> row >> col;
    row--; col--; //Adjust for 0-based index

    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
      if (board[row][col] == EMPTY) {
        valid = true;
      } else {
        cout << "That spot is already taken. Try again.\n";
      }
      } else {
        cout << "Invalid input. Please enter row and column numbers between 1 and 3.\n";
      }
    }
  }

//Determine game state
string getBoardState(char token, const char board[SIZE][SIZE]) {
  string result = checkForWinner(token, board);

  if (result == "WINNER") {
    return (token == 'X') ? "X_WIN" : "O_WIN";
    } else if (result == "NO_SPACE") {
      return "TIE";
    } else {
      return "Play";
    }
  }

//Checks for a win or tie
string checkForWinner(char token, const char board[SIZE][SIZE]) {
  //Check rows and columns
  for (int i = 0; i < SIZE; i++) {
    if ((board[i][0] == token && board[i][1] == token && board[i][2] == token) ||  
        (board[0][i] == token && board[1][i] == token && board[2][i] == token)) {
      return "WINNER";
    }
    }
  //Check diagonals
  if ((board[0][0] == token && board[1][1] == token && board[2][2] == token) ||
      (board[0][2] == token && board[1][1] == token && board[2][0] == token)) {
    return "WINNER";
    }
  //Check for empty spaces
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      if (board[i][j] == EMPTY)
        return "SPACE_LEFT";
  return "NO_SPACE";
  }
