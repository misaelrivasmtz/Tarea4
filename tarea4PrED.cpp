#include <iostream>
using namespace std;

//Implementacion de la lista 

//registro que administrara la informacion de la lista.
struct info{
    int id;
    string username;
    string profile;
};

class Node 
{
    //interfaz privada
    private:
        info data;
        // Tendra un nodo anterior
        Node *previous;
        // Tendra un nodo siguiente
        Node *next;

        //Como las variables son privadas debemos 
        // compartirlas con las funciones
        friend class LinkedList;
};

class LinkedList
{
    //Para los elementos de nuestra lista
    //El constructor
    public:
        // constructor
        LinkedList();
        // el destructor
        ~LinkedList();
        // Asigna memoria dinamicamente, el destructor libera memoria

        // funcion que devuelve el numero entero del primer nodo de
        // la lista HEAD
        info getFront() const;

        // funcion que nos va a devolver el numero del ultimo nodo 
        //de la lista TAIL
        info getBack() const;

        // Funcion para el nuevo nodo, que pasa el valor a la 
        //funcion
        void addFront(info dt);

        // Funcion para el nuevo nodo, que pasa el valor a la funcion
        void addBack(info dt);

        //Funcion para eliminar al primer Nodo
        void removeFront();

        //Funcion para eliminar al ultimo Nodo
        void removeBack();

        // Funcion para imprimir la informacion de forma inversa
        void printReverse();

        //Funcion para imprimir la lista del principio al final 
        // Mostrar de forma normal
        void printForward();
        
        void addDataFront();

        void addDataBack();
    
    private:
        //Declarar los punteros que apuntan a los nodos centinela
        Node *header;
        Node *trailer;
};

int main()
{
    info head, trailer;
    //crear un objeto de la lista una instancia
    LinkedList ll;
    // Añadir datos al inicio de la lista
    cout << "\nInsertando datos al inicio de la lista" << endl;
    ll.addDataFront();
    //  Anadir al final
    cout << "\nIngresando datos al final de la lista" << endl;
    ll.addDataBack();
    // Para imprimir
    cout << "\nImprimiendo los datos:" << endl;
    ll.printForward();

    cout << "\nImprimiendo los datos alreves:" << endl;
    ll.printReverse();   

    // Eliminar HEAD
    ll.removeFront();

    // Eliminar TAIL
    ll.removeBack();

    //Obtener HEAD
    cout << "\nLa informacion de HEAD es: " << endl;
    head = ll.getFront();
    cout << "ID: " << head.id <<endl;
    cout << "Usuario: " << head.username << endl;
    cout << "Perfil: " << head.profile << endl;

    // Obtener TAIL
    cout << "\nLa informacion de TAIL es: " << endl;
    trailer = ll.getBack();
    cout << "ID: " << trailer.id << endl;
    cout << "Usuario: " << trailer.username << endl;
    cout << "Perfil: " << trailer.profile << endl;

    return 0;
};

LinkedList::LinkedList(){
    // Se define dinamicamente la memoria 
    header = new Node;
    // creamos el trailer (que es el centinela final)
    trailer = new Node;
    //Tenemos que hacer que el header apunte al trailer, 
    // y el trailer al header
    header->next = trailer;
    trailer->previous = header;
    //Como la lista esta vacia se igual a NULL
    header->previous = NULL;
    trailer->next = NULL;
}

