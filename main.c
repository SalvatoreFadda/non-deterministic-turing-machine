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

#define MAX  2000
#define MAXB 100
#define MAXS 20000
#define MAXN 10000
#define DEFAULT 5
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
    int length;
    unsigned int level;
    //struct bfsNode *next;
    
    
} nodeBfs;

typedef nodeBfs* nodeList;

int atmNode;

unsigned int max;

char line[MAXS];//renderlo dinamico

int acc[MAX];

directAddr *arrayNode[MAXN];//renderlo dinamico

int tail = 0;

int head = 0;

nodeList bfsQueue[MAXB];

//-----prototype

int spaceEater(void);

void graphBuilder(int first, char toRead, char toWrite, char move, int last);

long charParser(char *string, int n);

char *tapeManager(char move, char *tape, int length);

int dynamicAddr(char read);

char bfsFun(void);

void addNode(int node);

void enque(char tape[], int head, int curr, int currState, int length, int level);

//-----main

int main(void) {
    
    // arrayNode = (arcGraph**) malloc(sizeof(arcGraph*));
    for(int j = 0; j < MAXN; j++){
        
        arrayNode[j] = NULL;
    }
    memset(acc, 0, sizeof(int)*MAX);
    atmNode = 0;
    int first = 0;
    int last = 0;
    char toRead = '\0';
    char toWrite = '\0';
    char move = '\0';
    
    fscanf(stdin, "%s", line);
    while(fscanf(stdin, "%d %c %c %c %d", &first, &toRead, &toWrite, &move, &last) == 5){
        
        //printf("tansazione: %d %c %c %c %d\n", first, toRead, toWrite, move, last);
        graphBuilder(first, toRead, toWrite, move, last);
    }
    memset(line, 0, strlen(line));
    int c = 0;
    fscanf(stdin, "%s", line);
    fscanf(stdin, "%s", line);
    while (strcmp(line, "max") != 0) {
        
        c = atoi(line);
        acc[c] = 1;
        //printf("acc in: %d è %d\n", c, acc[c]);
        memset(line, 0, strlen(line));
        fscanf(stdin, "%s", line);
    }
    fscanf(stdin, "%s", line);
    max = (unsigned int) atol(line);
   // printf("max: %u \n", max);
    fscanf(stdin, "%s", line);
    int eop = 0;
    char eof = '\0';
    char read = '\0';
    char res = '\0';
    scanf("%c", &read);
    if(read == '\r'){
        scanf("%c", &read);
    }
    int i = 0;
    while(eop == 0){
        
        memset(line, 0, strlen(line));
        i = 0;
        eof = scanf("%c", &read);
        if(eof != EOF){
        
            while (read != '\n' && eop == 0){
            
                if(read != '\r' && read != '\n'){
                    line[i] = read;
                    i++;
                }
                eof = scanf("%c", &read);
                if(eof == EOF){
                
                    eop = 1;
                }
            
            }
           // printf("%s\n", line);
            for(int j = 0; j < MAXB; j++){
                bfsQueue[j] = NULL;
            }
            head = 0;
            tail = 0;
           res = bfsFun();
           printf("%c\n", res);
        }else{
            
            eop = 1;
        }
    }
    return 0;
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

void graphBuilder(int first, char toRead, char toWrite, char move, int last){
    
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
    int loop = 0;
    int newHead = 0;
    int newCurr = 0;
    int newLength = 0;
    arcGraph *arc;
    char *newTape;
    newTape = malloc(sizeof(char)*DEFAULT+1);
    memset(newTape, '\0', DEFAULT);
    newTape[DEFAULT] = '\0';
    newTape[0] = line[0];
    directAddr *dir;
    dir = malloc(sizeof(directAddr));
    arc = malloc(sizeof(arcGraph));
    enque(newTape, 0, 0, 0, DEFAULT, 0);
    while(bfsQueue[head]->level <= max){
        
        //printf("%d Level: \n", bfsQueue[head]->level);
        //while(bfsQueue[head-1]->level == bfsQueue[head]->level){
            
            int accett = 0;
            dir = arrayNode[bfsQueue[head]->currState];
            arc = dir->trans[dynamicAddr(bfsQueue[head]->tape[bfsQueue[head]->head])];
            if(arc != NULL){
                // printf("testa %d \n", dynamicAddr(currNode1->tape[currNode1->head]));
                // printf("%d %c %c %c %d      ", arc->first, arc->toRead, arc->toWrite, arc->move, arc->last);
            }
            while(arc != NULL){
                
                if(arc->toRead == '_' && arc->first == arc->last && (arc->move == 'R' || arc->move == 'L')){
                    
                    loop = 1;
                    
                }else{
                    
                    accett = 1;
                    newLength = bfsQueue[head]->length;
                    if(arc->next == NULL){
                        
                        newTape = bfsQueue[head]->tape;
                        
                    }else{
                        
                        newTape = malloc(sizeof(char)*(newLength+1));
                        memcpy(newTape, bfsQueue[head]->tape, newLength);
                        newTape[newLength] = '\0';
                    }
                    
                    switch (arc->move) {
                        case 'R':
                            
                            newCurr = bfsQueue[head]->curr +1;
                            if((bfsQueue[head]->head)+1 == newLength){
                                //    printf(" %d \n", newLength);
                                newTape = tapeManager(arc->move, newTape, newLength);
                                newLength = newLength*2;
                                
                            }
                            if(newTape[bfsQueue[head]->head + 1 ] == '\0'){
                                
                                // printf("curr = %d", newCurr);
                                if(newCurr >= strlen(line)){
                                    
                                    newTape[bfsQueue[head]->head+1] = '_';
                                    
                                }else {
                                    
                                    newTape[bfsQueue[head]->head+1] = line[newCurr];
                                    
                                }
                            }
                            
                            newTape[bfsQueue[head]->head] = arc->toWrite;
                            newHead = bfsQueue[head]->head + 1;
                            
                            break;
                            
                        case 'L':
                            
                            newCurr = bfsQueue[head]->curr - 1;
                            if(((bfsQueue[head]->head)-1) < 0){
                                
                                newTape = tapeManager(arc->move, newTape, newLength);
                                newTape[bfsQueue[head]->head + newLength] = arc->toWrite;
                                newHead = bfsQueue[head]->head + (newLength -1);
                                newLength = newLength*2;
                                
                            }else{
                                
                                
                                newTape[bfsQueue[head]->head] = arc->toWrite;
                                newHead = bfsQueue[head]->head - 1;
                                
                            }
                            
                            
                            break;
                            
                        case 'S':
                            
                            newTape[bfsQueue[head]->head] = arc->toWrite;
                            newHead = bfsQueue[head]->head;
                            break;
                            
                        default:
                            break;
                    }
                    //printf("%s Tape da %d, a %d  \n", newTape, arc->first, arc->last);
                    // printf("lenght %d", newLength);
                    // printf(" Testa punta all'el: %d \n", newHead);
                    enque(newTape, newHead, arc->last, newCurr, newLength, bfsQueue[head]->level+1);
                }
                arc = arc->next;
                
            }
            
            if(accett == 0){
                
                free(bfsQueue[head]->tape);
                if(acc[bfsQueue[head]->currState] == 1){
                    
                    //printf("nodo di accettazione : %d \n", currNode1->currState);
                    res = '1';
                    return res;
                }
            }
            if(head+1 == MAXB){
                
                head = 0;
            }
            else{
                head++;
            }
            // free(preNode1->tape);
            //free(preNode1);
            
        //}
        
        if(bfsQueue[head] == NULL){
            //   printf("RIMASTI: %d \n", rimasti);
            if(loop == 1){
                res = 'U';
            }
            else{
                res = '0';
            }
            return res;
        }else if(head == 0){
            
            
            if(bfsQueue[MAXB-1]->level > bfsQueue[head]->level){
                //   printf("RIMASTI: %d \n", rimasti);
                if(loop == 1){
                    res = 'U';
                }
                else{
                    res = '0';
                }
                return res;
            }
        
        }else if(bfsQueue[head-1]->level > bfsQueue[head]->level){
            //   printf("RIMASTI: %d \n", rimasti);
            if(loop == 1){
                res = 'U';
            }
            else{
                res = '0';
            }
            return res;
        }
    }
    
    return res;
}


void enque(char *newTape, int head, int currState, int curr, int length, int level) {
    
    if(bfsQueue[tail] == NULL){
        
        nodeBfs *node;
        node = malloc(sizeof(nodeBfs));
        node->tape = newTape;
        node->head = head;
        node->currState = currState;
        node->curr = curr;
        node->length = length;
        node->level = level;
        bfsQueue[tail] = node;
        
    }else{
        
        bfsQueue[tail]->tape = newTape;
        bfsQueue[tail]->head = head;
        bfsQueue[tail]->currState = currState;
        bfsQueue[tail]->curr = curr;
        bfsQueue[tail]->length = length;
        bfsQueue[tail]->level = level;
        
    }
    if(tail+1 == MAXB){
        
        tail = 0;
        
    }else{
        
        tail++;
        
    }
}

char *tapeManager(char move, char *tape, int length){
    
    char *newString;
    switch (move) {
        case 'R':
            // printf("%c \n", move);
            tape = realloc(tape, sizeof(char)*((length*2)+1));
            //memset(newString, 0, (length+DEFAULT+1));
            //memcpy(newString, tape, length);
            //free(tape);
            for(int i = length; i < (length*2+1); i++){
                
                tape[i] = '\0';
                
            }
            return tape;
            break;
            
        case 'L':
            //printf("%c \n", move);
            newString = malloc(sizeof(char)*((length*2)+1));
            memset(newString, 0, (length+DEFAULT+1));
            for(int i = 0; i < (length); i++){
                
                newString[i] = '_';
                
            }
            newString = strcat(newString, tape);
            tape = realloc(tape, sizeof(char)*((length*2)+1));
            memcpy(tape, newString, sizeof(char)*((length*2)));
            tape[strlen(newString)] = '\0';
            free(newString);
            return tape;
            break;
            
        default:
            return tape;
            break;
    }
    
}

