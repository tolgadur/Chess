#include "Knight.h"
#include <iostream>
 
using namespace std;

bool Knight::isMoveOK(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]){
  bool destination_has_figure = (board[d_row][d_column] == nullptr) ? false : true;
  bool destination_figure_is_white = false;
  if(destination_has_figure){
    destination_figure_is_white = board[d_row][d_column]->getIs_white_piece();
  }

  if(d_row - s_row == 1 || s_row - d_row == 1){
    if(d_column - s_column == 2 || s_column - d_column == 2){
      if(!destination_has_figure){
        return true;
      }
      else if((is_white_piece && !destination_figure_is_white) || (!is_white_piece && destination_figure_is_white)){
        return true;
      }
    }
  }
  else if(d_row - s_row == 2 || s_row - d_row == 2){
    if(d_column - s_column == 1 || s_column - d_column == 1){
      if(!destination_has_figure){
        return true;
      }
      else if((is_white_piece && !destination_figure_is_white) || (!is_white_piece && destination_figure_is_white)){
        return true;
      }
    }
  }
  return false;

}
