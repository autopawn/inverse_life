#include "board.h"
#include "evolve.h"

int main(int argc, char const *argv[]){
    // Initial state
    int cells[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    board bo = {.size_y=7, .size_x=8, .cells=cells};


    board *target = board_copy(&bo);
    board_print(stdout,target);

    for(int s=0;s<200;s++){
        board *prev = reverse_step(target,1);
        int equals = board_eq(prev,target);
        board_free(target);
        target = prev;
        if(equals) break;
        printf("\n\n");
        board_print(stdout,target);
    }

    board_free(target);

    return 0;
}
