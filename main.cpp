
#include <iostream>
#include <vector>
#include "tetrominoes.h"
#include "IOFunction.h"
#include "MoveTetris.h"


using namespace std;
#define pb(x) push_back(x)


int movei;
bool newinput;
void read_move(){
    while(true){
        char x=readChar();
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

int Game(){
    int score=0,x,y;
    Piece W,Wi;
    srand((unsigned)time(NULL));
    cleanBoard();
    
    while(true){
        
        //Introduce a new Piece.
        W.setP(rand()%6),x=0,y=(rand()%7);
        if(!posible(W,x,y))break;
        changePiece(W,x,y,1);
        clearScreen();
        printBoard();
        
        while (true){
            //Wait for an action.
            this_thread::sleep_for(chrono::milliseconds(700));
            
            if(newinput)newinput=0;//If had newinput, dont reset movei
            else movei=5;//else, dont read new input, so
            
            if(!doMove(W,x,y,movei))break;
        }
        score+=deleteMultipleLines();
    }
    return score;
}


int main(){
    thread th(read_move);

 
    int score;
    printMenu();
    while(true){
        clearScreen();
        score=Game();
        finishGame(score);
    }
    th.join();
}