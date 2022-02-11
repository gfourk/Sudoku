/********************************************************************
   grid.c

   Provides definition of grid ADT used for solving sudoku puzzles and
   functions required to access and modify elements of the structure.
*********************************************************************/

#include "grid.h"

/* update value of i,j to n */
void grid_update_value(Grid_T *g, int i, int j, int n)
{
    (*g).elts[i][j].val=n;
}

/* return value of i,j */
int grid_read_value(Grid_T g, int i, int j)
{
    return g.elts[i][j].val;
}


/* set (to 1) or clear (to 0) choice n for elt i,j */
void grid_set_choice(Grid_T *g, int i, int j, int n)
{
    (*g).elts[i][j].choices.num[n]=1;
}

void grid_clear_choice(Grid_T *g, int i, int j, int n)
{
    (*g).elts[i][j].choices.num[n]=0;
}

/* return count, set (to 9), or clear (to 0) count for elt i, j */
int grid_read_count(Grid_T g, int i, int j)
{
    return g.elts[i][j].choices.count;
}

void grid_set_count(Grid_T *g, int i, int j)
{
    (*g).elts[i][j].choices.count = 9;
}

void grid_clear_count(Grid_T *g, int i, int j)
{
    (*g).elts[i][j].choices.count = 0;
}

void grid_eliminate_count(Grid_T *g, int i, int j)
{
    (*g).elts[i][j].choices.count--;
}

/* return val, set (to 1), or clear (to 0) unique flag for g */
int grid_read_unique(Grid_T g)
{
    return g.unique;
}

void grid_set_unique(Grid_T *g)
{
    (*g).unique = 1;
}

void grid_clear_unique(Grid_T *g)
{
    (*g).unique = 0;
}

