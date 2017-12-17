//
//  MoveTetris.h
//  Tetris
//
//  Created by Jose Manuel Tapia Avitia on 13/12/17.
//  Copyright (c) 2017 Jose Manuel Tapia Avitia. All rights reserved.
//

#ifndef Tetris_MoveTetris_h
#define Tetris_MoveTetris_h



#include "IOFunction.h"


using namespace std;
#define pb(x) push_back(x)



 
bool posible(Piece A, int x,int y){
    int i,j,L=(int)A.P.size();
    for(i=0;i<L;i++)for(j=0;j<L;j++){
        if(A.P[i][j])
            if(i+x>=Height||j+y>=Width||i+x<0||j+y<0||board[i+x][j+y])
                return false;
    }
    return true;
}

void changePiece(Piece A,int x,int y,int v){
    int i,j,L=(int)A.P.size();
    for(i=0;i<L;i++)for(j=0;j<L;j++)
        if(A.P[i][j])board[i+x][j+y]=v;
}

void deleteLine(int l){
    int i,j;
    for(i=l;i>0;i--)for(j=0;j<Width;j++)
        board[i][j]=board[i-1][j];
}
int deleteMultipleLines(){
    int i,j,complete,microScore=0;
    for(i=0;i<Height;i++){
        complete=1;
        for(j=0;j<Width;j++)
            if(!board[i][j])complete=0;
        if(complete)deleteLine(i),microScore++;
    }
    return microScore;
}

bool doMove(Piece &W,int &x,int &y,int movei){
    Piece Wi;
    //Do the move
    changePiece(W,x,y,0);
    switch(movei){
        case 0:
            if(posible(W,x,y-1))y--;
            changePiece(W,x,y,1);
            break;
        case 1:
            if(posible(W,x,y+1))y++;
            changePiece(W,x,y,1);
            break;
        case 2:
            Wi=rotateL(W);
            if(posible(Wi,x,y))W=Wi;
            changePiece(W,x,y,1);
            break;
        case 3:
            Wi=rotateR(W);
            if(posible(Wi,x,y))W=Wi;
            changePiece(W,x,y,1);
            break;
        case 4:
            while(posible(W,x+1,y))x++;
            changePiece(W,x,y,1);
            break;
        default:
            if(posible(W,x+1,y))
                changePiece(W,++x,y,1);
            else {
                changePiece(W,x,y,1);
                return false;
            }
            break;
    }
    clearScreen();
    printBoard();
    return true;
}

#endif
