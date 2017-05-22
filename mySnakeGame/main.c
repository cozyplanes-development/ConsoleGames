<<<<<<< HEAD
//move snake -> 70%
//make tail, remove tail
//collision with wall
//collision with itself
//collision with fruit -> 50%
//read best score from file.
//write best score to file


=======
//move snake                    o
//make tail, remove tail        x
//collision with wall           o
//collision with itself         x
//collision with fruit          o
//read best score from file.    o
//write best score to file      o
//what about using Queue.?      ..
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <Windows.h>
#include <time.h>

#define DEFAULT_X 0
<<<<<<< HEAD
#define DEFAULT_Y 0
#define TRUE 1
#define FALSE 0

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
=======

#define DEFAULT_Y 0

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define MAP_SIZE 22

#define WALL 1
#define EMPTY 0
#define HEAD 2
#define TAIL 3
#define FRUIT 5
#define COLLISION 10

#define TRUE 1
#define FALSE 0

#define EASY 10
#define NORMAL 30
#define HARD 50
#define HELL 70


typedef int MData;

typedef struct _fruitxy{
    int x;
    int y;
    int numOfFruit;
} FruitPos;

typedef struct _snakexp{
    int x;
    int y;
    int numOfTail;
} SnakePos;

///////////////////////////QUEUE//////////////////////////////////////////

//typedef int QData;
typedef struct _mynode{
    SnakePos data;
    struct _mynode *next;
} Node;

typedef struct _myqueue{
    Node * rear;
    Node * front;
} MyQueue;
typedef MyQueue Queue;

void QueueInit(Queue * pq){
    pq->rear = NULL;
    pq->front = NULL;
}
int isEmpty(Queue * pq){
    if(pq->front == NULL)
        return TRUE;
    else
        return FALSE;
}
void Enqueue(Queue * pq, SnakePos data){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    if(pq->front == NULL){
        pq->rear = newNode;
        pq->front = newNode;
    }else{
        pq->rear->next = newNode;
        pq->rear = newNode;
    }
}
SnakePos Dequeue(Queue * pq){
    Node * delNode;
    SnakePos delData = {0,0,0};
    if(isEmpty(pq)){
        return delData;
    }

    delNode = pq->front;
    delData = delNode->data;
    pq->front = pq->front->next;
    free(delNode);
    return delData;
}
SnakePos Peek(Queue * pq){
    return pq->front->data;
}
///////////////////////////////////////////////////////////////////////////

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
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
            }
        }

    }

}
void drawSubMap(int score, int best){

<<<<<<< HEAD
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
=======

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
            }else if(map[i][j] == TAIL){
                gotoxy(i,j);
                printf("o");
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

int setFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * fp){
// i,j >0  &&  i,j < MAP_SIZE-1i
    int i, j;
    srand((unsigned int)time(NULL));
    while(1){
        i=rand()%(MAP_SIZE-2) + 1;
        j=rand()%(MAP_SIZE-2) + 1;
        if(map[i][j] == EMPTY){
            map[i][j] = FRUIT;
            fp->x = i;
            fp->y = j;
            (fp->numOfFruit)++;
            return 1;
        }
    }
}


int setBonusFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * fp){
    int i, j, numOfFruit=0;
    for(i=0; i<MAP_SIZE-1 ; i++){
        for(j=0; j<MAP_SIZE ; j++){
            if(map[i][j] == EMPTY){
                map[i][j] = FRUIT;
                numOfFruit++;
            }
        }
    }
    return numOfFruit;
}

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    map[snake_x][snake_y] = HEAD;
}
void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    map[snake_x][snake_y] = EMPTY;
}

