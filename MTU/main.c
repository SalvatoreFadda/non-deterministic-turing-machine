//
//  main.c
//  NTM
//
//  Created by Salvatore Fadda on 26/07/18.
//  Copyright © 2018 Salvatore Fadda. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAXS 2000
#define START 200

typedef enum {R,L,S} move;

typedef struct graphNode {
    
    int numberState;
    struct graphArc *extArc[MAX];
    
} nodeGraph;

typedef struct graphArc {
    
    move move;
    char toRead;
    char toWrite;
    struct graphNode *first;
    struct graphNode *last;
    
} arcGraph;

typedef struct bfsNode {
    
    int tape[MAXS];
    int *head;
    struct bfsNode *pre;
    struct bfsNode *next[MAX];
    
} nodeBfs;



//-----prototype



//-----main

int main(int argc, const char * argv[]) {
    
}
