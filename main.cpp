#include <iostream>
#include <string>
#include <vector>
#include <math.h>
const int sz = 8;
using namespace std;
void ColorPrint(const char text, int fg_color, int bg_color)
{
    static const char begin_sequence[]{0x1B,'[','\0'};
    static const char reset[]{0x1B,'[','0','m','\0'};

    cout << begin_sequence << fg_color << ';' << bg_color << 'm' << text << reset;
}
class Board;
class Box;
class Piece  {
    public :
        bool is_white = false;
        char c;
        Piece(bool is_white, char c){
            this->is_white = is_white;
            this->c = c;
        }
        bool colour(){
            return this->is_white;
        }
        char name(){
            return c;
        }
        void rookMoves(vector<vector<Piece *> >boxes, pair<int, int> start, vector<vector<int> > &arr){
            int c = 1;
            while(start.second + c < sz){
                arr[start.first][start.second+c]++;
                if(boxes[start.first][start.second+c] != NULL)break;
                c++;
            }
            c = 1;
            while(c <= start.second){
                arr[start.first][start.second-c]++;
                if(boxes[start.first][start.second-c] != NULL)break;
                c++;
            }
            c = 1;
            while(start.first + c < sz){
                arr[start.first+c][start.second]++;
                if(boxes[start.first+c][start.second] != NULL)break;
                c++;
            }
            c = 1;
            while(c <= start.first){
                arr[start.first-c][start.second]++;
                if(boxes[start.first-c][start.second] != NULL)break;
                c++;
            }
        }
        void bishopMoves(vector<vector<Piece *> >boxes, pair<int, int> start, vector<vector<int> > &arr){
            int c = 1;
            while(start.first + c < sz and start.second + c < sz){
                arr[start.first+c][start.second+c]++;
                if(boxes[start.first + c][start.second+c] != NULL)break;
                c++;
            }
            c = 1;
            while(start.first + c < sz and start.second - c >= 0){
                arr[start.first+c][start.second-c]++;
                if(boxes[start.first + c][start.second-c] != NULL)break;
                c++;
            }
            c = 1;
            while(start.first -c >= 0 and start.second + c < sz){
                arr[start.first-c][start.second+c]++;
                if(boxes[start.first - c][start.second+c] != NULL)break;
                c++;
            }
            c = 1;
            while(start.first -c >= 0 and start.second - c >= 0){
                arr[start.first-c][start.second-c]++;
                if(boxes[start.first - c][start.second - c] != NULL)break;
                c++;
            }
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
            if(abs(start.second - end.second) == 1 and end.first - start.first == (is_white?1:-1) and p != NULL)return 1;
            return 0;
        }
};
class Rook : public Piece{
    public :
        Rook(bool is_white):Piece(is_white, 'r'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            vector<vector<int> >arr(8, vector<int>(8, 0));
            rookMoves(boxes,start, arr);    
            return arr[end.first][end.second] > 0;
        }
};
class Bishop : public Piece{
    public :
        Bishop(bool is_white):Piece(is_white, 'b'){};
        
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            vector<vector<int> >arr(8, vector<int>(8, 0));
            bishopMoves(boxes, start, arr);
            return arr[end.first][end.second] > 0;
        }
};
class King : public Piece{
    public :
        King(bool is_white):Piece(is_white, 'K'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            int dst = abs(start.first - end.first) + abs(start.second - end.second);
            if(dst == 1)return 1;
        }
};
class Queen : public Piece{
    public :
        Queen(bool is_white):Piece(is_white, 'q'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            vector<vector<int> >arr(8, vector<int>(8, 0));
            bishopMoves(boxes, start, arr);
            rookMoves(boxes,start, arr); 
            return arr[end.first][end.second] > 0;
        }
};
class Knight : public Piece{
    public :
        Knight(bool is_white):Piece(is_white, 'k'){};
        bool canMove(vector<vector<Piece *> >boxes, pair<int, int> start, pair<int, int> end){
            int a = abs(start.first - end.first), b = abs(start.second - end.second);
            if(a == 1 and b == 2 or a == 2 and b == 1)return 1;
            else return 0;
        }
};
class Board {
    private :
        vector<vector<Piece *> >boxes;
    public :
        Board(){
            boxes.resize(8, vector<Piece*>(8));
            for(int i = 0; i < sz; i++){
                boxes[1][i] = new Pawn(1);
                boxes[6][i] = new Pawn(0);
            }
            for(int i = 2; i < sz-2; i++){
                for(int j = 0; j < sz; j++){
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
            cout << "    ";
            for(int i = 1; i < 9; i++)cout << i << " ";cout << endl;
            for(int i = 7; i >= 0; i--){
                cout << i+1 << "   ";
                for(int j = 0; j <= 7; j++){
                    if(boxes[i][j] == NULL)ColorPrint('x', 90, 90), cout << " ";
                    else if((*boxes[i][j]).colour())cout << (*boxes[i][j]).name() << " ";
                    else ColorPrint((*boxes[i][j]).name(), 90, 30), cout << " ";
                }
                cout << "  " << i + 1 << endl;
            }
            cout << "    ";
            for(int i = 1; i <= 8; i++)cout << i << " ";
            cout << endl;
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
        string players[2];
        int turn;
        pair<int, int> start, end;
    public :
        Game(string pw, string pb){this->players[0] = pw, this->players[1] = pb, this->turn = 1;}
        void show(){b.show();}
        bool check(int a){
            if(a >= sz || a <0)return 0;
            return 1;
        }
        bool getMove(){
            cin >> start.second;
            if(start.second == -1)return 0;
            cin >> start.first >> end.second >> end.first;
            start.first--, start.second--, end.first--, end.second--;
            return 1;
        }
        void promotemsg(){
            cout << "Awesome you can promote now\n What would you like to promote your pawn at " << start.first << " " << start.second << " to promote to?\n";
            cout << "Options : Rook \n Knight \n Queen \n Bishop \n";
            cout << "Enter name of piece you want in same case\n";
        }
        bool isValid(pair<int, int> initial, pair<int, int> final, int cur_turn){
            if(initial == final)return 0;
            Piece * starting_piece = b.cellPtr(initial.first, initial.second), * ending_piece = b.cellPtr(final.first, final.second);
            if(starting_piece == NULL || (*starting_piece).colour() != cur_turn)return 0;
            if(ending_piece != NULL and (*starting_piece).colour() == (*ending_piece).colour())return 0;
            if((*starting_piece).canMove(b.allCells(), initial, final) == 0)return 0;
            return 1;
        }
        bool isCausingCheck(pair<int, int> initial, pair<int, int> final, int cur_turn){
            Board cur = b;
            Piece * starting_piece = b.cellPtr(initial.first, initial.second);
            b.set(final.first, final.second, starting_piece);
            b.set(initial.first, initial.second, NULL);
            bool ret = isCheck(cur_turn);
            b = cur;
            return ret;
        }
        bool move(){
            if(!isValid(start,end, turn) || isCausingCheck(start, end, turn))return 0;
            Piece * starting_piece = b.cellPtr(start.first, start.second);
            if((*starting_piece).name() == 'p' and end.first == 7 || end.first == 0){
                promotemsg();
                string s;
                next :
                    cin >> s;
                    if(s == "Rook")starting_piece = new Rook((*starting_piece).colour());
                    else if(s == "Bishop")starting_piece = new Bishop((*starting_piece).colour());
                    else if(s == "Knight")starting_piece = new Knight((*starting_piece).colour());
                    else if(s == "Queen")starting_piece = new Queen((*starting_piece).colour());
                    else {cout << "You dumb dumb Man who asked u to play chess on such a tough platform. Enter again!\n";goto next;}
            }
            b.set(end.first, end.second, starting_piece);
            b.set(start.first, start.second, NULL);
            turn = (turn+1)%2;
            if(isCheck(turn) and isStaleMate(turn)){cout << "CheckMate" << endl;exit(0);}
            if(isCheck(turn)){b.show();cout << "Check\n";}
            if(isStaleMate(turn)){
                b. show();
                cout << "Draw\n";
                exit(1);
            }
            return 1;
        }
        bool isStaleMate(bool col){
            for(int i = 0; i < sz; i++){
                for(int j = 0; j < sz; j++){
                    Piece* cur_piece = b.cellPtr(i, j);
                    if(cur_piece != NULL and (*cur_piece).colour() == col){
                        for(int x = 0; x < sz; x++){
                            for(int y = 0; y < sz; y++){
                                if(isValid({i, j}, {x, y}, col) and isCausingCheck({i, j}, {x, y}, col) == 0){return 0;}
                            }
                        }
                    }
                }
            }
            return 1;
        }
        bool isCheck(bool col){
            for(int i = 0; i < sz; i++){
                for(int j = 0; j < sz; j++){
                    Piece* cur_piece = b.cellPtr(i, j);
                    if(cur_piece != NULL and (*cur_piece).name() == 'K' and (*cur_piece).colour() == col){
                        for(int x = 0; x < sz; x++){
                            for(int y = 0; y < sz; y++){
                                pair<int, int> ini = {x, y}, fni = {i, j};
                                if(isValid(ini, fni, (col^1))){return 1;}
                            }
                        }
                        return 0;
                    }
                }
            }
        }
        void play(){
            show();
            cout << "First Move " << players[0] << " ?\n";
            while(getMove()){
                if(check(start.first)&&check(start.second)&&check(end.first)&&check(end.second)){
                    bool x = move();
                    if(x)cout << "Next Move " << players[turn] << " ?\n", show();
                    else cout << "Invalid Move! Think again.\n";
                }
                else cout << "Invalid Move! Think again.\n";
            }
        }
};
int main(){
    Game b("asd","bsd");
    b.play();
}
/*
5 2 5 4
5 7 5 5
6 1 3 4
4 7 4 6
4 1 6 3
2 8 3 6
6 3 6 7
*/
