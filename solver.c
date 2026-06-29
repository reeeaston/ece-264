// ***
// *** You MUST modify this file
// ***

#include "solver.h"
#include "list.h"
#include "mazehelper.h"
#include "path.h"

PathLL* solveMaze(Maze* m) {

    PathLL* successPaths = buildPaths();
    char* retval = malloc(((m->height * m->width) + 1) * sizeof(char));

    MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
    depthFirstSolve(m, mp, retval, 0, successPaths);

    free(retval);

    return successPaths;
}

void depthFirstSolve(Maze* m, MazePos curpos, char* path, int step,
					 PathLL* successPaths) {

	// FILL IN YOUR CODE HERE

	// Base case: if maze position is not in bounds or hit wall or was 
	// already visited, this is NOT a successful path
	if (!inBounds(curpos, m) || hitWall(curpos, m) || isVisited(curpos, m))
	{
		return;
	}
	// Base case: if maze position is the exit, we are at a successful path
	if (atEnd(curpos,m))
	{
		path[step] = '\0';
        addNode(successPaths, path);
		return;
	}

	// Update current square to be seen
	m->maze[curpos.ypos][curpos.xpos].visited = true;


	// Current situation: Current position isn't a blocker so we're
	// in a safe square
	// Recursive case: Explore four cardinal directions 

		// NORTHERN //
	// Update Path
	path[step] = 'N';
	MazePos newpos = curpos;
	newpos.ypos -= 1; 
	// Explore maze going up (row-1, col)
    depthFirstSolve(m, newpos, path, step+1, successPaths);

		// SOUTHERN //
	// Update Path
	path[step] = 'S';
	newpos = curpos;
	newpos.ypos += 1; 
	// Explore maze going down (row+1, col)
	depthFirstSolve(m, newpos, path, step+1, successPaths);

		// WESTERN //
	// Update Path
	path[step] = 'W';
	newpos = curpos;
	newpos.xpos -= 1; 
	// Explore maze going left (row, col-1)
    depthFirstSolve(m, newpos, path, step+1, successPaths);

		// EASTERN //
	// Update Path
	path[step] = 'E';
	newpos = curpos;
	newpos.xpos += 1; 
	// Explore maze going rightward (row, col+1)
	depthFirstSolve(m, newpos, path, step+1, successPaths);

    // Backtrack: Update current square to be unseen again for other paths
    m->maze[curpos.ypos][curpos.xpos].visited = false;
	
	return;
}
