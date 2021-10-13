#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(struct stack* this, int x)
{
    //this->stk[++this->sp] = x;
    	struct node *n = malloc(sizeof(struct node));
	n->data = x;
	n->next = this->top;
	this->top = n;
}

int pop(struct stack* this)
{
    //return this->stk[this->sp--];
    struct node *temp = this->top;
    int popped = temp->data;
    this->top = temp->next;
    free(temp);

    return popped;
}

struct stack* new_stack()
{
    struct stack* stk = malloc(sizeof(struct stack));
    stk->top = NULL;
    return stk;
}

void delete_stack(struct stack* stk)
{
    struct node *curr = stk->top;
	while(curr){
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
    free(stk);
}