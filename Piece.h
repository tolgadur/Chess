#ifndef PIECE_H
#define PIECE_H
 
#include <iostream>
#include <string>

class Piece{
private:
protected:
  bool is_white_piece; // false implies that the piece is a black piece.
  std::string name; // specifies the name of the piece. (e.g. the value of a Castle piece is "Castle")
public:
  Piece(bool is_white, std::string name) : is_white_piece(is_white), name(name){ };
  virtual ~Piece(){ };
  bool getIs_white_piece(); // Getter Method for the private data member specifying the color of the piece.
  std::string getName(); // Getter Method for the private data memeber specifying the name of the piece.
  // The methods isMoveOK take in the source and destnation (each represented by two integer values specifying the row and column respectively),
  // and return whether the move is valid or not.
  virtual bool isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]) = 0;
  // pieceInTheWayDiagonal and pieceInTheWayStraight take in the source, destination and the entire board holding pointers to all pieces on the chessboard.
  // They return true if there is a piece in the way and false if not. The prior is used to check if there is a piece in the way for straight moves (e.g. done
  // by the castle) and the latter to check if there is a pieces in the way for diagonal moves (e.g. for moves by the Bishop)
  bool pieceInTheWayDiagonal(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]);
  bool pieceInTheWayStraight(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]);
  friend std::ostream& operator <<(std::ostream& o, Piece* P);
  friend std::ostream& operator >>(std::ostream& o, Piece* P);

};

#endif
