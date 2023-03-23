#include <iostream>

struct linkedListNode {
    int data;
    linkedListNode* next;
    linkedListNode* prev;
};



void pushAfter (linkedListNode* node, int value) {
    linkedListNode* walk = node;
    while (walk -> prev && walk -> data >= value)
        walk = walk -> prev;
}






int main () {


}