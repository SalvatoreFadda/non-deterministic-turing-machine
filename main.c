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

#define MAX  1000
#define MAXS 10000
#define DEFAULT 10
#define ALPHA 63


//-----global declaration


typedef struct graphArc {
    
    char move;
    char toRead;
    char toWrite;
    int first;
    int last;
    struct graphArc *next;
    
} arcGraph;

typedef struct directAddr{
    
    arcGraph *trans[ALPHA];
    
    
} directAddr;

typedef struct bfsNode {
    
    char *tape;
    int head;
    int curr;
    int currState;
    //int length;
    //int lengthL;
    struct bfsNode *next;
    
    
} nodeBfs;

typedef nodeBfs* nodeList;

int atmNode;

unsigned int max;

char line[MAXS];//renderlo dinamico

int acc[MAX];

directAddr *arrayNode[MAX];//renderlo dinamico

//-----prototype

int spaceEater(void);

void graphBuilder(void);

long charParser(char *string, int n);

char *tapeManager(char move, char *tape);

int dynamicAddr(char read);

char bfsFun(void);

void addNode(int node);

nodeList addCoda(char tape[], int head, int curr, int currState);

//-----main

int main(void) {
    
    // arrayNode = (arcGraph**) malloc(sizeof(arcGraph*));
    for(int i = 0; i < MAX ; i++){
        
        arrayNode[i] = NULL;
    }
    atmNode = 0;
    spaceEater();
    if(strcmp(line,"tr") == 0){
        
         //printf("\n TR: %s \n", line);
        spaceEater();
        while (strcmp(line,"acc") != 0) {
            
           // printf("\n %s \n", line);
            graphBuilder();
            spaceEater();
            
        }
        
      /*  for(int i = 0; i <= atmNode; i++){
            
            if(arrayNode[i] != NULL){
                
                   printf("\n nodo: %d", i);
                arcGraph* p;
                p = arrayNode[i]->trans[dynamicAddr(p->toRead)];
                while(p != NULL){
                    
                     printf("  a % d leggendo %c ", p->last, p->toRead);
                    p = p->next;
                }
                
            }
            
            
        } */
        for(int i = 0; i < MAX; i++){
            
            acc[i] = -1;
        }
        if(strcmp(line,"acc") == 0){
            
             //  printf("\n ACC: %s \n", line);
            int c = 0;
            spaceEater();
            while (strcmp(line,"max") != 0) {
                
                //     printf("\n %s \n", line);
                acc[c] = (int) charParser(line, 1);
                //    printf("accettazione %d \n", acc[c]);
                spaceEater();
                c++;
                
                
            }
            
        }
        
        if(strcmp(line,"max") == 0){
            
             //printf("\n MAX: %s \n", line);
            spaceEater();
            // printf("\n MAX %s \n", line);
            max = (unsigned int) charParser(line, 1);
            //printf("\n max : %d \n", max);
            
        }
        spaceEater();
        if(strcmp(line,"run") == 0){
            
             //  printf("\n RUN: %s \n", line);
            char res;
            int end = 0;
            
            while(end == 0){
                
                end = spaceEater();
                    // printf("\n %s \n", line);
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
                if(end != 2){
                    res = bfsFun();
                    // memset(inputTape,0,strlen(inputTape));
                    printf("%c\n", res);
                }
                
            }
            
        }
        
        
    }
    
    return 0;
}

//-----function

//function that clar from the read line space and if the line it's void it jump from the first useful line
int spaceEater(){
    
    memset(line,0,strlen(line));
    char eof = '\0';
    int c = 0;
    eof = getchar();
    if(eof == EOF){
        return 2;
    }
    while(eof != '\n' || c == 0){
        
        if(eof != ' ' && eof != '\n' && eof != '\r'){
            line[c] = eof;
            c++;
        }
        eof = getchar();
        if(eof == EOF){
            return 1;
        }
        
    }
    return 0;
    
}

//function that found the nth-int in the given string and return it
long charParser(char *string, int nth){
    
    long trad;
    char integer[MAX];
    int c = 0;
    int temp = 0;
    int i = 0;
    memset(integer,0,MAX);
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
    // printf("\n integer %s \n", integer);
    trad = atol(integer);
    
    return trad;
}


int dynamicAddr(char read){
    
    int address;
    if(read >= '0' && read <= '9'){
        
        address = (int) read;
        return (address - 48);
        
        
    }else if(read >= 'A' && read <= 'Z'){
        
        address = (int) read;
        return (address - 55);
        
    }else if(read >= 'a' && read <= 'z'){
        
        address = (int) read;
        return (address - 61);
        
    }else{
        
        return (ALPHA - 1);
        
    }
}

void graphBuilder(){
    
    int c = 0;
    char toWrite = '0';
    char toRead = '0';
    char move = '0';
    int first = (int) charParser(line, 1);
    int last = (int) charParser(line, 2);
    
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
       // printf("cacca node \n");
        addNode(first);
    }
    
    arcGraph* newArc;
    newArc = malloc(sizeof(arcGraph));
    newArc->move = move;
    newArc->toRead = toRead;
    newArc->toWrite = toWrite;
    newArc->first = first;
    newArc->last = last;
    newArc->next = NULL;
    if(arrayNode[first]->trans[dynamicAddr(toRead)] == NULL){
        
       arrayNode[first]->trans[dynamicAddr(toRead)] = newArc;
        
    }else{
        
        arcGraph* p;
        p = arrayNode[first]->trans[dynamicAddr(toRead)];
        
        while(p->next != NULL){
        
            p = p->next;
            
        }
        p->next = newArc;
        
    }
}