//get snake x, y and move snake
int moveSnake(MData map[MAP_SIZE][MAP_SIZE], SnakePos * snake,int way, Queue * pq){
    if(way == UP){
        if(snake->y < 2) return COLLISION;
        removeSnake(map, snake->x, snake->y);
        snake->y -= 1;
        setSnake(map, snake->x, snake->y);
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
        printf("u\n");
        return UP;
    }
    if(way == DOWN){
<<<<<<< HEAD
        if(*py > MAP_SIZE-3) return COLLISION;
        removeSnake(map, px, py);
        *py += 1;
        setSnake(map, px, py);
=======
        if(snake->y > MAP_SIZE-3) return COLLISION;
        removeSnake(map, snake->x, snake->y);
        snake->y += 1;
        setSnake(map, snake->x, snake->y);
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
        printf("d\n");
        return DOWN;
    }
    if(way == LEFT){
<<<<<<< HEAD
        if(*px < 2) return COLLISION;
        removeSnake(map, px, py);
        *px -= 1;
        setSnake(map, px, py);
=======
        if(snake->x < 2) return COLLISION;
        removeSnake(map, snake->x, snake->y);
        snake->x -= 1;
        setSnake(map, snake->x, snake->y);
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
        printf("l\n");
        return LEFT;
    }
    if(way == RIGHT){
<<<<<<< HEAD
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
=======
        if(snake->x > MAP_SIZE-3) return COLLISION;
        removeSnake(map, snake->x, snake->y);
        snake->x += 1;
        setSnake(map, snake->x, snake->y);
        printf("r\n");
        return RIGHT;
    }

}

int overlap(int savedKey, int key){
    if(savedKey == UP && key == DOWN)
        return TRUE;
    if(savedKey ==DOWN && key == UP)
        return TRUE;
    if(savedKey ==LEFT && key == RIGHT)
        return TRUE;
    if(savedKey ==RIGHT && key == LEFT)
        return TRUE;

    return FALSE;
}

int colWithFruit(SnakePos * sp, FruitPos * fp){
    //meet;
    if((sp->x == fp->x && sp->y == fp->y)){
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
        return TRUE;
    }
    return FALSE;
}
<<<<<<< HEAD
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
=======

int isCollision(int state){
    if(state == COLLISION) return TRUE;
    return FALSE;
}
void GameOver(int score, int best){
    FILE * wfp;
    if(score >= best){
        wfp = fopen("score.txt", "w");
        fprintf(wfp, "%d", score);
        fclose(wfp);
    }
    gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-5);
    printf("===<GAME OVER>===\n");
    gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-3);
    printf("Your Score : %d\n", score);
    gotoxy(DEFAULT_X+8,MAP_SIZE+5);
    printf("\n");

}

void GameStart(MData map[MAP_SIZE][MAP_SIZE]) {
    int best = 0;
    int mode=NORMAL;
    FILE * rfp;
    rfp = fopen("score.txt", "r");
    if(rfp == NULL){
        best = 0;
    } else {
        fscanf(rfp, "%d", &best);
    }
    fclose(rfp);

    int score = 0;
    int key, savedKey=0;
    Queue queue;
    QueueInit(&queue);

    SnakePos snake = {MAP_SIZE/2, MAP_SIZE/2, 0};
    SnakePos snakeTail = {0,0,0};
    FruitPos fruit;
    fruit.numOfFruit=0;
    setSnake(map, snake.x, snake.y);
    Enqueue(&queue, snake);

    while (1) {
        gotoxy(DEFAULT_X, DEFAULT_Y);
        if (fruit.numOfFruit == 0) {          // draw fruit
            setFruit(map, &fruit);
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
        }

        drawMainMap(map);           // draw map include snake, fruit and wall
        drawSubMap(score, best);
<<<<<<< HEAD
        Sleep(1000/20);             // snake speed
        if(colWithFruit(&spos, &fpos) == TRUE){
            fruit = 0;
=======
        Sleep(1000/(DWORD)mode);             // snake speed


        if(colWithFruit(&snake, &fruit) == TRUE){
            (fruit.numOfFruit)--;
            (snake.numOfTail)++;
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
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
<<<<<<< HEAD
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
=======
                printf("                                            ");
                gotoxy(DEFAULT_X, DEFAULT_Y);
            }

            if (key == 224 || key == 0) {
                key = getch();
                if(overlap(savedKey, key) == TRUE){
                    key = savedKey;
                }
                savedKey = moveSnake(map, &snake, key, &queue);
                if(isCollision(savedKey)){ GameOver(score, best); return;  }
            }
        }else{
            if(savedKey!=0) {
                if(isCollision(moveSnake(map, &snake, savedKey,&queue))){
                    GameOver(score, best);
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
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
<<<<<<< HEAD

    }

=======
    }
>>>>>>> 1cbf6b72665712b1201f899acde19597737a3a17
    return 0;
}
