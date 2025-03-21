#include <ostream>
#include <iostream>
#include <memory>

// 3. Implemente una lista enlazada que utilice nodos que simplemente contengan un valor y una dirección de memoria de un nodo. Adicionalmente, agregue las siguientes
// funciones para manejar la lista:

// i. create_node(): devuelve un nodo.
// ii. push_front(): inserta un nodo al frente de la lista.
// iii. push_back(): inserta un nodo al final de la lista.
// iv. insert(): inserta un nodo en la posición que se le pase a la función. Si se le pasa una posición mayor al largo de la lista, se debe indicar lo ocurrido y se debe de agregar el nodo al final de la lista.
// v. erase(): borra un nodo en la posición que se le pase a la función. Similar a la función insert(), si la posición es mayor que el largo de la lista, se debe de borrar el último nodo.
// vi. print_list(): imprime la lista completa, separando el valor en cada nodo con “->”.

// Presentar ejemplos que verifiquen el funcionamiento requerido en las funciones i-vi y, muy importante para el ejercicio, sólo utilizar smart pointers. 

struct Nodo{
    int valor;
    std::shared_ptr<Nodo> next;
};

struct ListaEnlazada{
    std::shared_ptr<Nodo> head;
    std::shared_ptr<Nodo> tail;
    size_t tamano;
};

//devuelve un nodo.
std::shared_ptr<Nodo> create_node(int valor) {
    return std::make_shared<Nodo>(Nodo{valor, nullptr}); // crea un nodo con shared ptr
}

//inserta un nodo al frente de la lista.
bool push_front(ListaEnlazada *list, int valor){
    auto nuevonodo = create_node(valor);
    if (nuevonodo == nullptr){
        return false; // fallo el createnode
    }

    nuevonodo->next = list->head; // el siguiente al nuevo nodo va a ser la actual head, ya que el nuevo se va a posicionar adelante
    list->head = nuevonodo; // actualizamos el puntero head

    if(list->tail==nullptr){ 
        list->tail = nuevonodo; // caso de que la tail estaba vacia (lista vacia) el tail tamb ddebe apuntar al nuevo nodo (lista de solo 1 nodo que es head y tail)
        return true;
    }
    list->tamano++; // incrementa tamano
    return true;
}


//inserta un nodo al final de la lista.
bool push_back(ListaEnlazada *list, int valor){
    auto nuevonodo = create_node(valor);
    if (nuevonodo == nullptr){
        return false; // fallo el createnode
    }
    if(list->head==nullptr){//si esta vacia
        list->head = nuevonodo;
        list->tail = nuevonodo; // solo tiene 1 nodo y es nuevonodo
        return true;
    }
    list->tail->next = nuevonodo; // Si la lista no está vacía, recorre hasta el final y agrega el nuevo nodo atras del anterior tail
    list->tail = nuevonodo; // actualizamos puntero tail

    list->tamano++; // incrementa tamano
    return true;
}


//inserta un nodo en la posición que se le pase a la función. Si se le pasa una posición mayor al largo de la lista, se debe indicar lo ocurrido y se debe de agregar el nodo al final de la lista.
bool insert(ListaEnlazada *list, int valor, int pos){
    auto nuevonodo = create_node(valor);
    if (nuevonodo == nullptr){
        return false; // fallo el createnode
    }
    int largo = 0; // inicializamos contador
    std::shared_ptr<Nodo> actual = list->head;
    while(actual != nullptr){
        actual = actual->next;
        largo++; // recorremos todos los nodos para saber el largo de la lista
    }

    if (pos>largo){
        std::cout << "la posicion excede el largo de la lista - el nodo se ingresara al final" << std::endl;
        push_back(list, valor); // usamos pushback para meterlo al final
        list->tamano++;
        return true;
    }

    // caso que la posicion no excede el largo de la lista:
    std::shared_ptr<Nodo> temp = list->head;
    for(int i = 0; i<pos-1; i++){
        temp = temp->next; // recorremos hasta pararnos en el nodo anterior a la posicion nada 
    }
    std::shared_ptr<Nodo>aux = temp->next;
    temp->next = nuevonodo;
    nuevonodo->next = aux; // actualizamos punteros metiendo el nodo en temp next (la posicion dada)

    list->tamano++; // incrementamos tamano
    return true;
}

