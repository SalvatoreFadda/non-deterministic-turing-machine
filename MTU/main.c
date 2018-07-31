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
#define MAXS 20000
#define DEFAULT 0


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
    
    char *tape;
    int head;
    int curr;
    int currState;
    struct bfsNode *next;
    
    
} nodeBfs;

typedef nodeBfs* nodeList;

int max;

int acc[MAX];

char line[MAXS];

char *inputTape;

nodeGraph *arrayNode[MAX];

//-----prototype

int spaceEater(void);

void graphBuilder(void);

int charParser(char *string, int n);

char *exceedManager(char *string, char move, int curr);

char bfsFun(void);

void addNode(int node);

nodeList addCoda(char tape[], int head, int state, int curr);

//-----main

int main(void) {
    
    spaceEater();
    if(strcmp(line,"tr") == 0){
        
        // printf("\n TR: %s \n", line);
        spaceEater();
        while (strcmp(line,"acc") != 0) {
            
            //   printf("\n %s \n", line);
            graphBuilder();
            spaceEater();
            
        }
        
        if(strcmp(line,"acc") == 0){
            
            //   printf("\n ACC: %s \n", line);
            int c = 0;
            for(int i = 0; i < MAX ; i++){
                
                acc[i] = -1;
            }
            spaceEater();
            while (strcmp(line,"max") != 0) {
                
                //     printf("\n %s \n", line);
                acc[c] = charParser(line, 1);
                spaceEater();
                c++;
                
                
            }
            
        }
        
        if(strcmp(line,"max") == 0){
            
            //   printf("\n MAX: %s \n", line);
            spaceEater();
            //  printf("\n %s \n", line);
            max = charParser(line, 1);
            
        }
        spaceEater();
        if(strcmp(line,"run") == 0){
            
            //   printf("\n RUN: %s \n", line);
            char res;
            int end = 0;
            
            
            while(end == 0){
                
                end = spaceEater();
                //     printf("\n %s \n", line);
                /* inputTape = (char*)malloc(sizeof(char)*strlen(line));
                 inputTape = strdup(line);
                 char *newString;
                 newString = (char*)malloc(sizeof(char)*(strlen(inputTape)+1));
                 newString[0] = '_';
                 newString = strcat(newString,inputTape);
                 memset(inputTape,0,strlen(inputTape));
                 printf("%s \n", inputTape);
                 inputTape = newString;
                 printf("%s \n", newString);
                 printf("%s \n", inputTape);
                 inputTape = (char*)malloc(sizeof(char)*(strlen(line)));
                 char *newString;
                 newString = line;
                 printf("\n %c \n", *newString);
                 newString = newString + 9;
                 if(*newString == '\0'){
                 printf("\n cacca \n");
                 } */
                res = bfsFun();
                // memset(inputTape,0,strlen(inputTape));
                printf("%c \n", res);
                
            }
            
        }
        
        
    }
    
    return 0;
}

//-----function

//function that clar from the read line space and if the line it's void it jump from the first useful line
int spaceEater(){
    
    memset(line,0,strlen(line));
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
    memset(integer,0,strlen(integer));
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
            memset(nodeG->extArc, 0, sizeof(int)*MAX);
            
            
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
        c++;
        if(line[c] == '\0'){
            c = -1;
        }
        
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
    newArc->first = arrayNode[first];
    newArc->last = arrayNode[last];
    arrayNode[first]->extArc[arrayNode[first]->lastInsert] = newArc;
    arrayNode[first]->lastInsert++;
    
    
    
}

char *exceedManager(char *string, char move, int curr){
    
    char *newString;
    newString = (char*)malloc(sizeof(char)*(strlen(string)+1));
    memset(newString,0,strlen(newString));
    if(move == 'R'){
        
        newString = strcpy (newString,string);
        if(curr >= strlen(line)){
            
            newString[strlen(string)] = '_';
            
        }else {
            
            newString[strlen(string)] = line[curr];
            
        }
    }else{
        
        newString[0] = '_';
        newString = strcat(newString,string);
        
    }
    memset(string,0,strlen(string));
    return newString;
    
}


