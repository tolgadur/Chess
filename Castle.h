#ifndef CASTLE_H
#define CASTLE_H

#include "Piece.h"


class Castle : public Piece{
private:
public:
  Castle(bool is_white) : Piece(is_white, "Castle"){ };
  ~Castle() override{ };
  bool isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]) override;
};

#endif
 