void addNode(int node){
    
    
    if(atmNode <= node){
    
        for(int i = 0; i < (node+1) ; i++){
            
            if(arrayNode[i] == NULL){
            
                directAddr *newDin;
                newDin = malloc(sizeof(directAddr));
               
                for(int j = 0; j < ALPHA; j++){
                   
                    newDin->trans[j] = NULL;
                }
                arrayNode[i] = newDin;
            }
        }
        atmNode = node;
        
    }
    
    
    
}


char bfsFun(){
    
    char res = 'U';
    unsigned int level = 0;
    int loop = 0;
    int newHead = 0;
    int newCurr = 0;
    arcGraph *arc;
    char *newTape;
    directAddr *dir;
    dir = malloc(sizeof(directAddr));
    arc = malloc(sizeof(arcGraph));
    nodeList currNode1 = NULL;
    nodeList headNode2 = NULL;
    nodeList currNode2 = NULL;
    nodeList preNode1 = NULL;
    currNode1 = malloc(sizeof(nodeBfs));
    currNode1->tape = malloc(sizeof(char)*DEFAULT+1);
    memset(currNode1->tape, '_', DEFAULT);
    currNode1->tape[DEFAULT] = '\0';
    currNode1->head = DEFAULT/2;
    currNode1->curr = 0;
    currNode1->currState = 0;
    currNode1->tape[currNode1->head] = line[currNode1->curr];
    while(level <= max){
        
       // printf("%d Level: \n", level);
        while(currNode1 != NULL){
            
            int accett = 0;
            dir = arrayNode[currNode1->currState];
            arc = dir->trans[dynamicAddr(currNode1->tape[currNode1->head])];
            
            while(arc != NULL){
                
                if(arc->toRead == '_' && arc->first == arc->last){
                    
                    loop = 1;
                    
                }else{
                    
                    accett = 1;
                    if(arc->next == NULL){
                        
                        newTape = currNode1->tape;
                    
                    }else{
                        
                        newTape = malloc(sizeof(char)*(strlen(currNode1->tape)+1));
                        memcpy(newTape, currNode1->tape, strlen(currNode1->tape));
                        newTape[strlen(currNode1->tape)] = '\0';
                    }
                    
                    switch (arc->move) {
                        case 'R':
                            if((currNode1->head)+1 == strlen(newTape)){
                                
                                newTape = tapeManager(arc->move, newTape);
                                
                            }
                            if(newTape[currNode1->head + 1 ] == '_'){
                                
                                if((currNode1->curr)+1 < strlen(line)){
                                    
                                    newTape[currNode1->head+1] = line[currNode1->curr+1];
                                    newCurr = currNode1->curr +1;
                                    
                                }
                            }
                           
                            newTape[currNode1->head] = arc->toWrite;
                            newHead = currNode1->head + 1;
                           
                            break;
                            
                        case 'L':
                            
                            if(((currNode1->head)-1) < 0){
                            
                                newTape = tapeManager(arc->move, newTape);
                                newTape[currNode1->head + DEFAULT] = arc->toWrite;
                                newHead = currNode1->head + DEFAULT - 1;
                            
                            }else{
                                
                                
                                newTape[currNode1->head] = arc->toWrite;
                                newHead = currNode1->head - 1;
                                
                            }
                            
                            
                            break;
                            
                        case 'S':
                            
                            newTape[currNode1->head] = arc->toWrite;
                            newHead = currNode1->head;
                            break;
                            
                        default:
                            break;
                    }
                 //   printf("%s Tape da %d, a %d  \n", newTape, arc->first, arc->last);
                    if(headNode2 == NULL){
                        
                        headNode2 = addCoda(newTape, newHead, arc->last, newCurr);
                        currNode2 = headNode2;
                        
                    }else{
                        
                        currNode2->next = addCoda(newTape, newHead, arc->last, newCurr);
                        currNode2 = currNode2->next;
                        
                    }
                    
                }
                
                arc = arc->next;
                
            }
            
            if(accett == 0){
                for(int i = 0; i < MAX; i++){
                    if(currNode1->currState == acc[i]){
                        
                        //   printf("nodo di accettazione : %d \n", currNode1->currState);
                        res = '1';
                        return res;
                    }
                    
                }
            }
            
            
            preNode1 = currNode1;
            currNode1 = currNode1->next;
           // free(preNode1->tape);
            free(preNode1);
            
        }
        
        if(headNode2 == NULL){
            //   printf("RIMASTI: %d \n", rimasti);
            if(loop == 1){
                res = 'U';
            }
            else{
                res = '0';
            }
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
    
    
nodeList addCoda(char *newTape, int head, int currState, int curr) {
        
    nodeBfs *node;
    node = malloc(sizeof(nodeBfs));
    node->tape = newTape;
    node->head = head;
    node->next = NULL;
    node->currState = currState;
    return node;
}

char *tapeManager(char move, char *tape){
    
    char *newString;
    switch (move) {
        case 'R':
            newString = malloc(sizeof(char)*(strlen(tape)+DEFAULT)+1);
            memset(newString, '_', (strlen(tape)+DEFAULT));
            memcpy(newString, tape, strlen(tape));
            newString[strlen(newString)] = '\0';
            //free(tape);
            return newString;
            break;
            
        case 'L':
            newString = malloc(sizeof(char)*(strlen(tape)+DEFAULT+1));
            memset(newString, '_', DEFAULT-1);
            newString = strcat(newString, tape);
            newString[strlen(newString)] = '\0';
            //free(tape);
            return newString;
            break;
            
        default:
            return tape;
            break;
    }
    
}

            





























