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
#define START 50

//-----global declaration

typedef enum {R,L,S} move;

typedef struct graphArc {
    
    move move;
    char toRead;
    char toWrite;
    struct graphNode *first;
    struct graphNode *last;
    
} arcGraph;

typedef struct graphNode {
    
    int numberState;
    arcGraph *extArc[MAX];
    
} nodeGraph;

typedef struct bfsNode {
    
    char tape[MAXS];
    char *head;
    struct bfsNode *pre;
    struct bfsNode *next[MAX];
    
} nodeBfs;

long int max;

int acc[MAX];

char inputTape[MAXS];

char line[MAXS];

//-----prototype

char *spaceEater(void);

//-----main

int main(void) {
    
    
    
    return 0;
}

//-----function

char *spaceEater(){
    
    char i;
    int c = 0;
    scanf("%c", &i);
    while(i != '\n' || c == 0){
        
        if(i != ' ' && i != '\n'){
            line[c] = i;
            c++;
        }
        scanf("%c", &i);
        
    }
    
    return line;
}

void graphBuilder(){
    
    
}

























