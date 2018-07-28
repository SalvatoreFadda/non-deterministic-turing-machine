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
#define START 400
#define LAST 1999


//-----global declaration


typedef struct graphArc {
    
    char move;
    char toRead;
    char toWrite;
    struct graphNode *first;
    struct graphNode *last;
    
} arcGraph;


typedef struct graphNode {
    
    int numberState;
    int lastInsert;
    arcGraph *extArc[MAX];
    
} nodeGraph;



typedef struct bfsNode {
    
    char tape[MAXS];
    char *head;
    int curr;
    int currState;
    struct bfsNode *next;

    
} nodeBfs;

typedef nodeBfs* nodeList;

int max;

int acc[MAX];

char *line;

char *inputTape;

nodeGraph *arrayNode[MAX];

//-----prototype

int spaceEater(void);

void graphBuilder(void);

int charParser(char *string, int n);

char bfsFun(void);

void addNode(int node);

void addCoda(nodeList *lista, nodeList *pre, char tape[], char *head, int state, int curr);

//-----main

int main(void) {
    
    line = (char*)malloc(sizeof(char)*MAXS);
    
    spaceEater();
    if(strcmp(line,"tr")){
        
        spaceEater();
        while (!strcmp(line,"acc")) {
            
            graphBuilder();
            spaceEater();
            
        }
        
        if(strcmp(line,"acc")){
            
            int c = 0;
            spaceEater();
            while (!strcmp(line,"max")) {
                
                acc[c] = charParser(line, 1);
                spaceEater();
                c++;
                
                
            }
            
        }
        
        if(strcmp(line,"max")){
            
            spaceEater();
            max = charParser(line, 1);
            
        }
        spaceEater();
        if(strcmp(line,"run")){
            
            char res;
            int end = 0;
            while(end == 0){
                
                end = spaceEater();
                //sostituire in maniera che la tape diventi dinamica
                inputTape = (char*)malloc(sizeof(char)*MAXS);
                for(int i = 0; i < MAXS; i++){
                    
                    inputTape[i] = '_';
                }
                for(int i = 0; (i+START) < MAXS; i++){
                    
                    inputTape[START] = line[i];
                }
                //------------------------------------------------
                res = bfsFun();
                printf("%c \n", res);
                
            }
            
        }
        
        
    }
    
    
    free(line);
    return 0;
}

//-----function

//function that clar from the read line space and if the line it's void it jump from the first useful line
int spaceEater(){
    
    free(line);
    line = (char*)malloc(sizeof(char)*MAXS);
    char i;
    int c = 0;
    scanf("%c", &i);
    while(i != '\n' || c == 0){
        
        if(i != ' ' && i != '\n'){
            line[c] = i;
            c++;
        }
        scanf("%c", &i);
        if(i == EOF){
            return 1;
        }
        
    }
    return 0;
    
}

//function that found the nth-int in the given string and return it
int charParser(char *string, int nth){
    
    int trad;
    char integer[10];
    int c = 0;
    int temp = 0;
    int i = 0;
    while(c != -1){
    
        if(nth == 1){
        
            if(string[c] >= '0' && string[c] <= '9' ){
            
            
                integer[c] = string[c];
            
                c++;
        
            }else {
            
                c = -1;
                
            }
        }else {
            
            if(string[c] >= '0' && string[c] <= '9' ){
                
                if (temp == 1){
                    
                    integer[i] = string[c];
                    i++;
                
                }
                
                c++;
                
            }else if(string[c] == '\0'){
                
                c = -1;
            }else {
                
                temp = 1;
                c++;
            }
        }
        
    
    }
    trad = (int) strtol(integer, (char **)NULL, 10);
    
    return trad;
}


void addNode(int node){
    
    for(int i = 0; i <= node; i++){
        
        if(arrayNode[i] == NULL){
            
            nodeGraph * nodeG;
            nodeG = malloc(sizeof(nodeGraph));
            arrayNode[i] = nodeG;
            nodeG->numberState = i;
        
            
        }
        
    }
    
}


//function that create arc of the NTM using the given transiction and linked it to the node
void graphBuilder(){
    
    int c = 0;
    char toWrite = '0';
    char toRead = '0';
    char move = '0';
    int first = charParser(line, 1);
    int last = charParser(line, 2);
    
        while(c != -1){
            if(line[c] >= 'A' && line[c] <= 'z' ){
                if(toRead == '0'){
                    toRead = line[c];
                }else if(toWrite == '0') {
                    toWrite = line[c];
                    }else {
                        move = line[c];
                    }
            
            }
        
            if(line[c] == '\0'){
                c = -1;
            }
            c++;
        
        }
    if(first < last){
        addNode(last);
    }else{
        addNode(first);
    }
    arcGraph* newArc;
    newArc = malloc(sizeof(arcGraph));
    newArc->move = move;
    newArc->toRead = toRead;
    newArc->toWrite = toWrite;
    arrayNode[first]->extArc[arrayNode[first]->lastInsert] = newArc;
    arrayNode[first]->lastInsert++;
    
    
    
}


char bfsFun(){
    
    char res = 'N';
    int c = START;
    int level = 0;
    int stop = 0;
    char newTape[MAXS];
    char *newHead;
    arcGraph *arc;
    nodeList headNode2 = NULL;
    nodeList currNode2 = NULL;
    nodeList preNode1 = NULL;
    nodeList currNode1;
    //root
    nodeBfs *node;
    node = malloc(sizeof(nodeBfs));
    node->currState = 0;
    node->tape[c] = inputTape[c];
    node->curr = c;
    node->head = &(node->tape[c]);
    node->next = NULL;
    currNode1 = node;
    while(level <= max){
        
        while(currNode1 == NULL){
        
            int accett = 0;
            stop = arrayNode[currNode1->currState]->lastInsert + 1;
        
            for(int i = 0; i < stop; i++){
            
                arc = arrayNode[currNode1->currState]->extArc[i];
                if(arc->toRead == *(currNode1->head)){
                
                    accett = 1;
                    
                    for(int i = 0; i < MAXS; i++){
                    
                        newTape[i] = currNode1->tape[i];
                    }
                    c = currNode1->curr;
                    newTape[c] = arc->toWrite;
                    if(arc->move == 'R'){
                    
                        c = c+1;
                        newHead = &newTape[c];
                    
                    }else if(arc->move == 'L'){
                    
                        c = c-1;
                        newHead = &newTape[c];
                    
                    }else{
                    
                        newHead = &newTape[c];
                    
                    }
                
                addCoda( &currNode2, &headNode2/*deve puntare alla testa della lista*/, newTape, newHead, arc->last->numberState, c);
                
                }
            }
            if(accett == 0){
                for(int i = 0; i < MAX; i++){
                    if(currNode1->currState == acc[i]){
                        res = '1';
                        return res;
                    }
                }
            }
            
        
            preNode1 = currNode1;
            currNode1 = currNode1->next;
            free(preNode1);
        
        }
        if(headNode2 == NULL){
            res = '0';
            return res;
        }
        headNode2 = currNode1;
        preNode1 = NULL;
        currNode2 = NULL;
        level++;
        
        
        
        
    }
    if(level <= max){
        res = 'U';
    }
    
    
    return res;
}



void addCoda(nodeList *next, nodeList *pre, char tape[], char *head, int state, int curr){
    
    if (*next == NULL) {
        
        
    }
    else {
        addCoda(&((*lista)->next), )
    }
    
    
}















