//<V1.0>
//move snake                    o
//collision with wall           o
//collision with itself         o
//collision with fruit          o
//read best score from file.    o
//write best score to file      o
//what about using Queue ?      o
//<V2.0>
//separate tail with head       o
//added collision
//map changing                  x

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
#define TAIL 3
#define FRUIT 5
#define COLLISION 10

#define TRUE 1
#define FALSE 0

#define NORMAL 10


typedef int MData;

typedef struct _fruitxy{
    int x;
    int y;
    int numOfFruit;
} FruitPos;

typedef struct _snakexp{
    int x;
    int y;
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
    newNode->next = NULL;
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
    SnakePos delData = {0,0};
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

void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


//show start menu
int drawStartMenu(){

    gotoxy(DEFAULT_X,DEFAULT_Y);
    printf("============================================");
    printf("================ Snake Game ================");
    printf("============================================");
    gotoxy(DEFAULT_X,DEFAULT_Y+4);
    printf("> Key  : up, down, left, right,");
    gotoxy(DEFAULT_X,DEFAULT_Y+5);
    printf("> Exit : 't'");

    gotoxy(DEFAULT_X+10,DEFAULT_Y+12);
    printf("> Made by BlockDMask.");
    gotoxy(DEFAULT_X+10,DEFAULT_Y+13);
    printf("> BlockDMask@gmail.com");

    while(1){
        int keyDown = getKeyDown();
        if(keyDown == 's' || keyDown == 'S') {
            return TRUE;
        }
        if(keyDown == 't' || keyDown == 'T'){
            return FALSE;
        }
        gotoxy(DEFAULT_X+4,DEFAULT_Y+9);
        printf("-- press 's' to start --");
        Sleep(1000/3);
        gotoxy(DEFAULT_X+4,DEFAULT_Y+9);
        printf("                         ");
        Sleep(1000/3);
    }

}
//show stage Menu and score;
int drawSpeedMenu(int * scoreArr){
    int i;
    FILE * rfp;
    rfp = fopen("score.txt", "r");
    gotoxy(DEFAULT_X,DEFAULT_Y+2);
    printf("================ BEST SCORE ================");
    if(rfp==NULL){
        for(i=0; i<4; i++) {
            gotoxy(DEFAULT_X,DEFAULT_Y+(i+4));
            printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
        }
    }else{
        fscanf(rfp, "%d %d %d %d", &scoreArr[0], &scoreArr[1], &scoreArr[2], &scoreArr[3]);
        for(i=0; i<4; i++){
            gotoxy(DEFAULT_X,DEFAULT_Y+(i+4));
            printf(" Stage [%d] : %d", i+1, scoreArr[i]);
        }
    }
    fclose(rfp);

    while(1){
        int keyDown = getKeyDown();
        if(keyDown == '1') {
            return 1;
        }
        if(keyDown == '2') {
            return 2;
        }
        if(keyDown == '3') {
            return 3;
        }
        if(keyDown == '4') {
            return 4;
        }
        gotoxy(DEFAULT_X,DEFAULT_Y+9);
        printf(">> Choose Stage : 1, 2, 3, 4");
        Sleep(1000/3);
        gotoxy(DEFAULT_X,DEFAULT_Y+9);
        printf(">>                          ");
        Sleep(1000/3);
    }

}

//////////////////////////////////////STAGE MAP SETTING////////////////////////////////
void stageClear(MData map[MAP_SIZE][MAP_SIZE]){
    int i, j;
    for(i=0; i<=MAP_SIZE; i++){
        for(j=0; i<=MAP_SIZE; j++){
            map[i][j] = EMPTY;
        }
    }
}

void stageOneInit(MData map[MAP_SIZE][MAP_SIZE]){
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

void stageTwoInit(MData map[MAP_SIZE][MAP_SIZE]){
    int i,j;
    for(i=0; i<MAP_SIZE; i++){
        for(j=0; j<MAP_SIZE ;j++){
            if(i==(int)MAP_SIZE/2 || j==0 || j==MAP_SIZE-1 ){
                map[i][j] = WALL;
            }else{
                map[i][j] = EMPTY;
            }
        }

    }
 }
void stageThreeInit(MData map[MAP_SIZE][MAP_SIZE]){
    int i,j;
    for(i=0; i<MAP_SIZE; i++){
        for(j=0; j<MAP_SIZE ;j++){
            if(i== MAP_SIZE/2 || j == MAP_SIZE/2){
                map[i][j] = WALL;
            }else{
                map[i][j] = EMPTY;
            }
        }
    }
}

void stageFourinit(MData map[MAP_SIZE][MAP_SIZE]){
    int i,j;
    for(i=0; i<MAP_SIZE; i++){
        for(j=0; j<MAP_SIZE ;j++){
            if(i==j || i+j == MAP_SIZE-1){
                if(i == MAP_SIZE/2 -1 || i == MAP_SIZE/2)
                    map[i][j] = EMPTY;
                else
                    map[i][j] = WALL;

            }else{
                map[i][j] = EMPTY;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// D R A W ////////////////////////////////////////

//draw game map
void drawMainMap(MData map[MAP_SIZE][MAP_SIZE]){
    int i, j;
    for(i=0; i<MAP_SIZE;i++){
        for(j=0;j<MAP_SIZE;j++) {
            if (map[i][j] == WALL) {
                gotoxy(i, j);
                printf("*");
            }else if (map[i][j] == EMPTY) {
                gotoxy(i, j);
                printf(" ");
            }
        }
    }
}


void drawSubMap(int score, int best, int stage){
    gotoxy(DEFAULT_X,MAP_SIZE+1);
    printf(" Score : %4d", score);
    gotoxy(DEFAULT_X,MAP_SIZE+2);
    printf(" Stage[%d] Best  : %4d", stage, best);
    gotoxy(DEFAULT_X+8,MAP_SIZE+5);
    printf("[Exit - 't' / Pause - 'p']\n");

}
/////////////////////////////////////////////////////////////////////////////////////

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
            gotoxy(i, j);
            printf("F");
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

void setSnakeTail(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    gotoxy(snake_x, snake_y);
    printf("o");
    map[snake_x][snake_y] = TAIL;
}

void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    gotoxy(snake_x, snake_y);
    printf("s");
    map[snake_x][snake_y] = HEAD;
}

void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    gotoxy(snake_x, snake_y);
    printf(" ");
    map[snake_x][snake_y] = EMPTY;
}


int rotate(int xy, int way){
    if(way == UP || way == LEFT){
        if(xy -1 == -1) {
            xy = MAP_SIZE-1;
        }else{
            --(xy);
        }
        return xy;
    }
    if(way == DOWN || way == RIGHT){
        if(xy +1 == MAP_SIZE){
            xy = 0;
        }else{
            ++xy;
        }
        return xy;
    }
    return FALSE;
}



int colWithTail(MData map[MAP_SIZE][MAP_SIZE],SnakePos * sp, int way){
    if(way == UP){
        if(map[sp->x][rotate(sp->y, way)] == TAIL)
            return TRUE;
    }
    if(way == DOWN){
        if(map[sp->x][rotate(sp->y, way)] == TAIL)
            return TRUE;
    }
    if(way == LEFT){
        if(map[rotate(sp->x, way)][sp->y] == TAIL)
            return TRUE;
    }
    if(way == RIGHT){
        if(map[rotate(sp->x, way)][sp->y] == TAIL)
            return TRUE;
    }
    return FALSE;
}

int colWithWall(MData map[MAP_SIZE][MAP_SIZE],SnakePos * sp, int way){
    if(way == UP){
        if(map[sp->x][rotate(sp->y, way)] == WALL)
            return TRUE;
    }
    if(way == DOWN){
        if(map[sp->x][rotate(sp->y, way)] == WALL)
            return TRUE;
    }
    if(way == LEFT){
        if(map[rotate(sp->x, way)][sp->y] == WALL)
            return TRUE;
    }
    if(way == RIGHT){
        if(map[rotate(sp->x, way)][sp->y] == WALL)
            return TRUE;
    }
    return FALSE;
}


//get snake x, y and move snake
int moveSnakeHead(MData map[MAP_SIZE][MAP_SIZE], SnakePos * snake,int way){
    removeSnake(map, snake->x, snake->y);
    if(colWithWall(map, snake, way) == TRUE){
        gotoxy(1,1);
        printf("hit : wall");
        return COLLISION;
    }
    if(colWithTail(map, snake, way) == TRUE){
        gotoxy(1,1);
        printf("hit : tail");
        return COLLISION;
    }

    if(way == UP){
        if(snake->y -1 == -1) {
            snake->y = MAP_SIZE-1;
        }else{
            --(snake->y);
        }
        setSnake(map, snake->x, (snake->y));
        return UP;
    }
    if(way == DOWN){
        if(snake->y +1 == MAP_SIZE){
            snake->y = 0;
        }else{
            ++(snake->y);
        }
        setSnake(map, snake->x, (snake->y));
        return DOWN;
    }
    if(way == LEFT){
        if(snake->x -1 == -1){
            snake->x = MAP_SIZE-1;
        }else{
            --(snake->x);
        }
        setSnake(map, (snake->x), snake->y);
        return LEFT;
    }
    if(way == RIGHT){
        if(snake->x +1 == MAP_SIZE){
            snake->x = 0;
        }else{
            ++(snake->x);
        }
        setSnake(map, snake->x, snake->y);
        return RIGHT;
    }
    return way;
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
    //meet;->x == fp->x
    if((sp->x == fp->x && sp->y == fp->y)){
        return TRUE;
    }
    return FALSE;
}

int isCollision(int state){
    if(state == COLLISION) return TRUE;
    return FALSE;
}
void GameOver(int score, int best, Queue *pq, int stage, int * scoreArr){
    FILE * wfp;
    if(score >= best) scoreArr[stage-1] =score;
    wfp = fopen("score.txt", "w");
    fprintf(wfp, "%d %d %d %d", scoreArr[0], scoreArr[1], scoreArr[2], scoreArr[3]);
    fclose(wfp);

    gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-5);
    printf("===<GAME OVER>===\n");
    gotoxy(MAP_SIZE/2-4, MAP_SIZE/2-3);
    printf("Your Score : %d\n", score);
    gotoxy(DEFAULT_X+8,MAP_SIZE+5);
    printf("\n");

    while(!isEmpty(pq)){
        Dequeue(pq);
    }
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE], int stage, int * scoreArr) {
    int best = 0;
    int score = 0;
    int key, savedKey=0;
    Queue queue;
    QueueInit(&queue);
    SnakePos snake = {MAP_SIZE/4 -2, MAP_SIZE/4 +1};
    SnakePos snakeSecond;
    SnakePos snakeTail;
    int time = FALSE;
    FruitPos fruit;
    fruit.numOfFruit=0;

    if(stage ==1){
        stageOneInit(map);
    }else if(stage==2){
        stageTwoInit(map);
    }else if(stage==3){
        stageThreeInit(map);
    }else{
        stageFourinit(map);
    }

    drawMainMap(map);
    setSnake(map, snake.x, snake.y);

    while (1) {

        Sleep(1000/(DWORD)NORMAL);             // snake speed
        if (fruit.numOfFruit == 0) {          // draw fruit
            setFruit(map, &fruit);
        }
        drawSubMap(score, best, stage);

        if(colWithFruit(&snake, &fruit) == TRUE){
            (fruit.numOfFruit)--;
            time = FALSE;
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
                printf("                                            ");
                gotoxy(DEFAULT_X, DEFAULT_Y);
            }

            if (key == 224 || key == 0) {
                key = getch();
                if(overlap(savedKey, key) == TRUE){
                    key = savedKey;
                }
                snakeSecond = snake;
                savedKey = moveSnakeHead(map, &snake, key);
                Enqueue(&queue, snakeSecond);
                setSnakeTail(map, snakeSecond.x, snakeSecond.y);
                if(time == TRUE){
                    snakeTail = Dequeue(&queue);
                    removeSnake(map, snakeTail.x, snakeTail.y);
                }else{
                    time = TRUE;
                }
                if(isCollision(savedKey)){ GameOver(score, best, &queue,stage, scoreArr); return;  }
            }
        }else{
            snakeSecond = snake;
            savedKey = moveSnakeHead(map, &snake, savedKey);
            Enqueue(&queue, snakeSecond);
            setSnakeTail(map, snakeSecond.x, snakeSecond.y);
            if(time == TRUE){
                snakeTail = Dequeue(&queue);
                removeSnake(map, snakeTail.x, snakeTail.y);
            }else{
                time = TRUE;
            }
            if(isCollision(savedKey)){ GameOver(score, best,&queue,stage,scoreArr); return;  }

        }
    }
}

int main() {
    MData map[MAP_SIZE][MAP_SIZE];
    system("color 7");
    hidecursor();
    int stage;
    int scoreArr[4] = {0};
    while(1){
        system("mode con: cols=44 lines=30");   //console size
        if(drawStartMenu() == FALSE) break;
        system("cls");
        stage = drawSpeedMenu(scoreArr);
        system("cls");
        GameStart(map, stage, scoreArr);
        system("pause");
    }
    return 0;
}




