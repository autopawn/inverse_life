#include "evolve.h"

/* The minimum number of neighbors that need to change in order for a cell
to change to the given target state.
Negative values means that this change is ensured by more than one neighbor. */
int neigh_dist(int prev, int neighs, int tgt){
    if(tgt){
        if(prev){
            return neighs<=2? 2-neighs: neighs-3; 
        }else{
            return abs(neighs-3);
        }
    }else{
        if(prev){
            return neighs<=2? neighs-1 : 4-neighs;
        }else{
            return 1-abs(neighs-3);
        }
    }
}

int dist_cost(int dist){
    #ifdef THIRD_OBJECTIVE
    return dist>0? (100+dist)*100 : dist;
    #else
    return dist>0? 100*100+dist*100 : 0;
    #endif
}

void reverse_step(board *target, int void_ini_guess){
    int size_y = target->size_y;
    int size_x = target->size_x;
    board *guess = void_ini_guess? board_init(size_y,size_x) : board_copy(target);
    board *costs = board_init(size_y,size_x);
    

    /* Hill climbing */
    typedef struct {int y,x;} int2;
    int2 *candidates = malloc(size_y*size_x*sizeof(int2));
    int n_candidates = 0;
    while(1){

        /* Compute current cost of each cell */
        for(int y=0;y<size_y;y++){
            for(int x=0;x<size_x;x++){
                int neighs      = board_neighs(guess,y,x);
                int guess_stat  = board_get(guess,y,x);
                int target_stat = board_get(target,y,x);
                int dist = neigh_dist(guess_stat,neighs,target_stat);
                int cost = dist_cost(dist);
                board_set(costs,y,x,cost);
            }
        }

        /* Check improvement of each change */
        int best_improvement = 1;
        n_candidates = 0;
        for(int y=0;y<size_y;y++){
            for(int x=0;x<size_x;x++){
                int prev = board_get(guess,y,x);
                // Test to change the cell
                board_set(guess,y,x,!prev);
                // Check how costs change near cell:
                int improvement = 0;
                for(int yy=y-1; yy<=y+1; yy++){
                    for(int xx=x-1; xx<=x+1; xx++){
                        int neighs      = board_neighs(guess,yy,xx);
                        int guess_stat  = board_get(guess,yy,xx);
                        int target_stat = board_get(target,yy,xx);
                        int dist = neigh_dist(guess_stat,neighs,target_stat);
                        int cost = dist_cost(dist);
                        improvement += board_get(costs,yy,xx) - cost; // previous cost minus new cost
                    }
                }
                // Reset cell
                board_set(guess,y,x,prev);
                // Save candidate for change:
                if(improvement>=best_improvement){
                    if(improvement>best_improvement) n_candidates = 0;
                    int2 cand = {y,x};
                    candidates[n_candidates] = cand;
                    n_candidates += 1;
                }
            }
        }

        /* Perform one of the best improvements */
        if(n_candidates==0) break;
        int pick = rand()%n_candidates;
        int2 cand = candidates[pick];
        int prev = board_get(guess,cand.y,cand.x);
        board_set(guess,cand.y,cand.x,!prev);
    };

    /* Modify target */
    for(int i=0;i<target->size_y*target->size_x;i++){
        target->cells[i] = guess->cells[i];
    }
    free(candidates);
    board_free(costs);
    board_free(guess);
}

void forward_step(board *bo){
    board *nbo = board_init(bo->size_y,bo->size_x);
    // Check if each cell changes
    for(int y=0;y<bo->size_y;y++){
        for(int x=0;x<bo->size_x;x++){
            int neighs   = board_neighs(bo,y,x);
            int bo_stat  = board_get(bo,y,x);
            int dist = neigh_dist(bo_stat,neighs,1);
            board_set(nbo,y,x,dist<=0);
        }
    }
    // Copy on bo
    for(int i=0;i<bo->size_y*bo->size_x;i++){
        bo->cells[i] = nbo->cells[i];
    }
    board_free(nbo);
}
