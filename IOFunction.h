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
#include <fstream>
using namespace std;
const int MaxRecords=11;
int minRecord;
string namesR[MaxRecords];
int records[MaxRecords],cntR;
bool newinput,onGame;


char readChar(){
    system("stty raw");
    char input = getchar();
    system("stty cooked");
    if(input=='\377')return ' ';
    return input;
}
string readName(){
    string w;
    char x;
    x=' ';
    w.clear();
    while(x!='\n'){
        if(x!=' ')w.push_back(x);
        x=readChar();
    }
    return w;
}

inline void clearScreen(){ cout<<string(100,'\n'); }
    
void printBoard(){
    int i,j,L,startPrint=5;
    for(i=0;i<Width+2;i++)cout<<"#";
    cout<<"\n";
    for(i=1;i<Height;i++){
        cout<<"#";
        for(j=0;j<Width;j++){
            if(board[i][j]==2)cout<<"O";
            if(board[i][j]==1)cout<<"o";
            if(board[i][j]==0)cout<<".";
            
        }
        cout<<"#";
        
        if(i==startPrint)cout<<"\t\tTETRIS";
        if(i==startPrint+2)cout<<"\tActual score: "<<currentScore<<".";
        if(i==startPrint+4)cout<<"\tNext tetromino:";
        L=(int)nextPiece.P.size();
        if(startPrint+6<=i&&i<startPrint+6+L){
            cout<<"\t\t  ";
            for(j=0;j<L;j++){
                if(nextPiece.P[i-startPrint-6][j])cout<<"O";
                else cout<<" ";
            }
        }
        
        
        cout<<"\n";
    }
    for(i=0;i<Width+2;i++)cout<<"#";
    cout<<"\n";
}

void readRecords(){
    minRecord=0;
    string name;
    int i;
    ifstream recordsFile;
    recordsFile.open("records.data");
    if(recordsFile.eof()){
        cntR=0;
        return;
    }
    recordsFile>>cntR;
    for(i=0;i<cntR;i++){
        recordsFile>>name;
        namesR[i]=name;
        recordsFile>>records[i];
    }
    minRecord=records[i-1];
    if(cntR<10)minRecord=0;
    recordsFile.close();
}
void saveNewRecord(int score){
    string name;
    int i;

    name=readName();

    records[cntR]=score;
    namesR[cntR]=name;
    for(i=cntR;i>0;i--){
        if(records[i-1]<records[i]){
            swap(records[i],records[i-1]);
            swap(namesR[i],namesR[i-1]);
        }
    }
    if(cntR<10)cntR++;
    minRecord=records[cntR-1];
    if(cntR<10)minRecord=0;
    
    ofstream recordsFile;
    recordsFile.open("records.data");
    recordsFile<<cntR<<"\n";
    for(i=0;i<cntR;i++)
        recordsFile<<namesR[i]<<"\n"<<records[i]<<"\n";
    recordsFile.close();
    
}
void HallOfFame(){
    cout<<"\n\n\t\tHall of Fame\n\n";
    if(cntR==0){
        cout<<"\tThe Hall of Fame actually is empty :(\n\n";
        return;
    }
    for(int i=0;i<cntR;i++)
        cout<<"\t"<<i+1<<". "<<records[i]<<" - "<<namesR[i]<<"\n";
    cout<<"\n";
}

void printMenu(){
    cout<<"\n\n\t\t\tTETRIS\n";
    cout<<"\nHow to play:\n";
    cout<<"\t-Press A or D for move left or right (respective) the piece.\n";
    cout<<"\t-Press O to rotate the piece 90 grade to the left, and P for the right.\n";
    cout<<"\t-Press S to drop the current piece.\n\n";
    HallOfFame();
    cout<<"\nPress any key to start the game...\n";
    readChar();
}

void gameOver(int score){
    clearScreen();
    cout<<"\n\n\t\t\tTETRIS\n";
    cout<<"\n\t  Your final score was... "<<score<<"!!!\n";
    
    cout<<"\n\tThank you for playing this game!\n\n";
    if(score>=minRecord&&score>0){
        cout<<"\t  You got a record!!\n\n\tEnter your name for the Hall of Fame:";
        saveNewRecord(score);
    }
    cout<<"\n";
    HallOfFame();
    cout<<"If you want to play more, press any key.\n\n\n\n";

    this_thread::sleep_for(chrono::seconds(5));
    
    readChar();
}



#endif