//borra un nodo en la posición que se le pase a la función. Similar a la función insert(), si la posición es mayor que el largo de la lista, se debe de borrar el último nodo.
bool erase(ListaEnlazada *list, int valor, int pos){
    int largo = 0;
    std::shared_ptr<Nodo> actual = list->head; 
    while(actual != nullptr){
        actual = actual->next;
        largo++; // recorremos todos los nodos para saber el largo de la lista
    }

    if (pos>largo){
        std::cout << "la posicion excede el largo de la lista - se eliminara el nodo del final" << std::endl;
        if (list->head == nullptr) {
            return false; // Lista vacía
        }    
        std::shared_ptr<Nodo> anteult = list->head;
        while(anteult->next->next != nullptr){
            anteult = anteult->next; // recorremos hasta llegar al anteultimo
        }
        if (anteult->next == nullptr) { // solo hay 1 nodo
            list->head = nullptr;
            list->tail = nullptr; // vaciamos todo
            return true;
        }    
        list->tail = anteult; // caso que hay mas de 1, la tail pasa a ser el anteultimo y su siguiente se elimina
        anteult->next = nullptr;

        list->tamano--;
        return true;
    }

    // caso que la posicion no excede el largo de la lista:
    std::shared_ptr<Nodo> temp = list->head;
    for(int i = 0; i<pos-1; i++){
        temp = temp->next; // recorremos hasta la posicion arrancando desde el inicio(head)
    }
    std::shared_ptr<Nodo>aux = temp->next->next;
    temp->next = aux; //eliminamos temp->next ya que este pasa a ser el que le seguia 

    list->tamano--; //decrementamos tamano
    return true;
}

//imprime la lista completa, separando el valor en cada nodo con “->”.
void print_list(ListaEnlazada *list){
    if(list->head==nullptr){
        std::cout << "La lista está vacía." << std::endl;
        return; // lista vacia
    }

    std::shared_ptr<Nodo> actual = list->head;
    std::cout<< actual->valor; // imprimimos la head (ya sabemos que no es null)
    while(actual->next!=nullptr){
        actual = actual->next; // recorremos hasta llegar al anterior tail y vamos imprimiendo
        std::cout<< "->" << actual->valor;
    }
    if (list->tail != nullptr){
        std::cout << "->" << list->tail->valor; // si no es null imprimimos la tail ( si era null probablemente tenia solo 1 elemento y ni entro al ciclo while anterior)
    }
    std::cout << std::endl;

    return;
}


int main() {
    ListaEnlazada lista = {nullptr, nullptr, 0};  // Lista vacía inicialmente

    //ii Insertar nodos al frente (push_front)
    std::cout << "Insertando nodos al frente:" << std::endl;
    push_front(&lista, 10);
    push_front(&lista, 20);
    push_front(&lista, 30); 
    print_list(&lista); //30->20->10

    //iii Insertar nodos al final (push_back)
    std::cout << "\nInsertando nodos al final:" << std::endl;
    push_back(&lista, 40);
    push_back(&lista, 50); 
    print_list(&lista); // 30->20->10->40->50

    //iv Insertar en una posición específica (insert)
    std::cout << "\nInsertando en posición 2:" << std::endl;
    insert(&lista, 25, 2);
    print_list(&lista); //30->20->25->10->40->50

    //iv.b Insertar en una posición mayor al tamaño (insert)
    std::cout << "\nInsertando en una posición mayor al tamaño:" << std::endl;
    insert(&lista, 60, 10); 
    print_list(&lista); // 30->20->25->10->40->50->60

    //v. Borrar un nodo en una posición específica (erase)
    std::cout << "\nBorrando nodo en posición 2:" << std::endl;
    erase(&lista, 0, 2); 
    print_list(&lista); // 30->20->10->40->50->60

    //v.b Borrar un nodo en una posición mayor al tamaño (erase)
    std::cout << "\nBorrando nodo en una posición mayor al tamaño:" << std::endl;
    erase(&lista, 0, 10); 
    print_list(&lista); // 30->20->10->40->50

    //v.c Borrar el primer nodo (erase)
    std::cout << "\nBorrando el primer nodo:" << std::endl;
    erase(&lista, 0, 0); 
    print_list(&lista); // 20->10->40->50

    //v.d Borrar el último nodo
    std::cout << "\nBorrando el último nodo:" << std::endl;
    erase(&lista, 0, 3); 
    print_list(&lista); //20->10->40

    return 0;
}