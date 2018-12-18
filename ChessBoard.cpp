#include "ChessBoard.h"
#include <iostream>
#include <string>

using namespace std;

void ChessBoard::allocateChessBoard(){
  for(int row = 0; row < 8; row++){
    for(int column = 0; column < 8; column++){
      switch(row){
        case 0:{
          switch(column){
            case 0: board[row][column] = new Castle(true); break;
            case 1: board[row][column] = new Knight(true); break;
            case 2: board[row][column] = new Bishop(true); break;
            case 3: board[row][column] = new Queen(true); break;
            case 4: board[row][column] = new King(true); break;
            case 5: board[row][column] = new Bishop(true); break;
            case 6: board[row][column] = new Knight(true); break;
            case 7: board[row][column] = new Castle(true); break;
          }
          break;
        }
        case 1: board[row][column] = new Pawn(true); break;
        case 2: board[row][column] = nullptr; break;
        case 3: board[row][column] = nullptr; break;
        case 4: board[row][column] = nullptr; break;
        case 5: board[row][column] = nullptr; break;
        case 6: board[row][column] = new Pawn(false); break;
        case 7:{
          switch(column){
            case 0: board[row][column] = new Castle(false); break;
            case 1: board[row][column] = new Knight(false); break;
            case 2: board[row][column] = new Bishop(false); break;
            case 3: board[row][column] = new Queen(false); break;
            case 4: board[row][column] = new King(false); break;
            case 5: board[row][column] = new Bishop(false); break;
            case 6: board[row][column] = new Knight(false); break;
            case 7: board[row][column] = new Castle(false); break;
          }
          break;
        }
      }
    }
  }

  cout << "A new chess game is started!" << endl;
}

void ChessBoard::deallocateChessBoard(){
  for(int row = 0; row < 8; row++){
    for(int column = 0; column < 8; column++){
      if(board[row][column]){
        delete board[row][column];
        board[row][column] = nullptr;
      }
    }
  }
}

ChessBoard::ChessBoard(): is_white_turn(true), in_check(false), checkmate(false){
  allocateChessBoard();
}

ChessBoard::~ChessBoard(){
  deallocateChessBoard();

  for(unsigned int i = 0; i < eaten_pieces.size(); i++){
    delete eaten_pieces[i];
    eaten_pieces[i] = nullptr;
  }
}

void ChessBoard::resetBoard(){
  deallocateChessBoard();
  allocateChessBoard();
  is_white_turn = true;
  in_check = false;
  checkmate = false;
}


// Methods modelling the game
int ChessBoard::submitMove(char const source[], char const destination[]){
  int s_row = getRow(source);
  int s_column = getColumn(source);
  int d_row = getRow(destination);
  int d_column = getColumn(destination);
  bool ate_piece = false;

  if(isInvalidMove(s_row, s_column, d_row, d_column, source, destination)){
    return 1;
  }

  Piece* temp_destination = nullptr;
  Piece* temp_source = board[s_row][s_column];
  if(board[s_row][s_column]->isMoveOK(s_row, s_column, d_row, d_column, board)){
    makeMove(s_row, s_column, d_row, d_column, temp_destination, temp_source, ate_piece);
  }

  // Check methods
  if(isStillInCheck()){
    reverseMove(s_row, s_column, d_row, d_column, temp_destination, temp_source, ate_piece);
    return 1;
  }
  else if(isInCheck(is_white_turn)){
    cerr << "This is not a valid move as it would put you in check." << endl;
    reverseMove(s_row, s_column, d_row, d_column, temp_destination, temp_source, ate_piece);
  }
  if(in_check) in_check = false;
  if(isInCheck(!is_white_turn)) in_check = true;
  if(in_check && noPossibleMove(!is_white_turn)) checkmate = true;

  // display_board();
  printMove(d_row, d_column, source, destination, temp_destination, ate_piece);
  if(noPossibleMove(!is_white_turn) && checkmate == false){
    cerr << "The game ends in a stalemate" << endl;
    return 1;
  }

  nextTurn();
  return 0;
}

void ChessBoard::makeMove(int s_row, int s_column, int d_row, int d_column, Piece*& temp_destination, Piece*& temp_source, bool& ate_piece){
  board[s_row][s_column] = nullptr;
  if(hasPiece(d_row, d_column)){
    temp_destination = board[d_row][d_column]; // saving piece in case board needs to get rewinded
    eaten_pieces.push_back(board[d_row][d_column]);
    ate_piece = true;
    board[d_row][d_column] = nullptr;
  }
  board[d_row][d_column] = temp_source;
}

void ChessBoard::reverseMove(int s_row, int s_column, int d_row, int d_column, Piece* temp_destination, Piece* temp_source, bool& ate_piece){
  board[s_row][s_column] = temp_source;
  board[d_row][d_column] = temp_destination;
  if(ate_piece) eaten_pieces.pop_back();
  if(ate_piece) ate_piece = false;
}

void ChessBoard::nextTurn(){
  if(is_white_turn == true){
    is_white_turn = false;
  }
  else if(is_white_turn == false){
    is_white_turn = true;
  }
}

