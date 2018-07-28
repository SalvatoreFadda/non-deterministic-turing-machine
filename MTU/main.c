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
    struct bfsNode *pre;

    
} nodeBfs;

int max;

int acc[MAX];

char inputTape[MAXS];

char *line;

nodeGraph *arrayNode[MAX];

//-----prototype

void spaceEater(void);

void graphBuilder(void);

int charParser(char *string, int n);

char bfsFun(void);

void addNode(int node)

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
            
            spaceEater();
            char res;
            while(!strcmp(line,"\n")){
                
                res = bfsFun();
                printf("%c \n", res);
                spaceEater();
                
            }
            
        }
        
        
    }
    
    
    free(line);
    return 0;
}

//-----function

//function that clar from the read line space and if the line it's void it jump from the first useful line
void spaceEater(){
    
    free(line);
    line = (char*)malloc(sizeof(char)*MAXS);
    char i;
    int c = 0;
    scanf("%c", &i);
    while(i != '\n' /*|| c == 0*/){
        
        if(i != ' ' && i != '\n'){
            line[c] = i;
            c++;
        }
        scanf("%c", &i);
        
    }
    
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
    
    
    
    
}



















