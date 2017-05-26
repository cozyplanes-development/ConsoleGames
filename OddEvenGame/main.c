#include "common.h"
#include "game.h"
//done
int main() {
    int com;
    int usr;

    puts("=====GAME START=====");
    puts("");

    com = ChoiceOfCom();
    usr = ChoiceOfUsr();

    puts("");

    puts(">>>>>>RESULT>>>>>>");
    WhoIsWinner(com, usr);

    printf("=> com : %d\n", com);

    if(usr == EVEN)
        puts("=> usr : EVEN");
    else
        puts("=> usr : ODD");

    puts("");



    return 0;
}