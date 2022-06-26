#include <iostream>
#include <algorithm>
#include <sstream>
#include "board.hpp"

Tile::Tile(int val){
    this->value = val;
    if (val != 0) {
        this->concrete = true;
    } else {
        this->concrete = false;
    }
}


bool Tile::isConcrete(){
    return concrete;
}

int Tile::getValue(){
    return value;
}
bool Tile::setValue(int val){
    auto iter = std::find(begin(available), end(available), val);
    if (iter != available.end()){ //is available
        available.erase(iter,iter+1);
        value = val;
        return true;
    } 
    return false;
}

bool Tile::operator==(Tile& tile){
    if (this->getValue() == tile.getValue()){
        return true;
    } else {
        return false;
    }
}

//iterate over incoming and add it to rows and columns, validate that values are betwenn 0-9
Board::Board(std::vector<int> incoming){
    auto iter = incoming.begin();
    //tiles.resize(9);
    for(int i = 0; i < 9; i++){
        std::vector<Tile> row;
        //row.resize(9);
        for(int j = 0; j < 9; j++){
            if (*iter < 0 || *iter > 9){
                std::cout << "Value in intial board is out of bounds." << std::endl;
                return;
            }
            Tile tile(*iter);
            row.push_back(tile);
            ++iter;
        }
        tiles.push_back(row);
    }
}

//check for non zero duplicates in vector
bool Board::checkRow(int row, int column){
    Tile placedTile = tiles[row][column];
    for (int i = 0; i < 9; i++){
        if(i == column)
            continue;
        if (placedTile == tiles[row][i])
            return false;
    }
    return true;
}

bool Board::checkColumn(int row, int column){
    Tile placedTile = tiles[row][column];
    for(int i = 0; i < 9; i++){
        if (i == row)
            continue;
        if (placedTile == tiles[i][column])
            return false;
    }
    return true;
}

//always going to be called after checking row and column, so we will not repeat comparisons (hence the continues in the nested loop)
bool Board::checkSquare(int row, int column){
    Tile placedTile = tiles[row][column];
    int lowerRowBound = row - (row % 3);
    int lowerColumnBound = column - (column % 3);
    for(int i = lowerRowBound; i < lowerRowBound + 2; i++){
        if (i == row)
            continue;
        for (int j = lowerColumnBound; j < lowerColumnBound + 2; j++){
            if (j == column)
                continue;
            if(placedTile == tiles[i][j])
                return false;
        }
    }
    return true;
}

//tile is placed, verify that it works
bool Board::validTile(int row, int column){
    if (checkRow(row,column) && checkColumn(row,column) && checkSquare(row,column))
        return true;
    else
        return false;
}

void Board::printBoard(){
    std::string horizontal(25, '-');
    std::cout << std::endl << horizontal << std::endl;
    for(int i = 0; i < 9; i++){
        std::cout << "| ";
        for (int j = 0; j < 9; j++){
            if((j+1) % 3== 0)
                std::cout << tiles[i][j].getValue() << " | ";
            else
                std::cout << tiles[i][j].getValue() << " ";
        }
        if((i+1) % 3 == 0)
            std::cout << std::endl << horizontal << std::endl;
        else
             std::cout << std::endl;
    }
}

void Board::printTile(int row, int column){
    std::cout << tiles[row][column].getValue() << std::endl;
}

int main(int argc, char* argv[]){
    int input;
    std::vector<int> board;
    //for user inputed board
    /*while (board.size() < 81 && std::cin >> input){
        board.push_back(input);   
    }*/
    std::stringstream in;
    in <<  "1 8 4 9 6 3 7 2 5\
            5 6 2 7 4 8 3 1 9\
            3 9 7 5 1 2 8 6 4\
            2 3 9 6 5 7 1 4 8\
            7 5 6 1 8 4 2 9 3\
            4 1 8 2 3 9 6 5 7\
            9 4 1 3 7 6 5 8 2\
            6 2 3 8 9 5 4 7 1\
            8 7 5 4 2 1 9 3 6";
    while(in >> input){
        board.push_back(input);
    }
    
    Board testBoard(board);
    std::cout << testBoard.validTile(3,3) << std::endl;
    testBoard.printBoard();
}