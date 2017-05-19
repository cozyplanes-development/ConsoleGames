//move snake
//make tail, remove tail
//collision with wall
//collision with itself
//collision with fruit

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <Windows.h>
#include <time.h>

#define DEFAULT_X 0
#define DEFAULT_Y 0

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
            }else if(map[i][j] == EMPTY){
                gotoxy(i,j);
                printf(" ");
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

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    map[snake_x][snake_y] = 2;
}
void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    map[snake_x][snake_y] = 0;
}
//get snake x, y and move snake
int moveSnake(MData map[MAP_SIZE][MAP_SIZE],int * px, int * py,int way){
    if(way == UP){
        if(*py < 2) return -1;
        setSnake(map, *px, (*py)-1);
        removeSnake(map, *px, *py);
        *py -= 1;
        printf("u\n");
        return UP;
    }
    if(way == DOWN){
        if(*py > MAP_SIZE-3) return -1;
        setSnake(map, *px, (*py)+1);
        removeSnake(map, *px, *py);
        *py += 1;
        printf("d\n");
        return DOWN;
    }
    if(way == LEFT){
        if(*px < 2) return -1;
        setSnake(map, (*px)-1, *py);
        removeSnake(map, *px, *py);
        *px -= 1;
        printf("l\n");
        return LEFT;
    }
    if(way == RIGHT){
        if(*px > MAP_SIZE-3) return -1;
        setSnake(map, (*px)+1, *py);
        removeSnake(map, *px, *py);
        *px += 1;
        printf("r\n");
        return RIGHT;
    }
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE]) {
    int key, savedKey=0;
    int fruit = 0; //0 => no fruite, 1=> one fruit
    int snake_x = MAP_SIZE/2, snake_y = MAP_SIZE/2;
    setSnake(map, snake_x, snake_y);

    while (1) {
        gotoxy(DEFAULT_X, DEFAULT_Y);
        if (fruit == 0) {          // draw fruit
            fruit = setFruit(map);
        }

        drawMap(map);           // draw map include snake, fruit and wall
        Sleep(1000/30);

        if(kbhit()) {
            key = getch();
            if (key == 't' || key == 'T') {     //exit
                return;
            }
            if (key == 'p' || key == 'P'){
                system("pause");
                gotoxy(DEFAULT_X,MAP_SIZE+6);
                printf("    You are so beautiful M.J.          ");
                //printf("                                            ");
                gotoxy(DEFAULT_X, DEFAULT_Y);
            }
            if (key == 224 || key == 0) {
                key = getch();
                switch (key) {
                    case UP:
                        savedKey = moveSnake(map, &snake_x, &snake_y, UP);
                        break;
                    case LEFT:
                        savedKey = moveSnake(map, &snake_x, &snake_y, LEFT);
                        break;
                    case RIGHT:
                        savedKey = moveSnake(map, &snake_x, &snake_y, RIGHT);
                        break;
                    case DOWN:
                        savedKey = moveSnake(map, &snake_x, &snake_y, DOWN);
                        break;
                    default:
                        break;
                }
            }
        }else{
            if(savedKey!=0) moveSnake(map, &snake_x, &snake_y, savedKey);
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
