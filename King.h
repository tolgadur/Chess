#ifndef KING_H
#define KING_H
 
#include "Piece.h"

class King : public Piece{
private:
public:
  King(bool is_white) : Piece(is_white, "King"){ };
  ~King() override{ };
  bool isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]) override;
};

#endif
