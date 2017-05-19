//move snake -> 70%
//make tail, remove tail
//collision with wall
//collision with itself
//collision with fruit -> 50%
//read best score from file.
//write best score to file


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
#define COLLISION 10

typedef int MData;

typedef struct _fruitxy{
    int x;
    int y;
} FruitPos;

typedef struct _snakexp{
    int x;
    int y;
} SnakePos;

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
int drawStartMenu(){
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
            return TRUE;
        }
        if(keyDown == 't' || keyDown == 'T'){
            return FALSE;
        }

        gotoxy(DEFAULT_X+4,DEFAULT_Y+7);
        printf("-- press 's' to start --");
        Sleep(1000/3);
        gotoxy(DEFAULT_X+4,DEFAULT_Y+7);
        printf("                         ");
        Sleep(1000/3);
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
void drawMainMap(MData map[MAP_SIZE][MAP_SIZE]){
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

}
void drawSubMap(int score, int best){

    gotoxy(DEFAULT_X,MAP_SIZE+1);
    printf("Score : %4d", score);
    gotoxy(DEFAULT_X,MAP_SIZE+2);
    printf("Best  : %4d", best);
    gotoxy(DEFAULT_X+8,MAP_SIZE+5);
    printf("[Exit - 't' / Pause - 'p']\n");

}

int setFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * pf){
// i,j >0  &&  i,j < MAP_SIZE-1i
    int i, j;
    srand((unsigned int)time(NULL));
    while(1){
        i=rand()%(MAP_SIZE-2) + 1;
        j=rand()%(MAP_SIZE-2) + 1;
        if(map[i][j] == EMPTY){
            map[i][j] = 5;
            pf->x = i;
            pf->y = j;
            return 1;
        }
    }
}

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int *snake_x, int *snake_y){
    map[*snake_x][*snake_y] = 2;
}
void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int *snake_x, int *snake_y){
    map[*snake_x][*snake_y] = 0;
}
//get snake x, y and move snake
int moveSnake(MData map[MAP_SIZE][MAP_SIZE],int * px, int * py,int way){
    if(way == UP){
        if(*py < 2) return COLLISION;
        removeSnake(map, px, py);
        *py -= 1;
        setSnake(map, px, py);
        printf("u\n");
        return UP;
    }
    if(way == DOWN){
        if(*py > MAP_SIZE-3) return COLLISION;
        removeSnake(map, px, py);
        *py += 1;
        setSnake(map, px, py);
        printf("d\n");
        return DOWN;
    }
    if(way == LEFT){
        if(*px < 2) return COLLISION;
        removeSnake(map, px, py);
        *px -= 1;
        setSnake(map, px, py);
        printf("l\n");
        return LEFT;
    }
    if(way == RIGHT){
        if(*px > MAP_SIZE-3) return COLLISION;
        removeSnake(map, px, py);
        *px += 1;
        setSnake(map, px, py);
        printf("r\n");
        return RIGHT;
    }
}

int colWithFruit(SnakePos * ps, FruitPos * pf){
    //meet;
    if(ps->x == pf->x && ps->y == pf->y){
        return TRUE;
    }
    return FALSE;
}
int colWithWall(SnakePos * ps){
    if(ps->x <2)
    return TRUE;
    return FALSE;
}
void GameOver(int score){
    gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-5);
    printf("===<GAME OVER>===\n");
    gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-3);
    //printf("Do again Bro\n");
    //gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-2);
    printf("Your Score : %d\n", score);
    gotoxy(DEFAULT_X+8,MAP_SIZE+5);
    printf("\n");
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE]) {
    int best = 100; //fake
    int score = 0;
    int key, savedKey=0;
    int fruit = 0; //0 => no fruite, 1=> one fruit
    FruitPos fpos;
    SnakePos spos = {MAP_SIZE/2, MAP_SIZE/2};
    setSnake(map, &spos.x, &spos.y);

    while (1) {
        gotoxy(DEFAULT_X, DEFAULT_Y);
        if (fruit == 0) {          // draw fruit
            fruit = setFruit(map, &fpos);
        }

        drawMainMap(map);           // draw map include snake, fruit and wall
        drawSubMap(score, best);
        Sleep(1000/20);             // snake speed
         if(colWithFruit(&spos, &fpos) == TRUE){
             fruit = 0;
             score += 5;
         }

        if(kbhit()) {
            key = getch();
            if (key == 't' || key == 'T') {     //exit
                return;
            }
            if (key == 'p' || key == 'P'){
                system("pause");
                gotoxy(DEFAULT_X,MAP_SIZE+6);
                //printf("    You are so beautiful M.J.          ");
                printf("                                            ");
                gotoxy(DEFAULT_X, DEFAULT_Y);
            }
            if (key == 224 || key == 0) {
                key = getch();
                switch (key) {
                    case UP:
                        savedKey = moveSnake(map, &spos.x, &spos.y, UP);
                        if(savedKey == COLLISION){
                            GameOver(score);
                            return;
                        }
                        break;
                    case LEFT:
                        savedKey = moveSnake(map, &spos.x, &spos.y, LEFT);
                        if(savedKey == COLLISION){
                            GameOver(score);
                            return;
                        }
                        break;
                    case RIGHT:
                        savedKey = moveSnake(map, &spos.x, &spos.y, RIGHT);
                        if(savedKey == COLLISION){
                            GameOver(score);
                            return;
                        }
                        break;
                    case DOWN:
                        savedKey = moveSnake(map, &spos.x, &spos.y, DOWN);
                        if(savedKey == COLLISION){
                            GameOver(score);
                            return;
                        }
                        break;
                    default:
                        break;
                }
            }
        }else{
            if(savedKey!=0) {
                if(moveSnake(map,  &spos.x, &spos.y, savedKey) == COLLISION){
                    GameOver(score);
                    return ;
                }
            }
        }
    }

}

int main() {
    MData map[MAP_SIZE][MAP_SIZE] ;

    while(1){
        mapInit(map);
        system("mode con: cols=44 lines=30");   //console size
        if(drawStartMenu() == FALSE) break;
        system("cls");
        GameStart(map);
        system("pause");

    }

    return 0;
}
