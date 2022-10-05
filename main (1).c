#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 20

char abc[] = "abcdefghijklmnopqrstuvwxyz"; //Alphabet to be used in finding order of words in list to sort.
int size; //Global variable size for the size of the list to be used in various methods below.


typedef struct {
  char word[SIZE]; //Linked List storing word, first four letters of word, placement alphabetically, position in list, and length of word
  int place;
  int pos;
  int length;
  struct node *next;
} node;

node *head;

void printList(node *head) {
  while (head != NULL) {
    printf("%s [%d][%d], ", head->word, head->length,head->pos+1); //simple method to display list
    head = head->next;
  }
  printf("\n");
}


void addWord(node *head){ //Add word method to add a word to the list.
  char item[SIZE];
  node *temp=head;
  node *curr;
  size++;
  printf("Enter a new word: ");
  scanf("%s",item);
  for(int i = 0; i<strlen(item);i++){
    item[i]=tolower(item[i]); //Convert input char array to all lower case for formatting purposes
  }
  curr = malloc(sizeof(node));
  strcpy(curr->word,item);
  curr->length=strlen(item);
  curr->pos = size;
  for (int i = 0; i < sizeof(abc); i++) {
    if (item[0] == abc[i]) {
      curr->place = i;
    }
  }
  int counter=0;
  while(counter<size/2){
    temp=temp->next;
    counter++;
  }
  curr->next=temp->next;
  temp->next=curr;
  int holder=1;
  temp=head;
  while(temp->next!=NULL){ //Re initialize the position numbers of the list after the sort.
    temp=temp->next;
    temp->pos=holder;
    holder++;
  }
}

void deleteEnd(node *head){ //Method to remove "z" at the end to determine termination of sentence
  node *temp=head;
  for(int i = 0; i<size-1;i++){
    temp=temp->next;
  }
  temp->next=NULL;
  size--;
  
}

void deleteWord(node *head){ //Method to delete word, type in a word into item[] and will delete the word from list
  int index;
  node *temp=head,*curr;
  printf("What word would you like to delete, type position of the word: ");
  scanf("%d",&index);
  
  while(temp->pos!=index-2){
    temp=temp->next;
  }
  curr=temp->next;
  temp->next=curr->next;
  free(curr);
  curr=NULL;
  size--;
  while(temp->next!=NULL){

    temp=temp->next;
    temp->pos--;
  }
}

void searchWord(node *head){
  char item[SIZE];
  node *temp=head;
  int counter;
  printf("What word would you like to search for? (First 4 letters): ");
  scanf("%s", item);
  for(int i = 0; i<strlen(item);i++){
    item[i]=tolower(item[i]); //Convert input char array to all lower case for formatting purposes
  }
  counter=0;
  while(strcmp(temp->word,item)!=0){ //Find the node with the word of the input word
    temp=temp->next;
    counter++;
    if(counter>size){
      printf("Word does not exist in this dictionary\n");//If the loops searches through all nodes without finding word print word does not exist.
      break;
    }
  }
  if(counter<=size){ //If word does exist print this message
    printf("You searched for: %s\nThe length of that word is: %d\nPosition in list is number: %d of %d\n",temp->word,temp->length,(temp->pos)+1,size+1);
  } 
}

void sortList(node *head, int size) {//Method to sort list using bubble sort given the head address and size of list.
  node *temp = NULL, *start = NULL;
  int hold_place;
  int hold_length; //Holder variables to be used in for loop below.
  int hold_pos;
  int counter;
  char hold_four[SIZE];
  char hold_word[SIZE];
  while (counter <= size - 1) {
    counter = 0;
    start = head;
    temp = head->next;
    for (int i = 0; i < size; i++) {
      if (start->place > temp->place) { //If the starting value is greater than next value, swap all parameters of the node
        hold_place = start->place;
        hold_length = start->length;  //Swapping length, alphabetical placement, position in list, and the word.
        strcpy(hold_word, start->word);
        start->place = temp->place;
        start->length = temp->length;
        strcpy(start->word, temp->word);
        temp->place = hold_place;
        temp->length = hold_length;
        strcpy(temp->word, hold_word);
        
      } 
      else {
        counter++; //Continue the sort until counter=size-1 meaning it looped through the whole list with all values being ascending.
      }
      start = temp; //Travel down list using 2 points, one for the start value and one for next position from the start value
      temp = temp->next;
    }
  }
}

void getSentence(){
  node *ptr, *curr; //Initialization of pointers
  char item[SIZE];
  printf("Enter a free form sentence: ");
  scanf("%s",item); //Each word of sentence  gets stored in "item[]"
  for(int i = 0; i<strlen(item);i++){
    item[i]=tolower(item[i]);
  }
  head = malloc(sizeof(node)); //Allocating new memory for new node.
  strcpy(head->word,item); //head->word is whole word with all letters
  head->length=strlen(item); //Storing the length of the word in ->length
  head->pos = size; //Position inside of list in ascending order.
  for (int i = 0; i < sizeof(abc); i++) {
    if (item[0] == abc[i]) {
      head->place = i; //Determining the position of the word based on its starting letters, I.E. a=0, b=1, z=25
    }
  }
  head->next = NULL;
  ptr = head; //Storing mem address of head into ptr to travel down the list for each new word.
  size=0;
  while (item[0] != 'z') { //Continue adding words to list until item is a z which then terminates and displays list.
    size++;
    scanf("%s", item);
    for(int i = 0; i<strlen(item);i++){
      item[i]=tolower(item[i]);
    }
    curr = malloc(sizeof(node));
    strcpy(curr->word,item);//Storing whole version of word.
    curr->length=strlen(item);
    curr->pos = size;
    for (int i = 0; i < sizeof(abc); i++) {
      if (item[0] == abc[i]) {
        curr->place = i;
      }
    }
    curr->next = NULL;
    ptr->next = curr;
    ptr = ptr->next;
  } //Program will loops for as many words as the user enters.
}

int main() { //Main method to obtain sentence, sentence is terminated by typing a " z " at the end I.E. mouse on the grass z 
  getSentence(); //Calls method to get a sentence, stores all words as own nodes that point to another node alphabetically.
  
  deleteEnd(head);
  sortList(head, size); //calling start list method to sort list right after entering sentence.
  printList(head); //Displays list in command prompt 
  char input[SIZE];
  while(strcmp(input,"exit")!=0){
    printf("Would you like to add a word, search for a word, delete word in list, or exit?\n(search, add, delete, exit): ");
    scanf("%s",input);
    if(strcmp(input,"add")==0){
      addWord(head);
      sortList(head, size);
      printList(head);
    }
    else if(strcmp(input,"search")==0){
      searchWord(head);
    }
    else if(strcmp(input,"delete")==0){
      deleteWord(head);
      printf("\n");
      printList(head);
    }
  }
  printf("Goodbye! :)");
  
  

  return 0;
}
