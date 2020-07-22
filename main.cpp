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
    public :
        bool is_killed = false; 
        bool is_white = false;
        char c;
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
        virtual bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end) = 0;
};
class Pawn : public Piece{
    public :
        Pawn(bool is_white):Piece(is_white, 'p'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            Piece *p = boxes[end.first][end.second];
            if(start.second == end.second){
                if(end.first - start.first == (is_white?2:-2) and p == NULL and start.first == (is_white?1:6) and boxes[start.first + (is_white?1:-1)][end.second] == NULL)return 1;
                else if(end.first - start.first == (is_white?1:-1) and p == NULL)return 1;
                else return 0;
            }
            if(abs(start.second - start.first) == 1 and end.first - start.first == (is_white?1:-1) and p != NULL)return 1;
            return 0;
        }
};
class Rook : public Piece{
    public :
        Rook(bool is_white):Piece(is_white, 'r'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            return true;
        }
};
class Bishop : public Piece{
    public :
        Bishop(bool is_white):Piece(is_white, 'b'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            return true;
        }
};
class King : public Piece{
    public :
        King(bool is_white):Piece(is_white, 'K'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            return true;
        }
};
class Queen : public Piece{
    public :
        Queen(bool is_white):Piece(is_white, 'q'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            return true;
        }
};
class Knight : public Piece{
    public :
        Knight(bool is_white):Piece(is_white, 'k'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            return true;
        }
};
class Board {
    private :
        vector<vector<Piece *> >boxes;
    public :
        Board(){
            boxes.resize(8, vector<Piece*>(8));
            for(int i = 0; i < 8; i++){
                boxes[1][i] = new Pawn(1);
                boxes[6][i] = new Pawn(0);
            }
            for(int i = 2; i < 6; i++){
                for(int j = 0; j < 8; j++){
                    boxes[i][j] = NULL;
                }
            }
            boxes[0][0] = new Rook(1);
            boxes[0][7] = new Rook(1);
            boxes[7][7] = new Rook(0);
            boxes[7][0] = new Rook(0);
            boxes[0][6] = new Knight(1);
            boxes[0][1] = new Knight(1);
            boxes[0][5] = new Bishop(1);
            boxes[0][2] = new Bishop(1);
            boxes[0][3] = new Queen(1);
            boxes[0][4] = new King(1);
            boxes[7][6] = new Knight(0);
            boxes[7][1] = new Knight(0);
            boxes[7][5] = new Bishop(0);
            boxes[7][2] = new Bishop(0);
            boxes[7][3] = new Queen(0);
            boxes[7][4] = new King(0);
        }
        void show(){
            for(int i = 7; i >= 0; i--){
                for(int j = 0; j <= 7; j++){
                    if(boxes[i][j] == NULL)ColorPrint('x', 90, 90), cout << " ";
                    else if((*boxes[i][j]).colour())cout << (*boxes[i][j]).name() << " ";
                    else ColorPrint((*boxes[i][j]).name(), 90, 30), cout << " ";
                }
                cout << endl;
            }
        }
        Piece* cellPtr(int i, int j){
            return boxes[i][j];
        }
        vector<vector<Piece *> > allCells(){return boxes;}
        void set(int i, int j, Piece * p){
            boxes[i][j] = p;
        }
};
class Game{
    private :
        Board b;
        string pw, pb;
        int turn;
        pair<int, int> start, end;
    public :
        Game(string pw, string pb){this->pw = pw, this->pb = pb, this->turn = 0;}
        void show(){b.show();}
        bool getMove(){
            cin >> start.second;
            if(start.second == -1)return 0;
            cin >> start.first >> end.second >> end.first;
            start.first--, start.second--, end.first--, end.second--;
            return 1;
        }
        bool move(){
            Piece * starting_piece = b.cellPtr(start.first, start.second), * ending_piece = b.cellPtr(end.first, end.second);
            if(starting_piece == NULL || (*starting_piece).colour() == turn)return 0;
            if(ending_piece != NULL and (*starting_piece).colour() == (*ending_piece).colour())return 0;
            if((*starting_piece).canMove(b.allCells(), start, end) == 0)return 0;
            b.set(end.first, end.second, starting_piece);
            b.set(start.first, start.second, NULL);
            turn = (turn+1)%2;
        }
        void play(){
            show();
            cout << "First Move?\n";
            while(getMove()){
                bool x = move();
                if(x)cout << "Next Move?\n", show();
                else cout << "Invalid Move! Think again.\n";
            }
        }
};
int main(){
    Game b("asd","bsd");
    b.play();
};
