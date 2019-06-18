#include <stdio.h>
#include <stdlib.h>

#define MAX 900

int arr[MAX];	//arr is the primary memory
extern int head[6];	//head is the array of lists
extern int size;	
extern int FREE;

/*********** The data modification functions ********************/
int newList();
int insertNode(int h, int ele);
int deleteNode(int h, int ele);

int pushFree(int ele);
int popFree();
/****************** The counting functions ****************/
int countList(int h);
void countAll();

/***************** The printig functions *******************/
void displayList(int h);
void displayAll();
void displayFree();
void print();
/**************** The defragmenting function *******************/
int defragment();
