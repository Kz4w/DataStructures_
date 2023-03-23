#include <iostream>
class linkedListNode {
  private:
    int data{0};
    linkedListNode* next;
  public:
    linkedListNode() {
      next = NULL;
    }
  friend class circularLinkedList;
};

class circularLinkedList {
  private:
    linkedListNode* head;
  public:
    circularLinkedList() {
      head = NULL;
    }
    linkedListNode* createNode    (int);
    linkedListNode** findIndirect (int,bool &);
    void pushFront    (int);
    void pushBack     (int);
    void pushBeforeX  (int,int);
    void pushAfterX   (int,int);
    void popFront     ();
    void popBack      ();
    void popX         (int);
    void popBeforeX   (int);
    void popAfterX    (int);
    void displayNodes ();
    
};

linkedListNode* circularLinkedList::createNode (int value) {
    linkedListNode* aux = new linkedListNode();
    aux -> data = value;
    return aux;
}

void circularLinkedList::pushFront (int value) {
    linkedListNode* tmp = createNode(value);
    if (!head) {
      head = tmp;
      tmp -> next = head;
    }
    else {
      linkedListNode* walk = head;
      tmp -> next = head;
      while (walk -> next != head)
        walk = walk -> next;
      head = tmp;
      walk -> next = head;
    }
}

void circularLinkedList::pushBack (int value) {
  linkedListNode* tmp = createNode(value);
  if(!head) {
    head = tmp;
    tmp -> next = head;
  }
  else {
    linkedListNode* walk = head;
    while (walk -> next != head)
      walk = walk -> next;
    walk -> next = tmp;
    tmp -> next = head;
  }
}

void circularLinkedList::pushBeforeX (int value, int nodex) {
    if (!head) return;
    bool flag = false;
    linkedListNode** indirectNode = findIndirect(nodex,flag);
    if (!flag) {
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = createNode(value);
    tmp -> next = (*indirectNode);
    if ((*indirectNode) == head) { // si es el primer nodo
      linkedListNode* walk = head;
      while (walk -> next != head)
        walk = walk -> next;
      walk -> next = tmp; 
    }
    (*indirectNode) = tmp;
}

void circularLinkedList::pushAfterX (int value, int nodex) { //error en el final
    if (!head) return;
    bool flag = false;
    linkedListNode** indirectNode = findIndirect(nodex,flag);
    if (!flag) {
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = createNode(value);
    tmp -> next = (*indirectNode) -> next;
    (*indirectNode) -> next = tmp;
}

void circularLinkedList::popFront () {
    if (!head) return;  // verificar que la lista tenga algun elemento
    linkedListNode* tmp = head; // nodo temporal
    if (head -> next == head) {
        head = NULL;
    }
    else {
      linkedListNode* walk = head;
      while (walk -> next != head)
        walk = walk -> next;
      head = head -> next; // mover el inicio
      walk -> next = head; // actulizar el final de la lista
    }
    delete tmp;
}

void circularLinkedList::popBack () {
    if (!head) return;

    linkedListNode** walk = head; 
    while ((*walk) -> next != head)
      walk = (*walk) -> next;
    linkedListNode* tmp = (*walk);

    if (head -> next == head) head == NULL;
    else (*walk) = head;
    delete tmp;
}

void circularLinkedList::popX (int value) {
    if (!head) return;
    bool flag = false;
    linkedListNode** indirect = findIndirect(value,flag);
    if (!flag) { 
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = (*indirect);
    if ((*indirect) != head) (*indirect) = (*indirect) -> next;
    else if ((*indirect) -> next == head) head = NULL;
    else {
        linkedListNode* walk = head;
        while (walk -> next != head)
          walk = walk -> next;
        head = head -> next;
        walk -> next = head;
    }
    delete tmp;
}
// verificar nodos anteriores si se pueden eliminar

void circularLinkedList::popBeforeX (int value) {
    if (!head) return;
    if (head -> data == value) {
      linkedListNode* tmp = NULL;
      if (head -> next == head) { // nodo unico
        tmp = head;
        head = NULL;
      }
      else {
        linkedListNode** walk = &head;
        while ((*walk) -> next != head)
          walk = &(*walk) -> next;
        tmp = (*walk);
        (*walk) = head;
      }
      delete tmp;
      return;
    }
    linkedListNode** before = NULL; // apunta al nodo anterior a indirect
    linkedListNode** indirect = &head;
    bool flag = false;
    while ((*indirect) -> data != value && !flag) {
      if ((*indirect) != head) {
        indirect = &(*indirect) -> next;
        before = indirect;
      }
      else flag = true;
    }
    if(!flag) {
      std::cout << "No se encontro el Nodo.\n";
      return;
    }
    linkedListNode* tmp = (*before);
    if ((*before) == head) { // si el nodo a eliminar es el primero
      linkedListNode* walk = head;
      while (walk -> next != head)
        walk = walk -> next;
      head = (*before) -> next;
    }
    else (*before) = (*indirect); // casos generales
    delete tmp;
}
 // faltan cambios
void circularLinkedList::popAfterX (int value) {
    if (!head) return;
    bool flag = false;
    linkedListNode** indirect = findIndirect(value,flag);
    if (!flag) {
      std::cout << "No se encontro el Nodo\n";
      return;
    } 
    else if (!(*indirect) -> next == head ) {
      std::cout << "Nodo posterior no existente en la Lista\n";
      return;
    }
    linkedListNode* tmp = (*indirect) -> next;
    (*indirect) -> next = (*indirect) -> next -> next;
    delete tmp;
}

void circularLinkedList::displayNodes () {
    linkedListNode* walk = head;
    while (walk != NULL) {
      std::cout << walk -> data << std::endl;
      walk = walk -> next;
    }
}
linkedListNode** circularLinkedList::findIndirect (int value, bool &flag) {
    linkedListNode** indirect = &head;
    while ((*indirect) -> data != value && !flag) {
        if ((*indirect) != head) indirect = &(*indirect) -> next;
        else flag = true;
    }
    return indirect;
}
