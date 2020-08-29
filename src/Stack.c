#include "Stack.h"
#include <stdlib.h>


Stack_Info create_tmp_stack_info(Pointer tmp, int low, int high) {
	Stack_Info x;
	x.tmp = tmp;
	x.low = low;
	x.high = high;
	return x;
}

int stack_empty(Stack_Ptr s) {
	if (s == NULL)
		return 1;
	else
		return 0;
}

void push(Stack_Ptr *s, Stack_Info x) {

	if (stack_empty(*s)) {
		(*s) = malloc(sizeof(Stack_Field));
		(*s)->info = x;
		(*s)->next = NULL;
	}
	else {
		Stack_Ptr p = malloc(sizeof(Stack_Field));
		p->info = x;
		p->next = *s;
		(*s) = p;
	}
}

Stack_Info top(Stack_Ptr s) {
	Stack_Info x = { NULL,0,0 };
	if (s == NULL)
		return x;
	else
		return s->info;
}
Stack_Info pop(Stack_Ptr * s) {
	if (stack_empty(*s)) {
		perror("Underflow");
		exit(EXIT_FAILURE);
	}

	Stack_Info x = (*s)->info;
	Stack_Ptr p = *s;
	*s = (*s)->next;
	free(p);

	return x;
}
