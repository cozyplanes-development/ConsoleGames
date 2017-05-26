//v1.0
//draw background               o
//draw blocks                   x
//rotate blocks.                x
//drop the blocks.              x
//read best score from file     x
//write best score to file      x

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define MAP_SIZE_W 10
#define MAP_SIZE_H 20
#define HALF_W 15
#define TIME_H 10

#define EXIT 100

typedef char MData ;

//hide cursor
void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//move cursor.
void gotoxy(int x, int y){
    COORD P;
    P.X = 2*x;
    P.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), P);
}

//get keyboard input.
int getKeyDown(){
    if(kbhit()) return getch();
    else return -1;
}

typedef struct _shapeblock{
    int shape[4][4];
} BlockShape;
//////////////////////////////////////////////////DRAW/////////////////////////////////////////////////////////////////
void drawWall(MData map[MAP_SIZE_H][MAP_SIZE_W]){
    int h, w;
    for(h=0; h<=MAP_SIZE_H +1; h++){
        for(w=0; w<=MAP_SIZE_W +1; w++){
            gotoxy(w+1,h+1);
            if(h==0 || w==0 || h==MAP_SIZE_H+1 || w==MAP_SIZE_W+1)
                printf("¢Ë");
        }
        printf("\n");
    }
    gotoxy(HALF_W, 1);
    printf("<Next>");

    for(h=2; h<=7 ;h++){
        for(w=HALF_W ; w<=HALF_W+5; w++){
            if(w==HALF_W || w==HALF_W+5 || h==2 || h==7){
                gotoxy(w, h);
                printf("¢Ë");
            }
        }
    }
    gotoxy(HALF_W, TIME_H);
    printf("Time  : ");
    gotoxy(HALF_W, TIME_H+1);
    printf("Score : ");
    gotoxy(HALF_W, TIME_H+2);
    printf("Best  : ");
    gotoxy(HALF_W, TIME_H+12);
    printf("<Exit : 't' / Pause : 'p'>");
}

int drawFrontMenu(){

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    int keyInput;
    gotoxy(1,2);
    printf("=====================================================");
    gotoxy(1,3);
    SetConsoleTextAttribute(hand, 10);
    printf("=================== T E T R I S =====================");
    SetConsoleTextAttribute(hand, 7);
    gotoxy(1,4);
    printf("=====================================================\n");

    gotoxy(2,6);
    printf("Left : ¡ç \n");
    gotoxy(2,7);
    printf("Right : ¡æ \n");
    gotoxy(2,8);
    printf("Rotation : ¡è \n");
    gotoxy(2,9);
    printf("Down: space \n");
    gotoxy(2,10);
    printf("Exit: 't' \n");

    gotoxy(15,20);
    printf(" >> Made by BlockDMask.");
    gotoxy(15,21);
    printf(" >> BlockDMask@gmail.com");

    while(1){
        keyInput = getKeyDown();
        if(keyInput == 's' || keyInput == 'S') break;
        if(keyInput == 't' || keyInput == 'T') break;

        gotoxy(7, 15);
        SetConsoleTextAttribute(hand, 10);
        printf(" === press 's' to start ===");
        SetConsoleTextAttribute(hand, 7);
        Sleep(1000/2);
        gotoxy(7, 15);
        printf("                            ");
        Sleep(1000/2);
    }
    return keyInput;
}

void drawMap(MData map[MAP_SIZE_H][MAP_SIZE_W]){
    int h, w;
    for(h=0; h<MAP_SIZE_H; h++){
        for(w=0; w<MAP_SIZE_W; w++){
            gotoxy(w+2,h+2);
            if(map[h][w] == 0){
                printf("¡¤");
            }else if(map[h][w] ==1){
                printf("¡á");
            }
        }
                printf("\n");
    }
    printf("\n");
    printf("\n");
}

//show next shape, score, time, best score.
void drawSubMap(int score, int shape){
    gotoxy(HALF_W + 4, TIME_H);
    printf("%4d", 20);
    gotoxy(HALF_W + 4, TIME_H+1);
    printf("%4d", 2);
    gotoxy(HALF_W + 4, TIME_H+2);
    printf("%4d", 10);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameStart(MData map[MAP_SIZE_H][MAP_SIZE_W]){
    int key;
    int score =0, shape=0;




    drawMap(map);
    while(1){
        drawSubMap(score, shape);
        key = getKeyDown();
        if(key == 't' || key =='T') break;
        if(key == 'p' || key == 'P'){
            system("pause");
        }
    }
    return EXIT;
}



int main() {
    system("color 7");                      //console color
    system("mode con: cols=58 lines=25");   //console size
    char map[MAP_SIZE_H][MAP_SIZE_W] ={0};   //map
    int key;
    hidecursor();

    while(1){
        key = drawFrontMenu();
        if(key == 't' || key == 'T') break;
        system("cls");
        drawWall(map);
        GameStart(map);
        Sleep(1000/3);
        system("cls");
    }
    return 0;
}