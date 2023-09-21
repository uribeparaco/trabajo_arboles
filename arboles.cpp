//Julian David Ortiz Molina
//Juan Camilo Baez Bautista
//Brandon Stick Buitrago Ruiz

//Arbol

struct Nodo {
    int valor;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo* padre;
};

Nodo* arbol = NULL;

Nodo* crearNodo(int valor, Nodo* padre);
void insertarNodo(Nodo*& arbol, int valor, Nodo* padre);
void mostrarArbol(Nodo*& arbol, int nivel);
bool buscarNodoArbol(Nodo*& arbol, int valor);
void preorden(Nodo*& arbol);
void inorden(Nodo*& arbol);
void postorden(Nodo*& arbol);
void buscarParaEliminar(Nodo*& arbol, int valor);
void eliminarNodo(Nodo*& arbol);
Nodo* minimoNodo(Nodo*& arbol);
void menu();

int main() {
    menu();
    return 0;
}

Nodo* crearNodo(int valor, Nodo* padre) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->valor = valor;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    nuevoNodo->padre = padre;
    return nuevoNodo;
}

void insertarNodo(Nodo*& arbol, int valor, Nodo* padre) {
    if (arbol == NULL) {
        Nodo* nuevoNodo = crearNodo(valor, padre);
        arbol = nuevoNodo;
    } else {
        int valorRaiz = arbol->valor;
        if (valor < valorRaiz) {
            insertarNodo(arbol->izquierda, valor, arbol);
        } else {
            insertarNodo(arbol->derecha, valor, arbol);
        }
    }
}

void mostrarArbol(Nodo*& arbol, int nivel) {
    if (arbol == NULL) {
        return;
    } else {
        mostrarArbol(arbol->derecha, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            std::cout << "       ";
        }
        std::cout << arbol->valor << "\n";
        mostrarArbol(arbol->izquierda, nivel + 1);
    }
}

bool buscarNodoArbol(Nodo*& arbol, int valor) {
    if (arbol == NULL) {
        return false;
    } else if (arbol->valor == valor) {
        return true;
    } else if (valor < arbol->valor) {
        return buscarNodoArbol(arbol->izquierda, valor);
    } else {
        return buscarNodoArbol(arbol->derecha, valor);
    }
}

void preorden(Nodo*& arbol) {
    if (arbol == NULL) {
        return;
    } else {
        std::cout << arbol->valor << " -> ";
        preorden(arbol->izquierda);
        preorden(arbol->derecha);
    }
}

void inorden(Nodo*& arbol) {
    if (arbol == NULL) {
        return;
    } else {
        inorden(arbol->izquierda);
        std::cout << arbol->valor << " -> ";
        inorden(arbol->derecha);
    }
}

void postorden(Nodo*& arbol) {
    if (arbol == NULL) {
        return;
    } else {
        postorden(arbol->izquierda);
        postorden(arbol->derecha);
        std::cout << arbol->valor << " -> ";
    }
}

void buscarParaEliminar(Nodo*& arbol, int numeroEliminar) {
    if (arbol == NULL) {
        return;
    }

    if (numeroEliminar < arbol->valor) {
        buscarParaEliminar(arbol->izquierda, numeroEliminar);
    } else if (numeroEliminar > arbol->valor) {
        buscarParaEliminar(arbol->derecha, numeroEliminar);
    } else {
        eliminarNodo(arbol);
    }
}

void eliminarNodo(Nodo*& arbol) {
    if (arbol == NULL) {
        return;
    }

    if (arbol->izquierda == NULL && arbol->derecha == NULL) {
        Nodo* padre = arbol->padre;
        if (padre) {
            if (padre->izquierda == arbol) {
                padre->izquierda = NULL;
            } else {
                padre->derecha = NULL;
            }
        }
        delete arbol;
        arbol = NULL;
    } else if (arbol->derecha == NULL) {
        Nodo* temp = arbol;
        arbol = arbol->izquierda;
        arbol->padre = temp->padre;
        delete temp;
    } else if (arbol->izquierda == NULL) {
        Nodo* temp = arbol;
        arbol = arbol->derecha;
        arbol->padre = temp->padre;
        delete temp;
    } else {
        Nodo* minimo = minimoNodo(arbol->derecha);
        arbol->valor = minimo->valor;
        eliminarNodo(minimo);
    }
}

Nodo* minimoNodo(Nodo*& arbol) {
    if (arbol == NULL) {
        return NULL;
    } else if (arbol->izquierda) {
        return minimoNodo(arbol->izquierda);
    } else {
        return arbol;
    }
}

void menu() {
    int opcion, valor;
    while (true) {
        system("cls");
        
		std::cout << "ARBOL DE LOS MOSQUETEROS :)\n\n";
        std::cout << "\tMENU\n\n";
        std::cout << "1. Insertar un numero\n";
        std::cout << "2. Mostrar arbol\n";
        std::cout << "3. Buscar numero en el arbol\n";
        std::cout << "4. Mostrar arbol en preorden\n";
        std::cout << "5. Mostrar arbol en inorden\n";
        std::cout << "6. Mostrar arbol en posorden\n";
        std::cout << "7. Eliminar numero\n";
        std::cout << "8. Salir\n";
        std::cout << "\nIngrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese el numero a insertar: ";
                std::cin >> valor;
                insertarNodo(arbol, valor, NULL);
                break;
            case 2:
                std::cout << "\n\tARBOL\n";
                mostrarArbol(arbol, 0);
                std::cout << "\n";
                system("pause"); 
                break;
            case 3:
                std::cout << "Ingrese el numero a buscar:";
                std::cin >> valor;
                if (buscarNodoArbol(arbol, valor)) {
                    std::cout << "El numero " << valor << " esta en el arbol." << std::endl;
                } else {
                    std::cout << "El numero " << valor << " no esta en el arbol." << std::endl;
                }
                system("pause");
                break;
            case 4:
                std::cout << "\tArbol en preorden\n";
                preorden(arbol);
                std::cout << "\n";
                system("pause");
                break;
            case 5:
                std::cout << "\tArbol en inorden\n";
                inorden(arbol);
                std::cout << "\n";
                system("pause");
                break;
            case 6:
                std::cout << "\tArbol en posorden\n";
                postorden(arbol);
                std::cout << "\n";
                system("pause");
                break;
            case 7:
                std::cout << "Ingrese el numero a eliminar: ";
                std::cin >> valor;
                buscarParaEliminar(arbol, valor);
                break;
            case 8:
                return;
            default:
                std::cout << "Intente de nuevo." << std::endl;
                system("pause");
                break;
        }
    }
}
