#include "Piece.h"
#include <iostream>
#include <string>
 
using namespace std;


ostream& operator <<(ostream& o, Piece* P){
  return o << ((P->is_white_piece) ? "White's " : "Black's ") << P->getName();
}

ostream& operator >>(std::ostream& o, Piece* P){
  return o << ((P->is_white_piece) ? "White" : "Black");
}

string Piece::getName(){
  return name;
}

bool Piece::getIs_white_piece(){
  return is_white_piece;
}

bool Piece::pieceInTheWayDiagonal(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]){
  int r;
  int c;
  if(d_row > s_row && d_column > s_column){
    r = s_row + 1;
    c = s_column + 1;
    while(r != d_row || c != d_column){
      if(board[r][c]){
          return true;
      }
      r++;
      c++;
    }
  }
  else if(d_row > s_row && d_column < s_column){
    r = s_row + 1;
    c = s_column - 1;
    while(r != d_row || c != d_column){
      if(board[r][c]){
          return true;
      }
      r++;
      c--;
    }
  }
  else if(d_row < s_row && d_column > s_column){
    r = s_row - 1;
    c = s_column + 1;
    while(r != d_row || c != d_column){
      if(board[r][c]){
          return true;
      }
      r--;
      c++;
    }
  }
  else if(d_row < s_row && d_column < s_column){
    r = s_row - 1;
    c = s_column - 1;
    while(r != d_row || c != d_column){
      if(board[r][c]){
          return true;
      }
      r--;
      c--;
    }
  }
  return false;
}

bool Piece::pieceInTheWayStraight(int s_row, int s_column, int d_row, int d_column, Piece* board[8][8]){
  if(s_row == d_row){
    if(s_column < d_column){
      for(int i = s_column + 1; i < d_column; i++){
        if(board[s_row][i]){
          return true;
        }
      }
    }
    else if(s_column > d_column){
      for(int i = s_column - 1; i > d_column; i--){
        if(board[s_row][i]){
          return true;
        }
      }
    }
  }
  else if(s_column == d_column){
    if(s_row < d_row){
      for(int i = s_row + 1; i < d_row; i++){
        if(board[i][s_column]){
          return true;
        }
      }
    }
    else if(s_row > d_row){
      for(int i = s_row - 1; i > d_row; i--){
        if(board[i][s_column]){
          return true;
        }
      }
    }
  }
  return false;
}