char bfsFun(){
    
    char res = 'U';
    int level = 1;
    int stop = 0;
    int rimasti = 1;
    char *newTape;
    int newCurr = 0;
    int newHead;
    arcGraph *arc;
    arc = malloc(sizeof(arcGraph));
    nodeList headNode2 = NULL;
    nodeList currNode2 = NULL;
    nodeList preNode1 = NULL;
    nodeList currNode1;
    //root con DEFAULT = 0;
    nodeBfs *node;
    node = malloc(sizeof(nodeBfs));
    node->tape = malloc(sizeof(char)*1);
    node->currState = DEFAULT;
    node->tape[DEFAULT] = line[0];
    //  printf("%s RootTape \n", node->tape);
    node->curr = 0;
    node->head = 0;
    node->next = NULL;
    currNode1 = node;
    while(level <= max){
        // printf("%d Level: \n", level);
        
        while(currNode1 != NULL){
            
            int accett = 0;
            stop = arrayNode[currNode1->currState]->lastInsert;
            
            for(int i = 0; i < stop; i++){
                
                arc = arrayNode[currNode1->currState]->extArc[i];
                if(arc->toRead == currNode1->tape[currNode1->head]){
                    
                    accett = 1;
                    newTape = strdup(currNode1->tape);
                    if(arc->move == 'R'){
                        
                        newCurr = currNode1->curr + 1;
                        if(((currNode1->head)+1) >= strlen(currNode1->tape) ){ //strlen(line) < currNode1->curr
                            
                            //        printf("Posizione nella line: %d \n", newCurr);
                            newTape = exceedManager(newTape, arc->move, newCurr);
                            newTape[currNode1->head] = arc->toWrite;
                            newHead = currNode1->head + 1;
                            
                        }else{
                            
                            newTape[currNode1->head] = arc->toWrite;
                            newHead = currNode1->head + 1;
                            
                            
                            
                        }
                        
                        
                    }else if(arc->move == 'L'){
                        
                        newCurr = currNode1->curr - 1;
                        if(((currNode1->head)-1) < 0){ //strlen(line) < currNode1->curr
                            
                            
                            newTape = exceedManager(newTape, arc->move, currNode1->curr);
                            newTape[currNode1->head + 1] = arc->toWrite;
                            newHead = currNode1->head;
                            
                        }else{
                            
                            
                            newTape[currNode1->head] = arc->toWrite;
                            newHead = currNode1->head - 1;
                            
                        }
                        
                    }else{
                        
                        newTape[currNode1->head] = arc->toWrite;
                        newHead = currNode1->head;
                    }
                    // printf("%s Tape da %d, a %d  \n", newTape, arc->first->numberState, arc->last->numberState);
                    //  printf(" Testa punta all'el: %d \n", newHead);
                    if(headNode2 == NULL){
                        
                        headNode2 = addCoda(newTape, newHead, arc->last->numberState, newCurr);
                        rimasti++;
                        currNode2 = headNode2;
                        
                    }else{
                        
                        currNode2->next = addCoda(newTape, newHead, arc->last->numberState, newCurr);
                        rimasti++;
                        currNode2 = currNode2->next;
                        
                    }
                    
                }
                
            }
            if(accett == 0){
                for(int i = 0; i < MAX; i++){
                    if(currNode1->currState == acc[i]){
                        //      printf("%d CurrState/ACC: %d \n", currNode1->currState, acc[i]);
                        res = '1';
                        return res;
                    }
                }
            }
            
            
            preNode1 = currNode1;
            currNode1 = currNode1->next;
            memset(preNode1->tape,0,strlen(preNode1->tape));
            free(preNode1);
            rimasti--;
            
        }
        if(headNode2 == NULL){
            //   printf("RIMASTI: %d \n", rimasti);
            res = '0';
            return res;
        }
        currNode1 = headNode2;
        headNode2 = NULL;
        preNode1 = NULL;
        currNode2 = NULL;
        level++;
    }
    
    return res;
}



nodeList addCoda(char *newTape, int head, int state, int curr){
    
    nodeBfs *node;
    node = malloc(sizeof(nodeBfs));
    node->currState = state;
    node->tape = (char*)malloc(sizeof(char)*strlen(newTape));
    memset(node->tape,0,strlen(node->tape));
    node->tape = strdup(newTape);
    node->curr = curr;
    node->head = head;
    node->next = NULL;
    
    return node;
}
