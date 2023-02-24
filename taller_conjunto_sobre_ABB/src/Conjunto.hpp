
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
    // assert(false);
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
    //assert(false);
}

template <class T>
void Conjunto<T>::remover(const T&) {
    assert(false);
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    assert(false);
}

template <class T>
const T& Conjunto<T>::minimo() const {
    assert(false);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    assert(false);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    assert(false);
    return 0;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