//Al final si se puede
LinkedList::~LinkedList(){
    // llama a la funcion removeFront
    //para cuando elimine el elemento de la lista que no este vacia
    //Sera cuando ambos nodos centinela se apunten, es decir no hay head ni tail
    while(header->next!=trailer){
        removeFront();
    }
    //eliminar individualmente
    delete header;
    delete trailer;
}
info LinkedList::getFront() const{
    // Devuelve el primer valor
    //acceder al header
    //accedemos a su dato
    return header->next->data;
}
info LinkedList::getBack() const{
    //Devuelve el ultimo nodo
    return trailer->previous->data;
}
void LinkedList::addFront(info dt){
    // anadir un nuevo nodo a la memoria que se pasa por valor
    Node *nd = new Node;
    //al nodo que tenemos le ponemos el dato
    nd->data = dt;
    nd->previous = header;
    // es decir que ahora esta apuntando al nodo head
    nd->next = header->next; 

    // cambiar los punteros del header, y del nodo head
    // su puntero anterior es el nuevo nodo
    // acceder al nodo head, su puntero previous es 
    // el nuevo nodo anadido a la lista
    header->next->previous = nd;

    // el puntero head 
    header->next = nd;

}
void LinkedList::addBack(info dt){
    Node *nd = new Node;
    nd->data = dt;
    nd->previous=trailer->previous;
    nd->next=trailer;

    //actualizar trailer
    // a traves de trailer accedemos a su nodo previo apunta al nuevo nodo
    trailer->previous->next = nd;
    trailer->previous = nd;
}
void LinkedList::removeFront(){
    // Eliminar el nodo del principio
    // Accedemos al nodo siguiente de head
    Node *nd=header->next->next;
    delete header->next;

    // actualizar los punteros del header y del nodo anterior
    header->next=nd;
    nd->previous=header;
}
void LinkedList::removeBack(){
    // Eliminar a final
    // tomar una referencia al nodo anterior al nodo tail
    Node *nd = trailer->previous->previous;

    delete trailer->previous;

    //actualizar el puntero apuntara al 
    //nodo anterior al nodo tail que se elimino
    trailer->previous=nd;
    nd->next=trailer;
}
void LinkedList::printReverse(){
    // Vamos a imprimirlos 
    // Va del final al principio
    //referencia a tail
    Node *nd=trailer->previous;

    //Si el nodo es diferente al centinela inicial
    while (nd!=header)
    {
        // se imprime el nodo
        cout << "-------------------------" << endl; 
        cout << "Id: "<< nd->data.id << endl;
        cout << "Usuario: " << nd->data.username << endl;
        cout << "Perfil: " << nd->data.profile << endl;
        //actualizar el nodo anterior
        nd=nd->previous;
    }    

}
void LinkedList::printForward(){
    // Vamos a imprimirlos 
    // Va del principio al final
    //referencia a head
    Node *nd=header->next;

    //Si el nodo es diferente al centinela final
    while (nd!=trailer)
    {
        // se imprime el nodo
        cout << "--------------------------"  << endl;
        cout << "Id: "<< nd->data.id << endl;
        cout << "Usuario: " << nd->data.username << endl;
        cout << "Perfil: " << nd->data.profile << endl;
        //actualizar el nodo al siguiente
        nd=nd->next;
    }    
}

//funcion que solicita datos al usuario para ingresarlo al inicio
void LinkedList::addDataFront(){
    char opc;
    info data;
    cout << "Agregar elemento (s/n)?: ";
    cin>>opc; cin.ignore();
    while(opc != 'n' && opc != 'N'){
        cout << "ID: ";
        cin>>data.id; cin.ignore();
        cout << "Usuario: ";
        getline(cin, data.username);
        cout << "Perfil (Admin - Cliente - Trabajador): ";
        getline(cin, data.profile);
        
        addFront(data);
        cout << "Agregar elemento (s/n)?: ";
        cin>>opc; cin.ignore();      
    }
}
//funcion que solicita datos al usuario para ingresarlos al final
void LinkedList::addDataBack(){
    char opc;
    info data;
    cout << "Agregar elemento (s/n)?: ";
    cin>>opc; cin.ignore();
    while(opc != 'n' && opc != 'N'){
        cout << "ID: ";
        cin>>data.id; cin.ignore();
        cout << "Usuario: ";
        getline(cin, data.username);
        cout << "Perfil (Admin - Cliente - Trabajador): ";
        getline(cin, data.profile);
        
        addBack(data);
        cout << "Agregar elemento (s/n)?: ";
        cin>>opc; cin.ignore();      
    }
}