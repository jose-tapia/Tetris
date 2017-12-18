//
//  tests.h
//  Tetris
//
//  Created by Jose Manuel Tapia Avitia on 13/12/17.
//  Copyright (c) 2017 Jose Manuel Tapia Avitia. All rights reserved.
//

#ifndef __Tetris__tests__
#define __Tetris__tests__

#include <iostream>
#include <vector>
#include <stdio.h>
#include <limits.h>
#include <thread>
#include <chrono>


using namespace std;
#define pb(x) push_back(x)



struct Piece{
	int Type;
	vector<vector<int> >P;
	void I(){
		P.clear(),Type=0;
		P.pb(vector<int>(4,0));
		P.pb(vector<int>(4,1));
		P.pb(vector<int>(4,0));
		P.pb(vector<int>(4,0));
	}
	void L(){
		P.clear(),Type=1;
		P.pb(vector<int>(3,0));
		P[0][2]=1;
		P.pb(vector<int>(3,1));
		P.pb(vector<int>(3,0));
	}
	void O(){
		P.clear(),Type=2;
		P.pb(vector<int>(2,1));
		P.pb(vector<int>(2,1));
	}
	void S(){
		P.clear(),Type=3;
		P.pb(vector<int>(3,1));
		P.pb(vector<int>(3,1));
		P[0][0]=0,P[1][2]=0;
		P.pb(vector<int>(3,0));
	}
	void T(){
		P.clear(),Type=4;
		P.pb(vector<int>(3,0));
		P[0][1]=1;
		P.pb(vector<int>(3,1));
		P.pb(vector<int>(3,0));
	}
	void Z(){
		P.clear(),Type=5;
		P.pb(vector<int>(3,1));
		P.pb(vector<int>(3,1));
		P[0][2]=0,P[1][0]=0;
		P.pb(vector<int>(3,0));
	}
    void setP(int Ti){
        switch(Ti){
            case 0: I();break;
            case 1: L();break;
            case 2: O();break;
            case 3: S();break;
            case 4: T();break;
            case 5: Z();break;
        }
    }
};

Piece rotateL(Piece A){
    Piece w=A;
    int i,j,L=(int)A.P.size();
    for(i=0;i<L;i++)for(j=0;j<L;j++)
        w.P[i][j]=A.P[j][L-i-1];
    return w;
}

Piece rotateR(Piece A){
	Piece w=A;
	int i,j,L=(int)A.P.size();
	for(i=0;i<L;i++)for(j=0;j<L;j++)
		w.P[i][j]=A.P[L-j-1][i];
    return w;
}

Piece randomPiece(){
    Piece W;
    W.setP(rand()%6);
    int k=rand()%4;
    while(k--)W=rotateL(W);
    return W;
}
Piece nextPiece;
const int Width=10,Height=23;
int board[Height][Width],currentScore;

inline void resetGame(){ currentScore=0;for(int x=0;x<Height;x++)for(int y=0;y<Width;y++)board[x][y]=0; }//Clean board



#endif /* defined(__Tetris__tests__) */
