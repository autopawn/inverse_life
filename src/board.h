#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int size_y, size_x;
    int *cells;
} board;

board *board_init(int size_y, int size_x);
board *board_copy(const board *other);

int board_get(const board *bo, int y, int x);
int board_neighs(const board *bo, int y, int x);

int board_eq(const board *bo1, const board *bo2);

int board_set(board *bo, int y, int x, int v);

void board_free(board *bo);

void board_print(FILE *s, const board *bo);

#endif