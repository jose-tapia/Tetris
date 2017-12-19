
#include <iostream>
#include <vector>
#include "tetrominoes.h"
#include "IOFunction.h"
#include "MoveTetris.h"

using namespace std;
#define pb(x) push_back(x)

int movei;
bool newinput,onGame;

void read_move(){
    char x;
    while(true){
        while(onGame){
            x=readChar();
            if('a'<=x&&x<='z')x=x-'a'+'A';
            switch (x) {
                case 'A': movei=0; break;//left
                case 'D': movei=1; break;//right
                case 'O': movei=2; break;//rotate L
                case 'P': movei=3; break;//rotate R
                case 'S': movei=4; break;//drop
                default:  movei=5; break;//wrong key
            }
            newinput=1;
        }
    }
}

int Game(){
    int x,y;
    Piece W,Wi;
    srand((unsigned)time(NULL));
    newinput=0;
    onGame=1;
    resetGame();

    nextPiece=randomPiece();
    while(true){

        //Introduce a new Piece.
        W=nextPiece;
        nextPiece=randomPiece(),x=0,y=(rand()%7);
        if(!posible(W,x,y))break;
        changePiece(W,x,y,2);
        clearScreen();
        printBoard();

        while (true){
            //Wait for an action.
            this_thread::sleep_for(chrono::milliseconds(600));

            if(newinput)newinput=0;//If we had newinput, dont reset movei
            else movei=5;//else, dont read new input, so

            if(!doMove(W,x,y,movei))break;
            if(movei!=5){
                this_thread::sleep_for(chrono::milliseconds(100));
                movei=5;
                if(!doMove(W,x,y,movei))break;
            }
        }
        for(int i=0;i<Width;i++)if(board[0][i])break;

        currentScore+=deleteMultipleLines();
    }
    onGame=0;
    return currentScore;
}


int main(){
    int score;
    readRecords();
    printMenu();
    thread th(read_move);
    while(true){
        clearScreen();
        score=Game();
        gameOver(score);
    }
    th.join();
}
