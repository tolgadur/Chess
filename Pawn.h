#ifndef PAWN_H
#define PAWN_H
 
#include "Piece.h"

class Pawn : public Piece{
private:
public:
  Pawn(bool is_white) : Piece(is_white, "Pawn"){ };
  ~Pawn() override{ };
  bool isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]) override;
};

#endif
