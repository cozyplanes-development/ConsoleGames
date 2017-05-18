//저장,
//score 는 thread이용해서 돌리고,
//뱀 있어야하고
//음식 있어야함.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define X 32
#define Y 12

void init(char (*arr)[X]){
    int i, j;
    for(i=0; i<Y;i++){
        if(i==0 || i==Y-1){
            for(j=0;j<X;j++){
                arr[i][j] = '=';
            }
        }else {

            for (j = 0; j < X; j++) {
                if(j==(X-1)/2){
                    arr[i][j] = '|';
                }else{
                    arr[i][j] = ' ';
                }
            }
        }
    }
}

void draw(char (*arr)[X]){
    printf("========== Snake Game ==========\n");
    printf("Key : up down left right\n");
    printf("Exit : 't' or 'T' \n");

    int i, j;
    for(i=0;i<Y;i++){
        for(j=0; j<X;j++){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
    printf("scode : \n");
    printf("\t\t\tmade by BlockDMask\n");
}

void GameStart(char (*arr)[X]){
    int key;
    while(1){
        if(kbhit()){
            key = getch();
            if(key=='t'||key=='T') break;
            if(key ==224 || key==0){
                key=getch();
                switch(key){
                    case 72:
                        printf("up\n");
                        break;
                    case 75:
                        printf("left\n");
                        break;
                    case 77:
                        printf("right\n");
                        break;
                    case 80:
                        printf("down\n");
                        break;
                    default:
                        break;
                }
            }

        }
        sleep(1);
        system("cls");
        init(arr);
        draw(arr);
    }

}

int main() {
    char arr[Y][X] = {0};
    GameStart(arr);
    int key;
    system("pause");
    return 0;
}