bool ChessBoard::isInvalidMove(int s_row, int s_column, int d_row, int d_column, char const source[], char const destination[]){
  if(s_row > 7 || s_row < 0 || s_column > 7 || s_column < 0 || d_row > 7 || d_row < 0 || d_column > 7 || d_column < 0){
    cerr << "The source/destination you specified is not on the board!" << endl;
    return true;
  }
  else if(checkmate){
    cerr << "The game is already over. Please start a new game." << endl;
    return true;
  }
  else if(source == destination){
    cerr << "It is not a valid move to leave the " << board[s_row][s_column]->getName() << " on the same spot!" << endl;
    return true;
  }
  else if(!hasPiece(s_row, s_column)){
    cerr << "There is no piece at position " << source << "!\n";
    return true;
  }
  else if((is_white_turn && !board[s_row][s_column]->getIs_white_piece()) || (!is_white_turn && board[s_row][s_column]->getIs_white_piece())){
    cerr << "It is not " >> board[s_row][s_column] << "'s turn to move!" << endl;
    return true;
  }
  else if(!board[s_row][s_column]->isMoveOK(s_row, s_column, d_row, d_column, board)){
    cerr << board[s_row][s_column] << " cannot move to " << destination << endl;
    return true;
  }
  return false;
}


// Methods handling checking
bool ChessBoard::isInCheck(bool king_is_white){
  // Find position of the oponents king
  int king_row = 0;
  int king_column = 0;
  getKingPosition(king_row, king_column, king_is_white);

  // Check if there is a possibility that the could lead to the king being eaten in the next round.
  for(int row = 0; row < 8; row++){
    for(int column = 0; column < 8; column++){
      if(board[row][column]){
        if(board[row][column]->isMoveOK(row, column, king_row, king_column, board)){
          return true;
        }
      }
    }
  }
  return false;
}

bool ChessBoard::noPossibleMove(bool king_is_white){
  int king_row = 0;
  int king_column = 0;
  getKingPosition(king_row, king_column, king_is_white);

  for(int s_row = 0; s_row < 8; s_row++){
    for(int s_column = 0; s_column < 8; s_column++){
      if(board[s_row][s_column]){
        if(board[s_row][s_column]->getIs_white_piece() == king_is_white){
          for(int d_row = 0; d_row < 8; d_row++){
            for(int d_column = 0; d_column < 8; d_column++){
              if(board[s_row][s_column]->isMoveOK(s_row, s_column, d_row, d_column, board)){
                bool ate_piece_simulation= false;
                Piece* temp_source = board[s_row][s_column];
                Piece* temp_destination = nullptr;
                makeMove(s_row, s_column, d_row, d_column, temp_destination, temp_source, ate_piece_simulation);
                if(isInCheck(king_is_white) == false){
                  reverseMove(s_row, s_column, d_row, d_column, temp_destination, temp_source, ate_piece_simulation);
                  return false;
                }
                reverseMove(s_row, s_column, d_row, d_column, temp_destination, temp_source, ate_piece_simulation);
              }
            }
          }
        }
      }
    }
  }
  return true;
}

bool ChessBoard::isStillInCheck(){
  if(in_check){
    if(is_white_turn){
      if(isInCheck(true)){
        cerr << "Only moves that get you out of check are allowed!" << endl;
        return true;
      }
    }
    else{
      if(isInCheck(false)){
        cerr << "Only moves that get you out of check are allowed!" << endl;
        return true;
      }
    }
  }
  return false;
}


// Helper methods
void ChessBoard::getKingPosition(int &king_row, int &king_column, bool king_is_white){
  if(king_is_white){
      for(king_row = 0; king_row < 8; king_row++)
        for(king_column = 0; king_column < 8; king_column++)
          if(board[king_row][king_column])
            if(board[king_row][king_column]->getName() == "King" && board[king_row][king_column]->getIs_white_piece() )
              return;
  }
  else{
    for(king_row = 0; king_row < 8; king_row++)
      for(king_column = 0; king_column < 8; king_column++)
        if(board[king_row][king_column])
          if(board[king_row][king_column]->getName() == "King" && board[king_row][king_column]->getIs_white_piece() == false)
            return;
  }
}

void ChessBoard::printMove(int d_row, int d_column, char const source[], char const destination[], Piece* temp_destination, bool ate_piece){
  cout << board[d_row][d_column] << " moves from " << source << " to " << destination;
  if(ate_piece) cout << " taking " << temp_destination;
  cout << endl;

  int king_row = 0;
  int king_column = 0;
  getKingPosition(king_row, king_column, !is_white_turn);
  if(checkmate) cout >> board[king_row][king_column] << " is in checkmate" << endl;
  else if(in_check) cout >> board[king_row][king_column] << " is in check" << endl;
}

int ChessBoard::getRow(char const position[]){
  return (static_cast<int>(position[1]) - 49);
}

int ChessBoard::getColumn(char const position[]){
  return (static_cast<int>(position[0]) - 65);
}

bool ChessBoard::hasPiece(int row, int column){
  if(board[row][column] == nullptr){
    return false;
  }
  else{
    return true;
  }
}
