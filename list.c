// ***
// *** You MUST modify this file
// ***

#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL* buildPaths() {
    PathLL* retval = malloc(sizeof(PathLL));
    retval->head = NULL;
    return retval;
}

// Read the comments in list.h to understand what you need to implement
// for each function.
// Remember to check for memory leak.

void freePaths(PathLL* p) {
    // Remove all nodes from a linked list, deallocate the PathLL structure.
    // TODO
    PathNode* curr = p->head;
    while (curr != NULL) {
        PathNode* temp = curr;
        curr = curr->next;
        freeNode(temp);
    }
    free(p);
}

PathNode* buildNode(char* path) {
    // Allocate a new PathNode with path as its data, return the address.

    // WARNING: don't forget to use strcpy to copy path into the new node.
    // Don't just set them equal, otherwise if the input path changes the node
    // will have the wrong path.
    PathNode *newNode = malloc(sizeof(PathNode));
    newNode->path = malloc((strlen(path) + 1) * sizeof(char));
    strcpy(newNode->path, path);
    newNode->next = NULL;
    return newNode;

    // TODO
}

void freeNode(PathNode* p) {
    // Deallocate a pathNode
    free(p->path);
    free(p);
}

bool addNode(PathLL* paths, char* path) {
    // Add a path to the list of paths
    if (paths == NULL || path == NULL) {
        return false;
    }

    // Create new node with path
    PathNode* newNode = buildNode(path);
    if (newNode == NULL) {
        return false;
    }

    PathNode* curr = paths->head;
    PathNode* prev = NULL;

    while(curr != NULL)
    {
        bool shouldInsert = false;
        // If path is shorter than current path, automatically insert it
        if (strlen(path) < strlen(curr->path))
        {
            // New node points to curr's next, curr points to new node
            shouldInsert = true;
        }
        // If paths are of same length
        // Check for fewest number of turns amount of direction changes
        else if (strlen(path) == strlen(curr->path))
        {
            int pathTurns = 0;
            int currTurns = 0;
            
            int i = 1;
            while (path[i] != '\0')
            {
                pathTurns += (path[i] != path[i-1]) ? 1 : 0;
                currTurns += (curr->path[i] != curr->path[i-1]) ? 1 : 0;
                i++;
            }

            if (pathTurns < currTurns)
            {
                shouldInsert = true;
            }

            // If number of turns is equal, check if path is alphabetically sooner
            if ((pathTurns == currTurns) && (strcmp(path, curr->path) < 0))
            {
                shouldInsert = true;
            }
        }
        // If we're inserting, prev points to newNode, newNode points to curr
        if (shouldInsert) {
            if (prev == NULL) {
                newNode->next = paths->head;
                paths->head = newNode;
            }
            else {
                prev->next = newNode;
                newNode->next = curr;
            }
            return true;
        }


        // Regardless, increment the loop
        prev = curr;
        curr = curr->next;

    }


    // insert at end
    if (prev == NULL) {
        paths->head = newNode;
    } else {
        prev->next = newNode;
    }

    return true;
}

bool removeNode(PathLL* paths, char* path) {
    // Remove a node from the list with the specified path
    // TODO
    PathNode* curr = paths->head;
    PathNode* prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->path, path) == 0) {
            // Node to remove is found
            if (prev == NULL) {
                // Node to remove is head
                paths->head = curr->next;
            } 
            else {
                // Node to remove is in middle or end
                prev->next = curr->next;
            }
            freeNode(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false; // Node with specified path not found
}

bool containsNode(PathLL* paths, char* path) {
    // Return true if path exists in the list
    // TODO
    PathNode* curr = paths->head;
    while (curr != NULL) {
        // Check if path exists
        if (strcmp(curr->path, path) == 0) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void printPaths(PathLL* paths, FILE* fptr) {
    PathNode* curr = paths->head;
    int i = 0;
    while (curr != NULL) {
        fprintf(fptr, "Path %2d: %s\n", i, curr->path);
        i++;
        curr = curr->next;
    }
}
