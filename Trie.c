#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NUM_LETTERS 26


typedef struct node {
    struct node* enfants[NUM_LETTERS];
    char character;
    int position;
    int count;
} node;

typedef enum {FALSE=0, TRUE=1} boolean;

void addWord(node* head, char* word);
void printReverse(node* head, char *str);
void printWords(node* head, char *str);
void freeMemory(node* head);
node* addNode(char c);
boolean checktnai(char c);
boolean checkLetter(char c);


int main(int argc, char const *argv[])
{
    int i = 0;
    char *word = (char*)malloc(1);
    node* head = addNode(0);
	(*head).count--;
    while(TRUE)
    {
        char let = getchar();


        if(!(checkLetter(let))){ // if let is a letter
            let = tolower(let);  //lower it
            word = realloc(word, i+sizeof(char)); //allocate more space to word
            word[i] = let;
            i++;
        }

        else if(checktnai(let)){ // if we have a space or reached EOF

            word = realloc(word, i+sizeof(char)); //allocate more space to word
            word[i] = '\0'; //indicate end of word
            i=0;

            addWord(head, word);
            
            if(let == EOF) break;
        }
    }

    if(argc == 1) //if no argument
        printWords(head, word); //print lexicographically
    else if(argc == 2 && strcmp(argv[1],"r")==0) //if 2 arguments and arg 2 is r
        printReverse(head, word); // print reversed lexicographically

    free(word);
    freeMemory(head); //free the memory used by the tree
    return 0;
}

boolean checktnai(char c){
    if(c == EOF || c == ' ' || c == '\n') return TRUE;
    else return FALSE;
}

boolean checkLetter(char c){
    if((c < 'A' || c > 'z') || (c > 'Z' && c < 'a')) return TRUE;
    else return FALSE;
}

node* addNode(char c){
    node* n = malloc(sizeof(node));
    if(n == NULL) exit(0);
    else {
        (*n).character = c;
        return n;
    }
}


void addWord(node* head, char* word){

    int j = -1;

    for (int i =0; i< strlen(word); i++) {//will we haven't reached the end of the word

        char letter = word[i];

        //if letter isn't a small letter
        if (checkLetter(letter)) {
            letter = tolower(letter); //lower it
        }

        int index = (letter - 'a');

        if ((*head).enfants[index] == NULL) {


            (*head).enfants[index] = addNode(letter);
            (*head).position = j;
        }

        head = (*head).enfants[index];
        j++;

        //if we arrived at the end of the word

    }
    (*head).count++; //update count
    (*head).position = j;
}


void printReverse(node* head, char *str){
    if(head == NULL) return;

    str[(*head).position] = (*head).character;

    for (int i = NUM_LETTERS-1 ; i >= 0; i--){
        printReverse((*head).enfants[i], str);
    }

    boolean flag = FALSE;
    if((*head).count != 0) flag = TRUE; //word found

    if(flag){

        int length = (*head).position + 1;
        for(int i =0; i<length; i++) printf("%c",str[i]);
        printf(" %d\n", (*head).count);
    }
}


void printWords(node* head, char *str){
    if(head == NULL) return;

    str[(*head).position] = (*head).character;

    boolean flag = FALSE;
    if((*head).count != 0) flag = TRUE; //word found

    if(flag){

        int length = (*head).position + 1;
        for(int i =0; i<length; i++) printf("%c",str[i]);
        printf(" %d\n", (*head).count);
    }

    for (int i = 0; i < NUM_LETTERS; i++){
        printWords((*head).enfants[i], str);
    }
}

void freeMemory(node* head){
    if(head == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){
        freeMemory((*head).enfants[i]);
    }
    free(head);
}

