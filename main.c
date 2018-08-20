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

#define MAX  200
#define MAXS 10000
#define DEFAULT 0


//-----global declaration


typedef struct graphArc {
    
    char move;
    char toRead;
    char toWrite;
    int first;
    int last;
    struct graphArc *next;
    
} arcGraph;

typedef struct bfsNode {
    
    char *tape;
    int head;
    int curr;
    int currState;
    int length;
    struct bfsNode *next;
    
    
} nodeBfs;

typedef nodeBfs* nodeList;

int atmNode;

int max;

char line[MAXS];//renderlo dinamico

int acc[MAX];

arcGraph **arrayNode;//renderlo dinamico

//-----prototype

int spaceEater(void);

void graphBuilder(void);

int charParser(char *string, int n);

void *exceedManager(char *string, char move, int curr);

char bfsFun(void);

int loopChecker(arcGraph *arc);

void addNode(int node);

nodeList addCoda(char tape[], int head, int state, int curr, int length);

//-----main

int main(void) {
    
    arrayNode = (arcGraph**) malloc(sizeof(arcGraph*));
    arrayNode[0] = NULL;
    atmNode = 0;
    spaceEater();
    if(strcmp(line,"tr") == 0){
        
        // printf("\n TR: %s \n", line);
        spaceEater();
        while (strcmp(line,"acc") != 0) {
            
            //   printf("\n %s \n", line);
            graphBuilder();
            spaceEater();
            
        }
        
        for(int i = 0; i <= atmNode; i++){
            
            if(arrayNode[i] != NULL){
                
                //   printf("\n nodo: %d", i);
                arcGraph* p;
                p = arrayNode[i];
                while(p != NULL){
                    
                    // printf("  a % d leggendo %c ", p->last, p->toRead);
                    p = p->next;
                }
                
            }
            
            
        }
        for(int i = 0; i < MAX; i++){
            
            acc[i] = -1;
        }
        if(strcmp(line,"acc") == 0){
            
            //   printf("\n ACC: %s \n", line);
            int c = 0;
            spaceEater();
            while (strcmp(line,"max") != 0) {
                
                //     printf("\n %s \n", line);
                acc[c] = charParser(line, 1);
                //    printf("accettazione %d \n", acc[c]);
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
                printf("%c\n", res);;
                
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
    char i = '\0';
    int c = 0;
    eof = scanf("%c", &i);
    if(eof == EOF){
        return 1;
    }
    while(i != '\n' || c == 0){
        
        if(i != ' ' && i != '\n' && i != '\r'){
            line[c] = i;
            c++;
        }
        eof = scanf("%c", &i);
        if(eof == EOF){
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
    memset(integer,0,10);
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
    
    
    if(node >= atmNode){
        
        
        arrayNode = (arcGraph**) realloc(arrayNode, sizeof(arcGraph*)*(node+1));
        //     printf("riallocato con node  = %d e atmNode = %d \n", node, atmNode);
        for(int i = atmNode+1; i < (node+1) ; i++){
            
            arrayNode[i] = NULL;
        }
        atmNode = node;
        
        /*  nodeGraph * nodeG;
         nodeG = malloc(sizeof(nodeGraph));
         arrayNode[i] = nodeG;
         nodeG->numberState = i;
         nodeG->acc = 0;
         nodeG->lastInsert = 0;
         nodeG->extArc = malloc(sizeof(arcGraph*)); */
        
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
    newArc->first = first;
    newArc->last = last;
    newArc->next = NULL;
    if(arrayNode[first] == NULL){
        
        arrayNode[first] = newArc;
        
    }else{
        
        arcGraph* p;
        p = arrayNode[first];
        
        while(p->next != NULL){
            
            p = p->next;
            
        }
        p->next = newArc;
        
    }
    /*arrayNode[first]->extArc = (arcGraph**) realloc(arrayNode[first]->extArc, sizeof(arcGraph*)*((arrayNode[first]->lastInsert)+1));
     arrayNode[first]->extArc[arrayNode[first]->lastInsert] = newArc;
     arrayNode[first]->lastInsert++;*/
    
    
    
}

/*void *exceedManager(char *string, char move, int curr){
 
 char *newString;
 newString = (char*)malloc(sizeof(char)*(strlen(string)+2));
 string = (char*) realloc(string, sizeof(char)*(strlen(string)+2));
 memset(newString,0,strlen(string)+2);
 if(move == 'R'){
 
 newString = strcpy (newString,string);
 if(curr >= strlen(line)){
 
 string[strlen(string)] = '_';
 
 }else {
 
 string[strlen(string)] = line[curr];
 
 }
 }else{
 char *newString;
 newString = (char*)malloc(sizeof(char)*(strlen(string)+2));
 memset(newString,0,strlen(string)+2);
 newString[0] = '_';
 string = strcat(newString,string);
 
 }
 memset(newString,0,strlen(newString));
 free(newString);
 
 } */

int loopChecker(arcGraph *arc){
    int i = 0;
    if(arc->first == arc->last){
        
        if(arc->toRead == arc->toWrite && arc->move == 'S'){
            
            i = 1;
            return i;
        }else if(arc->toRead == '_'){
            
            i = 1;
            return i;
        }else {
            
            //caso rimbalzo con autoanello
        }
        
    }else {
        
        //caso rimbalzo senza autoanello
    }
    
    return i;
    
}

char bfsFun(){
    
    char res = 'U';
    int level = 1;
    int loop = 0;
    int rimasti = 1;
    int newLength = 0;
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
    node->tape = (char*)malloc(sizeof(char)*2);
    node->currState = DEFAULT;
    node->tape[DEFAULT] = line[0];
    //  printf("%s RootTape \n", node->tape);
    node->curr = 0;
    node->length = 1;
    node->head = 0;
    node->next = NULL;
    currNode1 = node;
    while(level <= max){
    //   printf("%d Level: \n", level);
        while(currNode1 != NULL){
            
            int accett = 0;
            arc = arrayNode[currNode1->currState];
            
            while(arc != NULL){
                
                if(arc->toRead == currNode1->tape[currNode1->head]){
                    if(loopChecker(arc) == 1){
                        loop = 1;
                    }else   {
                        currNode1->tape[currNode1->length] = '\0';
                        accett = 1;
                        newTape = strdup(currNode1->tape);
                        newLength = currNode1->length;
                        if(arc->move == 'R'){
                            
                            newCurr = currNode1->curr + 1;
                            currNode1->tape[currNode1->length] = '\0';
                            if(((currNode1->head)+1) == strlen(currNode1->tape) ){ //strlen(line) < currNode1->curr
                                
                                //        printf("Posizione nella line: %d \n", newCurr);
                                //newTape = exceedManager(newTape, arc->move, newCurr);
                                newTape = (char*)realloc(newTape, sizeof(char)*((currNode1->length)+2));
                                currNode1->tape[currNode1->head + 1 ] = '\0';
                                currNode1->tape[currNode1->head + 2] = '\0';
                                if(newCurr >= strlen(line)){
                                    
                                    newTape[currNode1->head+1] = '_';
                                    
                                }else {
                                    
                                    newTape[currNode1->head+1] = line[newCurr];
                                    
                                }
                                newTape[currNode1->head] = arc->toWrite;
                                newHead = currNode1->head + 1;
                                newLength++;
                                
                            }else{
                                
                                newTape[currNode1->head] = arc->toWrite;
                                newHead = currNode1->head + 1;
                                
                                
                                
                            }
                            
                            
                        }else if(arc->move == 'L'){
                            
                            newCurr = currNode1->curr - 1;
                            if(((currNode1->head)-1) < 0){ //strlen(line) < currNode1->curr
                                
                                
                                // newTape = exceedManager(newTape, arc->move, currNode1->curr);
                                
                                char *newString;
                                newString = (char*)malloc(sizeof(char)*((currNode1->length)+2));
                                memset(newString,0,(currNode1->length)+2);
                                newString[0] = '_';
                                newString = strcat(newString,newTape);
                                newTape = (char*)realloc(newTape, sizeof(char)*((currNode1->length)+2));
                                memcpy(newTape, newString, sizeof(char)*(newLength+2));
                                free(newString);
                                
                                
                                newTape[currNode1->head + 1] = arc->toWrite;
                                newHead = currNode1->head;
                                newLength++;
                                
                            }else{
                                
                                
                                newTape[currNode1->head] = arc->toWrite;
                                newHead = currNode1->head - 1;
                                
                            }
                            
                        }else{
                            
                            newTape[currNode1->head] = arc->toWrite;
                            newHead = currNode1->head;
                        }
                     //   printf("%s Tape da %d, a %d  \n", newTape, arc->first, arc->last);
                     //   printf("lenght %d", newLength);
                     //     printf(" Testa punta all'el: %d \n", newHead);
                        if(headNode2 == NULL){
                            
                            headNode2 = addCoda(newTape, newHead, arc->last, newCurr, newLength);
                            rimasti++;
                            currNode2 = headNode2;
                            
                        }else{
                            
                            currNode2->next = addCoda(newTape, newHead, arc->last, newCurr, newLength);
                            rimasti++;
                            currNode2 = currNode2->next;
                            
                        }
                        
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
            free(preNode1);
            rimasti--;
            
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



nodeList addCoda(char *newTape, int head, int state, int curr, int length) {
    
    nodeBfs *node;
    node = malloc(sizeof(nodeBfs));
    node->currState = state;
    node->length = length;
    newTape[length] = '\0';
    node->tape = (char*)malloc(sizeof(char)*strlen(newTape));
    memset(node->tape,0,strlen(newTape));
    node->tape = strdup(newTape);
    node->curr = curr;
    node->head = head;
    node->next = NULL;
    
    return node;
}
