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

int max;

int acc[MAX];

char inputTape[MAXS];

char line[MAXS];

//-----prototype

char *spaceEater(void);

void graphBuilder(void);

int charParser(char *string);

//-----main

int main(void) {
    
    int a;
    scanf("%s", line);
    a = charParser(line);
    printf("%d", a);
    
    return 0;
}

//-----function

//function that clar from the read line space and if the line it's void it jump from the first useful line
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

//function that found a char in the given string and return it
int charParser(char *string){
    
    int trad;
    char integer[10];
    int c = 0;
    while(c != -1){
    
        if(string[c] >= '0' && string[c] <= '9' ){
            
            integer[c] = string[c];
            c++;
        }else {
            c = -1;
        }
        
    
    }
    trad = (int) strtol(integer, (char **)NULL, 10);
    
    return trad;
}



//function that create the graph of the NTM using the given transictions
void graphBuilder(){
    
    
    
}

























