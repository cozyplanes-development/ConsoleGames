//v1.0
//draw background               o
//draw blocks                   o
//rotate blocks.                o
//go left, go right the block.  o
//drop the block.               x
//read best score from file     x
//write best score to file      x

//collision with side wall
//collision with bottom wall
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define MAP_SIZE_W 10
#define MAP_SIZE_H 20
#define HALF_W 15
#define TIME_H 10
#define EXIT 100

#define WALL 5
#define EMPTY 0
#define BLOCK 1

#define UP 72
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ESC 27
#define DOWN 80

typedef char MData ;

typedef struct _currentlocation{
    int X;
    int Y;
} Location;


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
    printf("Best  : ");
    gotoxy(HALF_W, TIME_H+2);
    printf("Score : ");
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
            if(map[h][w] == EMPTY){
                printf("¡¤");
            }
        }
        printf("\n");
    }

}
//show next shape, score, time, best score.
void drawSubMap(int sec, int best, int score){
    gotoxy(HALF_W + 4, TIME_H);
    printf("%4d", sec);
    gotoxy(HALF_W + 4, TIME_H+1);
    printf("%4d", best);
    gotoxy(HALF_W + 4, TIME_H+2);
    printf("%4d", score);
}

void drawShape(MData map[MAP_SIZE_H][MAP_SIZE_W],int shape[4][4], Location curLoc){
    int h, w;

    for(h=0; h<4;h++){
        for(w=0; w<4;w++){
            if(shape[h][w] ==BLOCK){
                map[curLoc.Y+ h][curLoc.X +w]=BLOCK;
                gotoxy(curLoc.X+2+w,curLoc.Y+2+h);
                printf("¡á");
            }
        }
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void startTime(){
    int i;
    for(i=0; i<2;i++){
        gotoxy(1,0);
        printf("Start : %d sec", 2-i);
        Sleep(1000);
    }
    gotoxy(1,0);
    printf("                       ");
}
void mapInit(MData map[MAP_SIZE_H][MAP_SIZE_W]){
    int i, j=0;
    for(i=0;i<MAP_SIZE_H;i++){
        for(j=0; j<MAP_SIZE_W; j++){
            map[i][j] = EMPTY;
        }
    }
}
void locationInit(Location * curLoc){
    curLoc->Y =0;
    curLoc->X =0;
}
void copyBlock(int blockShape[4][4], int copy[4][4]){
    int i, j;
    for(i=0;i<4;i++){
        for(j=0; j<4;j++){
            blockShape[i][j] = copy[i][j];
        }
    }
}
void setBlock(int blockShape[4][4]){

    int shapeLong[4][4] = {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}};
    int shapeRock[4][4] = {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}};
    int shapeHorn[4][4] = {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}};
    int shapeStair[4][4] = {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}};
    int shapeRStair[4][4] = {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}};
    int shapeNienun[4][4] = {{0,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,0}};
    int shapeRNieun[4][4] = {{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}};

    srand((unsigned int)(time(NULL)));

    switch(rand()%7) {
        case 0:
            copyBlock(blockShape, shapeLong);
            break;
        case 1:
            copyBlock(blockShape, shapeRock);
            break;
        case 2:
            copyBlock(blockShape, shapeHorn);
            break;
        case 3:
            copyBlock(blockShape, shapeStair);
            break;
        case 4:
            copyBlock(blockShape, shapeRStair);
            break;
        case 5:
            copyBlock(blockShape, shapeNienun);
            break;
        case 6:
            copyBlock(blockShape, shapeRNieun);
            break;
        default :
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void removeShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location * curLoc){
    int h, w;
    for(h=0; h<4;h++){
        for(w=0; w<4;w++){
                map[curLoc->Y + h][curLoc->X + w]=EMPTY;
        }
    }
}
void goLeft(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4], Location *curLoc){
    removeShape(map, blockShape,curLoc);
    (curLoc->X)--;
}
void goRight(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4], Location *curLoc){
    removeShape(map, blockShape,curLoc);
    (curLoc->X)++;

}

void goDown(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location *curLoc){
    Sleep(1000/10);
}

void rotate(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4]){
    int i, j;
    int tmp[4][4];
    for(i=0; i<4;i++){
        for(j=0; j<4;j++){
            tmp[j][3-i] = blockShape[i][j];
        }
    }
    mapInit(map);
    for(i=0; i<4;i++){
        for(j=0; j<4;j++){
            blockShape[i][j] = tmp[i][j];
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameStart(MData map[MAP_SIZE_H][MAP_SIZE_W]){
    int key;
    int score =0, bestscore =0, sec=0;
    int blockShape[4][4] ={0};
    Location curLoc = {2,2};
    mapInit(map);
    drawWall(map);
    drawMap(map);
    // startTime();

    setBlock(blockShape);
    locationInit(&curLoc);


    while(1){
        //goDown(map, blockShape, &curLoc);
        drawSubMap(sec,bestscore,score);
        drawShape(map,blockShape, curLoc);
        drawMap(map);

        key = getKeyDown();
        if(key == 't' || key =='T') break;
        if(key == 'p' || key == 'P'){
            system("pause"); system("cls");
            drawMap(map); drawWall(map);
        }
        if(key == SPACE){
            gotoxy(1, 24);
            printf("     ");
            gotoxy(1, 24);
            printf("SPACE");
        }
        if(key==224 || key ==0){
            key = getch();
            if(key == UP){
                rotate(map, blockShape);
                gotoxy(1, 24);
                printf("     ");
                gotoxy(1, 24);;
                printf("UP");
            }else if(key == LEFT){
                goLeft(map, blockShape, &curLoc);
                gotoxy(1, 24);
                printf("     ");
                gotoxy(1, 24);
                printf("LEFT");
            }else if(key == RIGHT){
                goRight(map, blockShape, &curLoc);
                gotoxy(1, 24);
                printf("     ");
                gotoxy(1, 24);
                printf("RIGHT");
            }

        }
        Sleep(1000/10);
    }
    return EXIT;
}



int main() {
    char map[MAP_SIZE_H][MAP_SIZE_W] ={0};   //map
    int key;
    hidecursor();

    system("color 7");                      //console color
    system("mode con: cols=57 lines=25");   //console size

    while(1){
        key = drawFrontMenu();
        if(key == 't' || key == 'T') break;
        system("cls");
        GameStart(map);
        Sleep(1000/3);
        system("cls");
    }
    return 0;
}
