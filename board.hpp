#include <vector> 

class Tile{
    private:
        int value; //1-9, 0 for empty
        bool concrete;
        std::vector<int> available{1,2,3,4,5,6,7,8,9};
    public:
        Tile(){
            value = 0;
        }
        Tile(int);
        bool operator==(Tile&);
        bool isConcrete();
        int getValue();
        void setValue(int);
};

class Board{
    private:
        std::vector<std::vector<Tile>> tiles;
        bool checkRow(int,int);
        bool checkColumn(int,int);
        bool checkSquare(int,int);
    public:
        Board(std::vector<int>);    
        bool validTile(int, int);
        void printBoard();
        void printTile(int, int);
        bool solveBoard(int, int);
        void solve();
};