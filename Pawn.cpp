#include "Pawn.h"
#include <iostream>

using namespace std;

bool Pawn::isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]){
  bool destination_has_piece = (board[d_row][d_column] == nullptr) ? false : true;
  bool destination_piece_is_white = false;
  if(destination_has_piece){
    destination_piece_is_white = board[d_row][d_column]->getIs_white_piece();
  }

  if(is_white_piece){
    if(s_column == d_column){
      if(d_row == 2 && s_row == 1 && !destination_has_piece){
        return true;
      }
      else if(d_row == 3 && s_row == 1 && !destination_has_piece && pieceInTheWayStraight(s_row, s_column, d_row, d_column, board) == false){
        return true;
      }
    }
    else if(d_column - s_column == 1 || s_column - d_column == 1){
      if(d_row - s_row == 1 && destination_has_piece && !destination_piece_is_white){ // check if destination piece is opponent
        return true;
      }
    }
  }
  else if(!is_white_piece){
    if(s_column == d_column){
      if(d_row == 5 && s_row == 6 && !destination_has_piece){
        return true;
      }
      else if(d_row == 4 && s_row == 6 && !destination_has_piece && pieceInTheWayStraight(s_row, s_column, d_row, d_column, board) == false){
        return true;
      }
    }
    else if(d_column - s_column == 1 || s_column - d_column == 1){
      if(s_row - d_row == 1 && destination_has_piece && destination_piece_is_white){
        return true;
      }
    }
  }
  return false;

}
