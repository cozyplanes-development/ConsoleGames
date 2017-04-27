//
// Created by BlockDMask on 26/04/2017.
//

#include <time.h>
#include "common.h"
#include "game.h"


int ChoiceOfCom(){
    srand((unsigned)time(NULL));

    return rand()%100;          //random range 0~99
}

int ChoiceOfUsr(){
    int num;
    printf("Odd:1, Even:2 = ");
    scanf("%d", &num);

    return num;
}

void WhoIsWinner(int com, int usr){
    if(com%2 == usr%2){
        printf("you win\n");
    }else
        printf("com win\n");
}

