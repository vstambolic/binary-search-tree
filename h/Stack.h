#ifndef STACK_H
#define STACK_H
#include "BST.h"



/************************************* STACK *************************************/


typedef struct stack_info {
	Pointer tmp;
	int low;
	int high;
} Stack_Info;

typedef struct stack {
	Stack_Info info;
	struct stack * next;
} Stack_Field;

typedef Stack_Field * Stack_Ptr;



Stack_Info create_tmp_stack_info(Pointer tmp, int low, int high);

int stack_empty(Stack_Ptr s);
void push(Stack_Ptr *s, Stack_Info x);
Stack_Info top(Stack_Ptr s);
Stack_Info pop(Stack_Ptr * s);

#endif // !STACK_H
