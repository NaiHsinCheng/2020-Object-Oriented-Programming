#ifndef __STACK_H__
#define __STACK_H__

class Node{
    int data;
    Node *next;
    
    public:
	Node(){}
        Node(int x, Node* nextNode):data(x),next(nextNode){}
	friend class Stack;
};

class Stack {
    /*enum { STACK_SIZE = 100 };
    int stk[STACK_SIZE];
    int sp;*/
    
    Node *top;
public:
    Stack();
    void push(int x);
    int pop();
    ~Stack();
};

#endif



