//move snake                    o
//make tail, remove tail        x
//collision with wall           o
//collision with itself         x
//collision with fruit          o
//read best score from file.    o
//write best score to file      o
//what about using Queue.?      ..
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
SnakePos Enqueue(Queue * pq, SnakePos data){
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
            }
        }

    }
}


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
            gotoxy(i, j);
            printf("+");
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
    gotoxy(snake_x, snake_y);
    printf("s");
    map[snake_x][snake_y] = HEAD;
}
void setSnakeTail(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    gotoxy(snake_x, snake_y);
    printf("o");
    map[snake_x][snake_y] = TAIL;
}
void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y){
    gotoxy(snake_x, snake_y);
    printf(" ");
    map[snake_x][snake_y] = EMPTY;
}

//get snake x, y and move snake
int moveSnake(MData map[MAP_SIZE][MAP_SIZE], SnakePos * snake,int way, Queue * pq){
    int i;
   // removeSnake(map, snake->x, snake->y);
    if(way == UP){
        if(snake->y < 2) return COLLISION;
        --(snake->y);
        setSnake(map, snake->x, (snake->y));
        return UP;
    }
    if(way == DOWN){
        if(snake->y > MAP_SIZE-3) return COLLISION;
        ++(snake->y);
        setSnake(map, snake->x, (snake->y));
        return DOWN;
    }
    if(way == LEFT){
        if(snake->x < 2) return COLLISION;
        --(snake->x);
        setSnake(map, (snake->x), snake->y);

        return LEFT;
    }
    if(way == RIGHT){
        if(snake->x > MAP_SIZE-3) return COLLISION;
        setSnake(map, ++(snake->x), snake->y);
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
    int i;
    int best = 0;
    int mode = EASY;
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
    int time = TRUE;

    FruitPos fruit;
    fruit.numOfFruit=0;
    setSnake(map, snake.x, snake.y);

    while (1) {
        //gotoxy(DEFAULT_X, DEFAULT_Y);
        if (fruit.numOfFruit == 0) {          // draw fruit
            setFruit(map, &fruit);
        }

        drawMainMap(map);           // draw map include snake, fruit and wall
        drawSubMap(score, best);
        Sleep(1000/(DWORD)mode);             // snake speed

        if(colWithFruit(&snake, &fruit) == TRUE){
            (fruit.numOfFruit)--;
            (snake.numOfTail)++;
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
                Enqueue(&queue, snake);
                savedKey = moveSnake(map, &snake, key, &queue);

                if(time == TRUE){
                    snakeTail = Dequeue(&queue);
                    removeSnake(map, snakeTail.x, snakeTail.y);
                }else{
                    time = TRUE;
                }



                if(isCollision(savedKey)){ GameOver(score, best); return;  }
            }
        }else{
                Enqueue(&queue, snake);
                savedKey = moveSnake(map, &snake, savedKey, &queue);
            if(time == TRUE){
                snakeTail = Dequeue(&queue);
                removeSnake(map, snakeTail.x, snakeTail.y);
            }else{
                time = TRUE;
            }
                if(isCollision(savedKey)){ GameOver(score, best); return;  }

        }
    }
}

int main() {
    MData map[MAP_SIZE][MAP_SIZE] ;
    system("color 2");
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
