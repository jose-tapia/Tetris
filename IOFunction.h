//
//  printablethings.h
//  Tetris
//
//  Created by Jose Manuel Tapia Avitia on 13/12/17.
//  Copyright (c) 2017 Jose Manuel Tapia Avitia. All rights reserved.
//

#ifndef Tetris_printablethings_h
#define Tetris_printablethings_h


#include "tetrominoes.h"


using namespace std;
#define pb(x) push_back(x)

char readChar(){
    system("stty raw");
    char input = getchar();
    system("stty cooked");
    return input;
}

inline void clearScreen(){ cout<<string(100,'\n'); }
    
void printBoard(){
    int i,j;
    for(i=0;i<Width+2;i++)cout<<"#";
    cout<<"\n";
    for(i=0;i<Height;i++){
        cout<<"#";
        for(j=0;j<Width;j++){
            if(board[i][j])cout<<"O";
            else cout<<".";
        }
        cout<<"#";
        cout<<"\n";
    }
    for(i=0;i<Width+2;i++)cout<<"#";
    cout<<"\n\n";
}

void printMenu(){
    cout<<"\n\n\t\t\tTETRIS\n";
    cout<<"\nHow to play:\n";
    cout<<"\t-Press A or D for move left or right (respective) the piece.\n";
    cout<<"\t-Press O to rotate the piece 90 grade to the left, and P for the right.\n";
    cout<<"\t-Press S to drop the current piece.";
    cout<<"\nPress any key to start the game...\n";
    readChar();
}

void finishGame(int score){
    clearScreen();
    cout<<"\n\n\t\t\tTETRIS\n";
    cout<<"\n\tYour final score was... "<<score<<"!!!\n";
    cout<<"\nThank you for playing this game!\n\nIf you want to play more, press any key.\n\n\n\n\n\n";
    this_thread::sleep_for(chrono::seconds(5));
    readChar();
}


#endif
