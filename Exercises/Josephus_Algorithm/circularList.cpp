#include <iostream>

class linkedListNode {
    private:
        int data{0};
        linkedListNode* next = NULL;
        linkedListNode* prev = NULL;
    friend class circularList;
};

class circularList {
    private:
        linkedListNode* root = NULL;
        linkedListNode* tail = NULL;
        linkedListNode** ap  = NULL;
    public:
        linkedListNode* createNode (int);
        void pushBack   (int);
        void pop ();
        void it  ();
        void rit ();
};

linkedListNode* circularList::createNode (int value) {
    linkedListNode* aux = new linkedListNode();
    aux -> data = value;
    return aux;
}

void circularList::it () {
    if (!(*ap)) ap = &root;
    ap = &(*ap) -> next;
}
void circularList::rit () {
    if(!(*ap)) ap = &tail;
    ap = &(*ap) -> prev;
}

void circularList::pushBack (int value) {
    linkedListNode* tmp = createNode(value);
    if (!root) {
        root = tmp;
        tail = tmp;
        tmp -> next = root;
        tmp -> prev = tail;
    }
    else {
        tmp -> next = tail -> next;
        tmp -> prev = tail;
        tail -> next = tmp;
        tail = tmp;
    }
}

void circularList::pop () {
    if (!root) return;
    
}