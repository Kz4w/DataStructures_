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
  friend class doublyLinkedList;
};

class doublyLinkedList {
  private:
    linkedListNode* head;
    linkedListNode* tail;
  public:
    doublyLinkedList() {
      head = NULL;
      tail = NULL;
    }
    linkedListNode* createNode    (int);
    linkedListNode** findIndirect (int);
    linkedListNode** rfindIndirect(int);
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

linkedListNode* doublyLinkedList::createNode (int value) {
    linkedListNode* aux = new linkedListNode();
    aux -> data = value;
    return aux;
}
/*
  No se utilizo nodos de cabecera para el puntero tail y head
  Note: ya viene inicializado los punteros next y prev a NULL
*/
void doublyLinkedList::pushFront (int value) {
    linkedListNode* tmp = createNode(value);
    if (!head) {
      head = tmp;
      tail = tmp;
    }
    else {
      tmp -> next = head;
      head -> prev = tmp;
      head = tmp;
    }
}

void doublyLinkedList::pushBack (int value) {
    linkedListNode* tmp = createNode(value);
    if (!tail) {
      tail = tmp;
      head = tmp;
    }
    else {
      tmp -> prev = tail;
      tail -> next = tmp;
      tail = tmp;
    }
}

void doublyLinkedList::pushBeforeX (int value, int nodex) {
    if (!head) return;
    linkedListNode** indirectNode = findIndirect(nodex); // revisar  la implementacion
    if (!(*indirectNode)) {
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
    (*indirectNode) = tmp;
}

void doublyLinkedList::pushAfterX (int value, int nodex) {
    if (!head) return;
    linkedListNode** indirectNode = rfindIndirect(nodex); //revisar la impleentacion
    if (!(*indirectNode)) {
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

void doublyLinkedList::popFront () {
    if (!head) return;  // verificar que la lista tenga algun elemento
    linkedListNode* tmp = head;
    if (!tmp -> next) {
      head = NULL;
      tail = NULL;
    }
    else {
      head = tmp -> next;
      head -> prev = NULL; //importante para evitar punteros colgantes (core dump)
    }
    delete tmp;
}

void doublyLinkedList::popBack () {
    if (!tail) return; 
    linkedListNode* tmp = tail;
    if (!tmp -> prev) {
      head = NULL;
      tail = NULL;
    }
    else {
      tail = tmp -> prev;
      tail -> next = NULL;
    }
    delete tmp;
}

void doublyLinkedList::popX (int value) {
    if (!head) return;
    linkedListNode** indirect = findIndirect(value);
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

void doublyLinkedList::popBeforeX (int value) {
    if (!head) return;
    if (head -> data == value) {
      std::cout << "Nodo anterior no existente en la Lista\n";
      return;
    }
    linkedListNode** indirect = findIndirect(value);
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

void doublyLinkedList::popAfterX (int value) {
    if (!head) return;
    if (tail -> data == value) {
      std::cout << "Nodo posterior no existente en la Lista\n";
      return;
    }
    linkedListNode** indirect = rfindIndirect(value);
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

void doublyLinkedList::displayNodes () {
    linkedListNode* walk = head;
    while (walk != NULL) {
      std::cout << walk -> data << std::endl;
      walk = walk -> next;
    }
}
linkedListNode** doublyLinkedList::findIndirect (int value) {
    linkedListNode** indirect = &head;
    while ((*indirect) && (*indirect) -> data != value) {
        indirect = &(*indirect) -> next;
    }
    return indirect;
}
linkedListNode** doublyLinkedList::rfindIndirect (int value) {
    linkedListNode** indirect = &tail;
    while ((*indirect) && (*indirect) -> data != value) {
        indirect = &(*indirect) -> prev;
    }
    return indirect;
}

int main() {
    short i = 0;
  std::cout << "::Creacion de la lista\n";
  doublyLinkedList* book1 = new doublyLinkedList();

  std::cout << "\nComprobando metodos a lista vacia (push)\n";
  book1 -> pushAfterX(0,0);
  book1 -> pushBeforeX(0,0);
  std::cout << "\nComprobando metodos a lista vacia (pop)\n";
  book1 -> popAfterX(0);
  book1 -> popBeforeX(0);
  book1 -> popFront();
  book1 -> popBack();
  std::cout << "\nIngresando datos (push_back)\n";
  for (i = 1; i < 10; i++)
    book1 -> pushBack(i*5);
  book1 -> displayNodes();
  std::cout << "\nIngresando datos (push_front)\n";
  for (i = 2; i < 10; i++)
    book1 -> pushFront(i*3);
  book1 -> displayNodes();
  std::cout << "\nComprobando Busqueda (push)\n";
  book1 -> pushBeforeX(150,0);
  book1 -> pushAfterX(250,0);
  book1 -> displayNodes();
  std::cout << "\nComprobando nodoInicial pushBeforeX y pushAfterX\n";
  book1 -> pushBeforeX(150,27);
  book1 -> pushAfterX(250,27);
  book1 -> displayNodes();
  std::cout << "Comprobando nodoMedio pushBeforeX y pushAfterX";
  book1 -> pushBeforeX(550,6);
  book1 -> pushAfterX(750,5);
  book1 -> displayNodes();
  std::cout << "\nComprobando nodoUltimo pushBeforeX y pushAfterX\n";
  book1 -> pushBeforeX(950,45);
  book1 -> pushAfterX(1250,45);
  book1 -> displayNodes();
  std::cout << "\nComprobando nodoPrimero popX popBeforeX PopAfterX\n";
  book1 -> popX(150);
  book1 -> popBeforeX(27); // no existe ErrorMsg
  book1 -> popAfterX(27);
  book1 -> displayNodes();
  std::cout << "\nComprobando nodoMedio popX popBeforeX PopAfterX\n";
  book1 -> popX(6);
  book1 -> popBeforeX(5);
  book1 -> popAfterX(5);
  book1 -> displayNodes();
  std::cout << "\nComprobando nodoUltimo popX popBeforeX PopAfterX\n";
  book1 -> popX(1250);
  book1 -> popBeforeX(45);
  book1 -> popAfterX(45); // no existe ErrorMsg
  book1 -> displayNodes();
  // Comprobando pop Back y PopFront hasta dejar 1 nodo
  std::cout << "\nComprobando popFront y popBack. Out -> 5 10 \n";
  i = 0;
  while (i <= 6) {
    book1 -> popFront();
    book1 -> popBack();
    i++;
  }
  book1 -> displayNodes();
  return 0;
}