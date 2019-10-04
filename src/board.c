#include "board.h"

board *board_init(int size_y, int size_x){
    // alloc board
    board *bo = malloc(sizeof(board));
    assert(bo!=NULL);
    // set sizes
    bo->size_y = size_y;
    bo->size_x = size_x;
    // alloc and init cells
    bo->cells = malloc(sizeof(int)*size_y*size_x);
    assert(bo->cells!=NULL);
    for(int i=0;i<size_y*size_x;i++) bo->cells[i] = 0;
    return bo;
}

board *board_copy(const board *other){
    board *bo = board_init(other->size_y,other->size_x);
    for(int i=0;i<bo->size_y*bo->size_x;i++) bo->cells[i] = other->cells[i];
    return bo;
}

int board_get(const board *bo, int y, int x){
    x = x%bo->size_x;
    x = x<0? bo->size_x+x : x; 
    y = y%bo->size_y;
    y = y<0? bo->size_y+y : y; 
    return bo->cells[y*bo->size_x+x];
}

int board_neighs(const board *bo, int y, int x){
    int neighs = 0;
    neighs += board_get(bo,y-0,x+1);
    neighs += board_get(bo,y-1,x+1);
    neighs += board_get(bo,y-1,x-0);
    neighs += board_get(bo,y-1,x-1);
    neighs += board_get(bo,y+0,x-1);
    neighs += board_get(bo,y+1,x-1);
    neighs += board_get(bo,y+1,x+0);
    neighs += board_get(bo,y+1,x+1);
    return neighs;
}

int board_eq(const board *bo1, const board *bo2){
    if(bo1->size_y!=bo2->size_y) return 0;
    if(bo1->size_x!=bo2->size_x) return 0;
    for(int i=0;i<bo1->size_y*bo1->size_x;i++){
        if(bo1->cells[i] != bo2->cells[i]) return 0;
    }
    return 1;
}

int board_set(board *bo, int y, int x, int v){
    if(y<0 || x<0 || y>=bo->size_y || x>=bo->size_x) return 0;
    bo->cells[y*bo->size_x+x] = v;
    return 1;
}

void board_free(board *bo){
    free(bo->cells);
    free(bo);
}

void board_print(FILE *s, const board *bo){
    for(int y=0;y<bo->size_y;y++){
        for(int x=0;x<bo->size_x;x++){
            fprintf(s," %c",board_get(bo,y,x)? '#':'.');
        }
        fprintf(s,"\n");
    }
}