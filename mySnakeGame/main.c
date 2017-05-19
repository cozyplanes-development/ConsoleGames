//move snake
//collision

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <Windows.h>
#include <time.h>

#define DEFAULT_X 0
#define DEFAULT_Y 0

//#define MAP_X_SIZE 32
//#define MAP_Y_SIZE 12
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define MAP_SIZE 22

#define WALL 1
#define EMPTY 0
#define HEAD 2
#define FRUIT 5



typedef int MData;

//keyboard input
int getKeyDown() {
    if(kbhit()) return getch();
    return -1;
}

//move cursor
void gotoxy(int x, int y){
	COORD Pos;
	Pos.X = 2*x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//show start menu
void drawStartMenu(){
    gotoxy(DEFAULT_X,DEFAULT_Y);
 	printf("================ Snake Game ================");
    gotoxy(DEFAULT_X,DEFAULT_Y+2);
    printf("> Key  : up, down, left, right,");
    gotoxy(DEFAULT_X,DEFAULT_Y+3);
    printf("> Exit : 't'");

    gotoxy(DEFAULT_X+12,DEFAULT_Y+10);
    printf("made by BlockDMask.");

    while(1){
        int keyDown = getKeyDown();
            if(keyDown == 's' || keyDown == 'S') {
                break;
            }
        gotoxy(DEFAULT_X+4,DEFAULT_Y+7);
        printf("-- press 's' to start --");
        sleep(1);
        gotoxy(DEFAULT_X+4,DEFAULT_Y+7);
        printf("                         ");
        sleep(1);
    }

}

void mapInit(MData map[MAP_SIZE][MAP_SIZE]){
    int i,j;

    for(i=0; i<MAP_SIZE; i++){
        if(i==0 || i==MAP_SIZE-1){
            for(j=0; j<MAP_SIZE;j++){
                map[i][j] = WALL;
            }
        }else{
            for(j=0; j<MAP_SIZE;j++){
                if(j==0 || j==MAP_SIZE-1)
                    map[i][j] = WALL;
                else
                    map[i][j] = EMPTY;
            }
        }

    }
}

//draw game map
void drawMap(MData map[MAP_SIZE][MAP_SIZE]){
    int i, j;
    for(i=0; i<MAP_SIZE;i++){
        for(j=0;j<MAP_SIZE;j++){
            if(map[i][j]==WALL){
                gotoxy(i,j);
                printf("*");
            }else if(map[i][j] == HEAD){
                gotoxy(i,j);
                printf("s");
            }else if(map[i][j] == FRUIT){
                gotoxy(i,j);
                printf("+");
            }
        }
    }

    gotoxy(DEFAULT_X,MAP_SIZE+1);
    printf("Score : ");
    gotoxy(DEFAULT_X,MAP_SIZE+2);
    printf("Best  : ");
    gotoxy(DEFAULT_X+8,MAP_SIZE+5);
    printf("[Exit - 't' / Pause - 'p']\n");

}

void setSnake(MData map[MAP_SIZE][MAP_SIZE]){
    map[MAP_SIZE/2][MAP_SIZE/2] = 2;
}

int setFruit(MData map[MAP_SIZE][MAP_SIZE]){
// i,j >0  &&  i,j < MAP_SIZE-1i
    int i, j;
    srand((unsigned int)time(NULL));
    while(1){
        i=rand()%(MAP_SIZE-2) + 1;
        j=rand()%(MAP_SIZE-2) + 1;
        if(map[i][j] == EMPTY){
            map[i][j] = 5;
            return 1;
        }
    }
}

int moveSnake(MData map[MAP_SIZE][MAP_SIZE], int way){
    if(way == UP){
        printf("u\n");
    }
    if(way == DOWN){
        printf("d\n");
    }
    if(way == LEFT){
        printf("l\n");
    }
    if(way == RIGHT){
        printf("r\n");
    }
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE]) {
    int key;
    int fruit = 0; //0 => no fruite, 1=> one fruit
    setSnake(map);

    while (1) {
        gotoxy(DEFAULT_X, DEFAULT_Y);
        if (fruit == 0) {          // draw fruit
            fruit = setFruit(map);
        }
        drawMap(map);           // draw map include snake, fruit and wall

        if(kbhit()) {
            key = getch();
            if (key == 't' || key == 'T') {     //exit
                return;
            }
            if (key == 'p' || key == 'P'){
                system("pause");
                gotoxy(DEFAULT_X,MAP_SIZE+6);
                printf("                                      ");
                gotoxy(DEFAULT_X, DEFAULT_Y);
            }
            if (key == 224 || key == 0) {
                key = getch();
                switch (key) {
                    case UP:
                        moveSnake(map, UP);
                        break;
                    case LEFT:
                        moveSnake(map, LEFT);
                        break;
                    case RIGHT:
                        moveSnake(map, RIGHT);
                        break;
                    case DOWN:
                        moveSnake(map, DOWN);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main() {
    MData map[MAP_SIZE][MAP_SIZE] ;
    mapInit(map);
    system("mode con: cols=44 lines=30");   //console size
    drawStartMenu();
    system("cls");
    GameStart(map);
    system("pause");

    return 0;
}
