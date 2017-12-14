
#include <iostream>
#include <vector>
#include <stdio.h>
#include <limits.h>
#include "tetrominoes.h"
#include "IOFunction.h"
#include "MoveTetris.h"
#include <conio.h>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;
#define pb(x) push_back(x)




int Game(){
    int score=0,x,y;
    Piece W,Wi;
    srand((unsigned)time(NULL));
    for(x=0;x<Height;x++)for(y=0;y<Width;y++)board[x][y]=0;//Clean board
    
    while(true){
        
        W.setP(rand()%6); //Random piece
        x=0,y=0;//Start position
        ///Change the posible start
        
        
        if(!posible(W,x,y))break;
        changePiece(W,x,y,1);
        clearScreen();
        printBoard();
       
        
        
        while (true){
            
            if (kbhit())
                read_move();
            else
                if (cv.wait_for(lck, chrono::milliseconds(700)) == cv_status::timeout)
                    movei=5;//Fall one block
            
            if(!doMove(W,x,y))
                break;
        }
        score+=deleteMultipleLines();
    }
    return score;
}


int main(){
 
 
    int score;
    printMenu();
    while(true){
        clearScreen();
        score=Game();
        finishGame(score);
    }
}