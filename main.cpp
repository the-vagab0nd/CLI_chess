#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;
void ColorPrint(const char text, int fg_color, int bg_color)
{
    static const char begin_sequence[]{0x1B,'[','\0'};
    static const char reset[]{0x1B,'[','0','m','\0'};

    cout << begin_sequence << fg_color << ';' << bg_color << 'm' << text << reset;
}
class Board;
class Box;
class Piece;
class Pawn;
class Bishop;
class Knight;
class King;
class Queen;
class Rook;
class Piece  {
    private : 
        bool is_killed = false; 
        bool is_white = false;
        char c;
    public :
        Piece(bool is_white, char c){
            this->is_white = is_white;
            this->c = c;
        }
        bool isAlive(){
            return this->is_killed == false;
        }
        void setKilled(){
            is_killed = true;
        }
        bool colour(){
            return this->is_white;
        }
        char name(){
            return c;
        }
        virtual bool canMove(Board *board, Box *start, Box *end) = 0;
};
class Box {
    private :
        Piece *piece;
        int x, y;
    public :
        Box(){
            this->x = 0;
            this->y = 0;
            piece = NULL;
        }
        Box(int x, int y, Piece *piece){
            this -> x = x;
            this -> y = y;
            this -> piece = piece;
        }
        void setPiece(Piece *piece){
            this -> piece = piece;
        }
        char name(){
            return ((*(this->piece)).name());
        }
        bool isEmpty(){return piece == NULL;}
        void setX(int x){this->x = x;}
        void setY(int y){this->x = y;}
        bool isWhite(){
            return ((*(this->piece)).colour());
        }
};
class Pawn : public Piece{
    public :
        Pawn(bool is_white):Piece(is_white, 'p'){};
        bool canMove(Board *board, Box *start, Box *end){
            return true;
        }
};
class Rook : public Piece{
    public :
        Rook(bool is_white):Piece(is_white, 'r'){};
        bool canMove(Board *board, Box *start, Box *end){
            return true;
        }
};
class Bishop : public Piece{
    public :
        Bishop(bool is_white):Piece(is_white, 'b'){};
        bool canMove(Board *board, Box *start, Box *end){
            return true;
        }
};
class King : public Piece{
    public :
        King(bool is_white):Piece(is_white, 'K'){};
        bool canMove(Board *board, Box *start, Box *end){
            return true;
        }
};
class Queen : public Piece{
    public :
        Queen(bool is_white):Piece(is_white, 'q'){};
        bool canMove(Board *board, Box *start, Box *end){
            return true;
        }
};
class Knight : public Piece{
    public :
        Knight(bool is_white):Piece(is_white, 'k'){};
        bool canMove(Board *board, Box *start, Box *end){
            return true;
        }
};
class Board {
    private :
        Box boxes[8][8];
    public :
        Board(){
            Rook r0(0), r1(1);
            Bishop b0(0), b1(1);
            Knight k0(0), k1(1);
            Queen q0(0), q1(1);
            King K0(0), K1(1);
            for(int i = 0; i < 8; i++){
                boxes[1][i] = Box(1, i, new Pawn(1));
                boxes[6][i] = Box(7, i, new Pawn(0));
            }
            for(int i = 2; i < 6; i++){
                for(int j = 0; j < 6; j++){
                    boxes[i][j] = Box(i, j, NULL);
                }
            }
            boxes[0][0] = Box(0, 0, new Rook(1));
            boxes[0][7] = Box(0, 7, new Rook(1));
            boxes[7][7] = Box(7, 7, new Rook(0));
            boxes[7][0] = Box(7, 0, new Rook(0));
            boxes[0][6] = Box(0, 6, new Knight(1));
            boxes[0][1] = Box(0, 1, new Knight(1));
            boxes[0][5] = Box(0, 5, new Bishop(1));
            boxes[0][2] = Box(0, 2, new Bishop(1));
            boxes[0][3] = Box(0, 3, new Queen(1));
            boxes[0][4] = Box(0, 4, new King(1));
            boxes[7][6] = Box(0, 6, new Knight(0));
            boxes[7][1] = Box(0, 1, new Knight(0));
            boxes[7][5] = Box(0, 5, new Bishop(0));
            boxes[7][2] = Box(0, 2, new Bishop(0));
            boxes[7][3] = Box(0, 3, new Queen(0));
            boxes[7][4] = Box(0, 4, new King(0));
        }
        void show(){
            for(int i = 7; i >= 0; i--){
                for(int j = 0; j <= 7; j++){
                    if(boxes[i][j].isEmpty())ColorPrint('x', 90, 90), cout << " ";
                    else if(boxes[i][j].isWhite())cout << boxes[i][j].name() << " ";
                    else ColorPrint(boxes[i][j].name(), 90, 30), cout << " ";
                }
                cout << endl;
            }
        }
        
};

int main(){
    Board b;
    b.show();
};
