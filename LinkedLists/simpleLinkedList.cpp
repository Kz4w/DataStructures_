/*
  Name: Sandro Mamani
  Simple implementation for Linked List - Oswaldo Cairo 
*/
#include <iostream>

class linkedListNode {
  private:
    int data{0};
    linkedListNode* next;
  public:
    linkedListNode() {
      next = NULL;
    }
  friend class simpleLinkedList;
};

/*
  clase y metodos modificado del libro de Oswaldo cairo
*/

class simpleLinkedList {
  private:
    linkedListNode* head;
  public:
    simpleLinkedList() {
      head = NULL;
    }
    linkedListNode* createNode    (int);
    linkedListNode** findIndirect (int);
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

linkedListNode* simpleLinkedList::createNode (int value) {
    linkedListNode* aux = new linkedListNode();
    aux -> data = value;
    return aux;
}

void simpleLinkedList::pushFront (int value) {
    linkedListNode* tmp = createNode(value);
    tmp -> next = head;
    head = tmp;
}

void simpleLinkedList::pushBack (int value) {
    linkedListNode** indirect = &head;
  /*
    iteracion sobre punteros, indirectamente accedemos a los nodos
  */
    while ((*indirect))
      indirect = &(*indirect) -> next;
    (*indirect) = createNode(value);
}

void simpleLinkedList::pushBeforeX (int value, int nodex) {
    if (!head) return;
    linkedListNode** indirectNode = findIndirect(nodex); // revisar el metodo
    if (!(*indirectNode)) {
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    linkedListNode* tmp = createNode(value);
    tmp -> next = (*indirectNode);
    (*indirectNode) = tmp;
}

void simpleLinkedList::pushAfterX (int value, int nodex) {
    if (!head) return;
    linkedListNode** indirectNode = findIndirect(nodex); // revisar implementacion
    if (!(*indirectNode)) {
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    /*
      El puntero devuelto por indirect corresponde al puntero next del Nodo anterior a X.
      Despues de la creacion nodo se hacen las conexiones con los otros nodos.
    */
    linkedListNode* tmp = createNode(value);
    tmp -> next = (*indirectNode) -> next;
    (*indirectNode) -> next = tmp;
}

void simpleLinkedList::popFront () {
    if (!head) return;  // verificar que la lista tenga algun elemento
    linkedListNode* tmp = head;
    head = head -> next;
    delete tmp;
}

void simpleLinkedList::popBack () {
    if (!head) return;
    /*
      p
    */
    linkedListNode** walk = &head; 
    while ((*walk) -> next)
      walk = &(*walk) -> next;
    delete (*walk); // desreferenciando ultimo puntero indirecto al ultimo nodo
    (*walk) = NULL; // evitando punteros colgantes estableciendo NULL al ultimo puntero
}

void simpleLinkedList::popX (int value) {
    if (!head) return;
    linkedListNode** indirect = findIndirect(value); // revisar la implementacion de metodo
    if (!(*indirect)) { // null = busqueda fallida 
      std::cout << "No se encontro el nodo.\n";
      return;
    }
    /*
      Nos ubicamos en el punteero next del nodo anterior a X
    */
    linkedListNode* tmp = (*indirect);
    (*indirect) = (*indirect) -> next;
    delete tmp;
}

void simpleLinkedList::popBeforeX (int value) {
    if (!head) return;
    if (head -> data == value) {
      std::cout << "Nodo anterior no existente en la Lista\n";
      return;
    }
      linkedListNode** before = NULL; // nos ubica a un puntero ante de indirect
      linkedListNode** indirect = &head;

      //la iteracion se realizar con 2 punteros para guardar un acceso al puntero anterior a indirect
    
    while ((*indirect) && (*indirect) -> data != value) {
      before = indirect;
      indirect = &(*indirect) -> next;
    }

    if(!(*indirect)) {
      std::cout << "No se encontro el Nodo.\n";
      return;
    }
    /*
      guardamos la direccion del puntero a eliminar antes de modificar los valores de los punteros
    */
    linkedListNode* tmp = (*before);
    (*before) = (*indirect);
    delete tmp;
}

void simpleLinkedList::popAfterX (int value) {
    if (!head) return;
    linkedListNode** indirect = findIndirect(value);
    if (!(*indirect)) {
      std::cout << "No se encontro el Nodo\n";
      return;
    } 
    else if (!(*indirect) -> next) {
      std::cout << "Nodo posterior no existente en la Lista\n";
      return;
    }
    /*
      Nos ubicamos en el puntero next del nodo M   , M -> X -> A -> NULL
      con el cual accedemos indirectamente al nodo X.

      Los cambios solo se hacen modificando los valores de los punteros, 
      siendo tmp un auxiliar para guardar la direccion del nodo a eliminar.
    */
    linkedListNode* tmp = (*indirect) -> next;
    (*indirect) -> next = (*indirect) -> next -> next;
    delete tmp;
}

void simpleLinkedList::displayNodes () {
    linkedListNode* walk = head;
    while (walk != NULL) {
      std::cout << walk -> data << std::endl;
      walk = walk -> next;
    }
}
/*
  iteramos sobre los punteros sin tocar los nodos, empezando por el punetero inicial
*/
linkedListNode** simpleLinkedList::findIndirect (int value) {
    linkedListNode** indirect = &head;
    while ((*indirect) && (*indirect) -> data != value) {
        indirect = &(*indirect) -> next;
    }
    return indirect;
}

int main () {
  short i = 0;
  std::cout << "::Creacion de la list\n";
  simpleLinkedList* book1 = new simpleLinkedList();

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