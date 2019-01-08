#include "King.h"
#include <iostream>

using namespace std;

bool King::isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]){
  bool destination_has_piece = (board[d_row][d_column] == nullptr) ? false : true;
  bool destination_piece_is_white = false;
  if(destination_has_piece){
    destination_piece_is_white = board[d_row][d_column]->getIs_white_piece();
  }

  if(s_column - d_column == 1 || d_column - s_column == 1 || s_column == d_column){
    if(s_row - d_row == 1 || d_row - s_row == 1 || d_row == s_row){
      if(destination_has_piece){
        if((is_white_piece && !destination_piece_is_white) || (!is_white_piece && destination_piece_is_white)){
          return true;
        }
      }
      else if(!destination_has_piece){
        return true;
      }
    }
  }
  return false;
}
 
