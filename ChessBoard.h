#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "Castle.h"
#include "Bishop.h"
#include "King.h"
#include <string>
#include <vector>

class ChessBoard {
private:
  Piece* board[8][8];
  std::vector<Piece*> eaten_pieces; //Holding pointers to eaten figures so that they can get deleted later
  bool is_white_turn;
  bool in_check;
  bool checkmate;
public:
  ChessBoard();
  ~ChessBoard();
  void resetBoard(); // Resets board in order to start a new game
  void deallocateChessBoard(); // Deletes all pieces which the board points to
  void allocateChessBoard(); // Creates pieces on the heap which are pointed to by the two dimensional board array

  // Methods modelling basic game functionalities
  int submitMove(char const source[], char const destination[]); // Returns 0 if successfull, 1 if not
  bool isInvalidMove(int s_row, int s_column, int d_row, int d_column, char const source[], char const destination[]); // Returns true if move is invalid and false otherwise
  void nextTurn(); //Changes is_white_turn to the opposite state to indicate the start of the next turn
  void makeMove(int s_row, int s_column, int d_row, int d_column, Piece*& temp_destination, Piece*& temp_source, bool& ate_piece);
  void reverseMove(int s_row, int s_column, int d_row, int d_column, Piece* temp_destination, Piece* temp_source, bool& ate_piece);

  // Methods handling checking and stalemate
  bool isInCheck(bool king_is_white);
  bool isStillInCheck();
  bool noPossibleMove(bool king_is_white); //Function to check if there is a possible move without landing in check

  //Helper methods
  int getRow(char const position[]);
  int getColumn(char const position[]);
  bool hasPiece(int destination_row, int destination_column);
  void printMove(int d_row, int d_column, char const source[], char const destination[], Piece* temp_destination, bool ate_piece);
   // Takes in two integers by reference (initial value does not matter) and a bool variable specifying which king we are searching, and iterates through the ChessBoard until
   // this piece is found. After the function ends, the values of the two strings passed in will have the kings row and column position respectively.
  void getKingPosition(int &king_row, int &king_column, bool king_is_white);
};
#endif
