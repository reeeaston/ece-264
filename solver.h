// ***
// *** Do NOT modify this file
// ***

#ifndef _SOLVER_H_
#define _SOLVER_H_
#include "list.h"
#include "maze.h"

PathLL* solveMaze(Maze* m);

void depthFirstSolve(Maze* m, MazePos curpos, char* path, int step,
                     PathLL* successPaths);

#endif
