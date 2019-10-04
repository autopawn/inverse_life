#include <stdlib.h>
#include <unistd.h>

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

    // Go backwards

    int steps = 0;
    for(steps=0;steps<5;steps++){
        board *prev = board_copy(target); 
        reverse_step(target,1);
        int equals = board_eq(prev,target);
        board_free(prev);
        if(equals) break;
        printf("\n");
        board_print(stdout,target);
        printf("\n");
    }

    // Go forward
    for(int k=0;k<steps;k++){
        forward_step(target);
        usleep(1000000);
        printf("\n");
        board_print(stdout,target);
        printf("\n");
    }

    board_free(target);

    return 0;
}
