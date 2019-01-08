#include "Castle.h"
#include <iostream>

using namespace std;

bool Castle::isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]){
  bool destination_has_piece = (board[d_row][d_column] == nullptr) ? false : true;
  bool destination_piece_is_white = false;
  if(destination_has_piece){
    destination_piece_is_white = board[d_row][d_column]->getIs_white_piece();
  }

  // Check if piece is in the way
  if(pieceInTheWayStraight(s_row, s_column, d_row, d_column, board)) return false;
  // Check if move is valid otherwise
  if(s_row == d_row || s_column == d_column){
    if(destination_has_piece){
      if((is_white_piece && !destination_piece_is_white) || (!is_white_piece && destination_piece_is_white)){
        return true;
      }
    }
    else if(!destination_has_piece){
      return true;
    }
  }
  return false;
}
 
