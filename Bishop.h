#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"


class Bishop : public Piece{
private:
public:
  Bishop(bool is_white) : Piece(is_white, "Bishop"){ };
  ~Bishop() override{ };
  bool isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]) override;
};

#endif
