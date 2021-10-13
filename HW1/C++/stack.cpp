#include "stack.h"

Stack::Stack()
{
    //sp = -1;
    top = 0;
}

void Stack::push(int x)
{
    //stk[++sp] = x;
    Node *n = new Node(x,top);
    top = n;
}

int Stack::pop()
{
    //return stk[sp--];
    Node *temp = top;
    int popped = temp->data;
    top = temp->next;
    delete temp;

    return popped;
}

Stack::~Stack()
{
    Node *curr = top;
    while(curr){
	Node *temp = curr;
	curr = curr->next;
	delete temp;
    }
}