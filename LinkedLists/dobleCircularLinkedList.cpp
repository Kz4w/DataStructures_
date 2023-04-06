#include <iostream>

class linkedListNode {
  private:
    int data{0};
    linkedListNode* next;
    linkedListNode* prev;
  public:
    linkedListNode() {
      prev = NULL;
      next = NULL;
    }
  friend class dCircularLinkedList;
};

class dCircularLinkedList {
  private:
    linkedListNode* head;
    linkedListNode* tail;
  public:
    dCircularLinkedList() {
      head = NULL;
      tail = NULL;
    }
    linkedListNode* createNode    (int);
    linkedListNode** findIndirect (int,bool &);
    linkedListNode** rfindIndirect(int,bool &);
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

linkedListNode* dCircularLinkedList::createNode (int value) {
    linkedListNode* aux = new linkedListNode();
    aux -> data = value;
    return aux;
}
/*
  No se utilizo nodos de cabecera para el puntero tail y head
  Note: ya viene inicializado los punteros next y prev a NULL
*/
void dCircularLinkedList::pushFront (int value) {
    linkedListNode* tmp = createNode(value);
    if (!head) {
      head = tmp;
      tail = tmp;
      // enlazando punteros del objeto
      tmp -> prev = tail;
      tmp -> next = head;
    }
    else {
      tmp -> next = head;
      tmp -> prev = head -> prev; // enlazando inicio del nuevo nodo 
      head -> prev = tmp;
      head = tmp;
      tail -> next = head; //enlazando el final de la lista
    }
}

void dCircularLinkedList::pushBack (int value) {
    linkedListNode* tmp = createNode(value);
    if (!tail) {
      tail = tmp;
      head = tmp;
      tmp -> next = tail;
      tmp -> next = head;
    }
    else {
      tmp -> prev = tail;
      tmp -> next = tail -> next;
      tail -> next = tmp;
      tail = tmp;
      head -> prev = tail;
    }
}

void dCircularLinkedList::pushBeforeX (int value, int nodex) {
    if (!head) return;
    bool flag = false;
    linkedListNode** indirectNode = findIndirect(nodex,flag); // revisar  la implementacion
    if (!flag) {
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = createNode(value);
    /*
      (*indirectNode) corresponde al nodo next previo al nodo que contiene el dato nodex.
    */
    tmp -> next = (*indirectNode);
    tmp -> prev = (*indirectNode) -> prev;
    (*indirectNode) -> prev = tmp;
    if ((*indirectNode) == head) tail -> next = tmp;
    (*indirectNode) = tmp;
}

void dCircularLinkedList::pushAfterX (int value, int nodex) {
    if (!head) return;
    bool flag = false;
    linkedListNode** indirectNode = rfindIndirect(nodex,flag); //revisar la impleentacion
    if (!flag) {
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = createNode(value);
    /*
      (*indirectNode) corresponde al nodo prev siguiente al nodo que contiene el dato nodex.
    */
    tmp -> prev = (*indirectNode);
    tmp -> next = (*indirectNode) -> next;
    (*indirectNode) -> next = tmp;
    (*indirectNode) = tmp;
}

void dCircularLinkedList::popFront () {
    if (!head) return;  // verificar que la lista tenga algun elemento
    linkedListNode* tmp = head;
    if (head -> next == head) { // un unico elemento
      head = NULL;
      tail = NULL;
    }
    else {
      head = head -> next;
      head -> prev = tail; //importante para evitar punteros colgantes (core dump)
    }
    delete tmp;
}

void dCircularLinkedList::popBack () {
    if (!tail) return; 
    linkedListNode* tmp = tail;
    if (tail -> prev == tail) {
      head = NULL;
      tail = NULL;
    }
    else {
      tail = tail -> prev;
      tail -> next = head;
    }
    delete tmp;
}

void dCircularLinkedList::popX (int value) {
    if (!head) return;
    bool flag = false;
    linkedListNode** indirect = findIndirect(value,flag);
    if (!(*indirect)) { // null -> busqueda fallida 
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = (*indirect);
    if (head == tail) { //indica que el nodo encontrado es el unico
      head == NULL;
      tail == NULL;
    }
    else if (head == (*indirect)) { // .. es el primero
      head = head -> next;
      head -> prev = NULL;
    }
    else if (tail == (*indirect)) { // .. es el ultimo
      tail = tail -> prev;
      tail -> next = NULL;
    }
    else { // .. default
      (*indirect) = tmp -> next;
      (*indirect) -> prev = tmp -> prev;
    }
    delete tmp;
}

void dCircularLinkedList::popBeforeX (int value) {
    if (!head) return;
    if (head -> data == value) {
      std::cout << "Nodo anterior no existente en la Lista\n";
      return;
    }
    bool flag = false;
    linkedListNode** indirect = findIndirect(value,flag);
    if(!(*indirect)) {
      std::cout << "No se encontro el Nodo.\n";
      return;
    }
    linkedListNode* tmp = (*indirect) -> prev;
    if (head == tmp) { // si se quiere eliminar el primer nodo , necesita actualizar
      head = (*indirect);
      head -> prev = NULL;
    }
    else { // eliminacion de nodo generico
      linkedListNode* before = tmp -> prev;
      before -> next = (*indirect);
      (*indirect) -> prev = before;
    }
    delete tmp;
}

void dCircularLinkedList::popAfterX (int value) {
    if (!head) return;
    if (tail -> data == value) {
      std::cout << "Nodo posterior no existente en la Lista\n";
      return;
    }
    bool flag = false;
    linkedListNode** indirect = rfindIndirect(value,flag);
    if (!(*indirect)) {
      std::cout << "No se encontro el Nodo\n";
      return;
    } 
    linkedListNode* tmp = (*indirect) -> next;
    if (tail == tmp) { // si se quiere eliminar el ultimo nodo , necesita actualizar
      tail = (*indirect);
      tail -> next = NULL;
    }
    else { // eliminacion de nodo generico
      linkedListNode* after = tmp -> next;
      after -> prev = (*indirect);
      (*indirect) -> next = after;
    }
}

void dCircularLinkedList::displayNodes () {
    linkedListNode* walk = head;
    while (walk != NULL) {
      std::cout << walk -> data << std::endl;
      walk = walk -> next;
    }
}
linkedListNode** dCircularLinkedList::findIndirect (int value, bool &flag) {
    linkedListNode** indirect = &head;
    while ((*indirect) -> data != value && !flag) {
        if ((*indirect) != head) indirect = &(*indirect) -> next;
        else flag = true;
    }
    return indirect;
}
linkedListNode** dCircularLinkedList::rfindIndirect (int value, bool &flag) {
    linkedListNode** indirect = &tail;
    while ((*indirect) -> data != value && !flag) {
        if ((*indirect) != head) indirect = &(*indirect) -> prev;
        else flag = true;
    }
    return indirect;
    linkedListNode** indirect = &tail;
    while ((*indirect) && (*indirect) -> data != value) {
        indirect = &(*indirect) -> prev;
    }
    return indirect;
}

int main() {
  return 0;
}