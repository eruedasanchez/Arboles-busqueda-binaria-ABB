
template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), cantNodos(0) {
    /* Completar */
    /** Conjunto Vacio. No tenemos elementos en el arbol. Por lo tanto, la raiz apunta a nullptr y
     * la cantidad de nodos del ABB es igual a 0. */
}

template<class T>
void Conjunto<T>::destruir(Nodo* r) {
    if(r!= nullptr) {
        destruir(r->izq);
        destruir(r->der);
        delete r;
    }
}

template <class T>
Conjunto<T>::~Conjunto() { 
    /* Completar */
    destruir(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    /*** Caso 1: NO tenemos elementos en el ABB ***/
    if(cardinal() == 0){
        return false;
    }
    /*** Caso 2: Hay elementos en el ABB ***/
    Nodo* nodo_actual = _raiz;
    while(nodo_actual != nullptr) {
        if (nodo_actual->valor != clave) {
            /*** Caso 2.a: Hay elementos en el ABB y el valor del nodo al que estoy apuntando es menor al valor buscado
             * Tengo que buscar a clave en el subarbol derecho ***/
            if (nodo_actual->valor < clave) {
                nodo_actual = nodo_actual->der;
            } else {
                /*** Caso 2.b: Hay elementos en el ABB y el valor del nodo al que estoy apuntando es mayor al valor buscado
             * Tengo que buscar a clave en el subarbol izquerdo ***/
                if (nodo_actual->valor > clave) {
                    nodo_actual = nodo_actual->izq;
                }
            }
        } else {
            /*** Caso 3: Encontre el valor buscado y devuelvo verdadero ***/
            return true;
        }
    }
    /** Salgo del ciclo porque no hay mas elementos del ABB por recorrer. Por lo tanto, no encontre a clave */
    delete nodo_actual;
    return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    /** Se comienza chequeando si la clave ya pertenece al ABB. De ser asi, no se modifica el arbol. De lo contrario, se busca en donde insertarla. */
    if(!pertenece(clave)) {
        if(cardinal() == 0) {
            /** Caso 1: El ABB se encuentra vacia y vamos a insertar la clave como raiz del mismo */
            Nodo* nuevo_nodo = new Nodo(clave);
            _raiz = nuevo_nodo;
            cantNodos++;
            return;
        }
        /** Caso 2: El ABB NO se encuentra vacio y hay que insertar la clave */
        cantNodos++;
        Nodo* nodo_actual = _raiz;
        while(nodo_actual != nullptr) {
            if (nodo_actual->valor > clave) {
                /** Caso 2.a: El nodo del ABB al que se esta apuntando es mayor al valor de clave. Por lo tanto, se debe insertar en el subarbol izquierdo */
                if (nodo_actual->izq == nullptr) {
                    /** Caso 2.a.1: Si la rama izquierda del nodo actual se encuentra vacia, entonces se encontro al padre del nodo a insertar.
                     * Se inserta el nodo con su clave y el padre del nodo insertado es el nodo actual */
                    nodo_actual->izq = new Nodo(clave);
                    nodo_actual->izq->padre = nodo_actual;
                    return;
                }
                /** De lo contrario, se continua buscando donde insertar el nodo en el subarbol izquierdo */
                nodo_actual = nodo_actual->izq;
            }

            if (nodo_actual->valor < clave) {
                /** Caso 2.b: El nodo del ABB al que se esta apuntando es menor al valor de clave.
                 * Por lo tanto, se debe insertar en el subarbol derecho */
                 if (nodo_actual->der == nullptr) {
                     /** Caso 2.b.1: Si la rama derecha del nodo actual se encuntra vacia, se encontro al padre del nodo a insertar.
                      * Se inserta el nodo con su clave y el padre del nodo insertado es el nodo actual */
                    nodo_actual->der = new Nodo(clave);
                    nodo_actual->der->padre = nodo_actual;
                    return;
                }
                /** De lo contrario, se continua buscando donde insertar el nodo en el subarbol derecho */
                nodo_actual = nodo_actual->der;
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::minimo_version_nodo(Nodo* r) const {
    Nodo* nodo_actual = r;
    while (nodo_actual->izq != nullptr) {
        nodo_actual = nodo_actual->izq;
    }
    return nodo_actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo_version_nodo(Nodo* r) const {
    Nodo* nodo_actual = r;
    while (nodo_actual->der != nullptr) {
        nodo_actual = nodo_actual->der;
    }
    return nodo_actual->valor;
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(!pertenece(clave) || _raiz == nullptr){
        /** Caso 1: El nodo que contiene a clave no se encuentra en el ABB o el ABB es nil. NO se modifica nada */
        return;
    }
    if(cardinal() == 1) {
        /** Caso 2: El ABB tiene un solo elemento y como no ingreso al if anterior (caso 1), se elimina la raiz */
        delete _raiz;
        _raiz = nullptr;
        cantNodos--;
        return;
    }
    /** Caso 3: La clave se encuentra en el ABB y el arbol tiene mas de un elemento */
    Nodo* nodo_actual = _raiz;
    string direccion = "";
    /** Se busca el nodo a remover */
    while(nodo_actual->valor != clave) {
        if (nodo_actual->valor < clave) {
            nodo_actual = nodo_actual->der;
            direccion = "DER";
        } else {
            nodo_actual = nodo_actual->izq;
            direccion = "IZQ";
        }
    }

    /** Una vez que se sale del ciclo pueden suceder dos cosas.
     * La primera es haber recorrido todo el arbol y por lo tanto, la clave a borrar no se encuentra en el ABB  y no modifico el ABB.
     * La segunda es haber salido del ciclo porque se encontro el nodo que contiene a clave.
     * Entonces, se analizan los siguientes casos: */
    if (nodo_actual->valor == clave) {
        /** Se encontro el nodo que contiene a clave */
        if (nodo_actual->izq == nullptr && nodo_actual->der == nullptr) {
            /** Caso 4.a: El nodo a borrar es una hoja */
            if (direccion == "DER"){
                nodo_actual->padre->der = nullptr;
            }
            if (direccion == "IZQ"){
                nodo_actual->padre->izq = nullptr;
            }
            delete nodo_actual;
            cantNodos--;
        } else {
            if(nodo_actual->der != nullptr) {
                /** Caso 4.b: El nodo a borrar tiene un solo hijo derecho o dos hijos */
                T predecesor_inmediato = minimo_version_nodo(nodo_actual->der);
                remover(predecesor_inmediato);
                nodo_actual->valor = predecesor_inmediato;
            } else {
                /** Caso 4.c: El nodo a borrar tiene un solo hijo izquierdo */
                T sucesor_inmediato = maximo_version_nodo(nodo_actual->izq);
                remover(sucesor_inmediato);
                nodo_actual->valor = sucesor_inmediato;
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& elem) {
    /** Pre: La clave se encuentra en el ABB y tiene un elemento siguiente */
    if(!pertenece(elem)){
        assert(false);
    }
    Nodo* nodo_actual = _raiz;
    /** Se busca el nodo que contiene a clave en el ABB */
    while(nodo_actual->valor != elem) {
        if (nodo_actual->valor < elem) {
            nodo_actual = nodo_actual->der;
        } else {
            nodo_actual = nodo_actual->izq;
        }
    }
    /** Caso 1: Una vez que se encontro el nodo que contiene a clave en el ABB, como es el siguiente, se encuentra
     * en el subarbol derecho y sera el nodo mas a la izquierda de este */
    if(nodo_actual->der != nullptr) {
        nodo_actual = nodo_actual->der;
        while (nodo_actual->izq != nullptr) {
            nodo_actual = nodo_actual->izq;
        }
        return nodo_actual->valor;
    }
    /** Caso 2: Una vez que se encuentra el nodo que contiene a clave en el ABB, como no tiene hijo derecho, hoy que ir avanzando
     * hacia arriba hasta que el nodo actual sea una hoja o llegue a la raiz */
    Nodo* father = nodo_actual->padre;
    while(father != nullptr && nodo_actual == father->der) {
        nodo_actual = father;
        father = nodo_actual->padre;
    }
    return father->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* nodo_actual = _raiz;
    while (nodo_actual->izq != nullptr){
        nodo_actual = nodo_actual->izq;
    }
    return nodo_actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* nodo_actual = _raiz;
    while (nodo_actual->der !=  nullptr) {
        nodo_actual = nodo_actual->der;
    }
    return nodo_actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cantNodos;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}


