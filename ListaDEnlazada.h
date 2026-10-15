/**
 * @file ListaDElazada.h
 * @brief Declaración e implementación de la plantilla de clase ListaDEnlazada y sus clases auxiliares Nodo e Iterador.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#ifndef PRÁCTICA_2_LISTADENLAZADA_H
#define PRÁCTICA_2_LISTADENLAZADA_H

#include "stdexcept"

template <class T> class Nodo;
template <class T> class ListaDEnlazada;

/**
 * @brief Nodo para una lista doblemente enlazada.
 * @tparam T Tipo de dato almacenado en el nodo.
 */
template <class T>
class Nodo {
public:
    T dato;         /**< Dato almacenado en el nodo. */
    Nodo<T> *ant;   /**< Puntero al nodo anterior. */
    Nodo<T> *sig;   /**< Puntero al nodo siguiente. */

    /**
     * @brief Constructor de la clase Nodo.
     * @param aDato Elemento que guardará el nodo.
     * @param aAnt Puntero al nodo anterior (por defecto nullptr).
     * @param aSig Puntero al nodo siguiente (por defecto nullptr).
     */
    Nodo(const T &aDato, Nodo<T> *aAnt = nullptr, Nodo<T> *aSig = nullptr): dato(aDato), ant(aAnt), sig(aSig) {}
};

/**
 * @brief Iterador para recorrer elementos de una ListaDEnlazada.
 * @tparam T Tipo de dato almacenado en la lista.
 */
template<class T>
class Iterador {
    Nodo<T> *nodo; /**< Puntero al nodo actual sobre el que se posiciona el iterador. */
    friend class ListaDEnlazada<T>;
public:

    /**
     * @brief Constructor del iterador.
     * @param aNodo Nodo inicial donde se posicionará el iterador.
     */
    Iterador(Nodo<T> *aNodo): nodo(aNodo) {}

    /**
     * @brief Comprueba si el iterador apunta a una posición válida.
     * @return true si el nodo actual no es nullptr, false en caso contrario.
     */
    bool hayAnterior() {
        return nodo != nullptr;
    }

    /**
     * @brief Comprueba si el iterador apunta a una posición válida.
     * @return true si el nodo actual no es nullptr, false en caso contrario.
     */
    bool haySiguiente() {
        return nodo != nullptr;
    }

    /**
     * @brief Desplaza el iterador al nodo anterior.
     */
    void anterior() {
        if (nodo != nullptr) {
            nodo = nodo->ant;
        }
    }

    /**
     * @brief Desplaza el iterador al nodo siguiente.
     */
    void siguiente() {
        if (nodo != nullptr) {
            nodo = nodo->sig;
        }
    }

    /**
     * @brief Obtiene una referencia al dato sobre el que está posicionado el iterador.
     * @return Referencia al dato almacenado en el nodo actual.
     * @throw std::out_of_range Si el iterador apunta a nulo.
     */
    T &dato() {
        if (nodo == nullptr) {
            throw std::out_of_range("El iterador apunta a nulo.");
        }
        return nodo->dato;
    }

    /**
     * @brief Comprueba si el iterador ha llegado al final (es decir, apunta a nulo).
     * @return true si el nodo actual es nullptr, false en caso contrario.
     */
    bool fin() const {
        return nodo == nullptr;
    }

    /**
     * @brief Avanza el iterador a la siguiente posición (alias de siguiente()).
     */
    void avanza() {
        siguiente();
    }

    /**
     * @brief Obtiene la referencia al dato actual (alias de dato()).
     * @return Referencia al dato almacenado en el nodo actual.
     * @throw std::out_of_range Si el iterador apunta a nulo.
     */
    T& getdato() {
        return dato();
    }
};

/**
 * @brief Estructura de datos de tipo Lista Doblemente Enlazada.
 * @tparam T Tipo de elemento que almacena la lista.
 */
template<class T>
class ListaDEnlazada {
private:
    Nodo<T> *cabecera, *cola; /**< Punteros al primer y último nodo de la lista. */
    int numElementos;         /**< Cantidad de elementos guardados en la lista. */

public:

    /**
     * @brief Constructor por defecto. Crea una lista vacía.
     */
    ListaDEnlazada(): cabecera(nullptr), cola(nullptr), numElementos(0){}

    /**
     * @brief Constructor de copia. Crea una lista clonando los elementos de otra.
     * @param origen Lista desde la cual se copiarán los datos.
     */
    ListaDEnlazada(const ListaDEnlazada& origen): cabecera(nullptr), cola(nullptr), numElementos(0) {
        Nodo<T>* actual = origen.cabecera;
        while (actual != nullptr) {
            insertaFin(actual->dato);
            actual = actual->sig;
        }
    }

    /**
     * @brief Destructor. Libera la memoria dinámica asignada a todos los nodos.
     */
    ~ListaDEnlazada() {
        while (cabecera != nullptr) {
            Nodo<T>* aux = cabecera;
            cabecera = cabecera->sig;
            delete aux;
        }
        cola = nullptr;
        numElementos = 0;
    }

    /**
     * @brief Operador de asignación.
     * @param origen Lista que se copiará en la lista actual.
     * @return Referencia a la lista actual (*this).
     */
    ListaDEnlazada<T>& operator=(ListaDEnlazada<T>&& origen) noexcept {
        if (this != &origen) {
            this->~ListaDEnlazada();
            cabecera = origen.cabecera;
            cola = origen.cola;
            numElementos = origen.numElementos;

            origen.cabecera = nullptr;
            origen.cola = nullptr;
            origen.numElementos = 0;
        }
        return *this;
    }

    /**
     * @brief Obtiene una referencia al primer elemento de la lista.
     * @return Referencia al dato almacenado en la cabecera.
     * @throw std::out_of_range Si la lista está vacía.
     */
    T& inicio() {
        if (cabecera == nullptr) throw std::out_of_range("La lista esta vacia.");
        return cabecera->dato;
    }

    /**
     * @brief Obtiene una referencia al último elemento de la lista.
     * @return Referencia al dato almacenado en la cola.
     * @throw std::out_of_range Si la lista está vacía.
     */
    T& fin() {
        if (cola == nullptr) throw std::out_of_range("La lista esta vacia.");
        return cola->dato;
    }

    /**
     * @brief Devuelve un iterador posicionado al principio de la lista.
     * @return Iterador situado en la cabecera.
     */
    Iterador<T> iterador() const {
        return Iterador<T>(cabecera);
    }

    /**
     * @brief Devuelve un iterador posicionado al final de la lista.
     * @return Iterador situado en la cola.
     */
    Iterador<T> iteradorFin() const {
        return Iterador<T>(cola);
    }

    /**
     * @brief Inserta un nuevo elemento al principio de la lista.
     * @param dato Elemento a insertar.
     */
    void insertaInicio(const T &dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato, nullptr, cabecera);

        if (cabecera != nullptr) {
            cabecera->ant = nuevo;
        } else {
            cola = nuevo;
        }

        cabecera = nuevo;
        numElementos++;
    }

    /**
     * @brief Inserta un nuevo elemento al final de la lista.
     * @param dato Elemento a insertar.
     */
    void insertaFin(const T &dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato, cola, nullptr);

        if (cola != nullptr) {
            cola->sig = nuevo;
        } else {
            cabecera = nuevo;
        }

        cola = nuevo;
        numElementos++;
    }

    /**
     * @brief Inserta un elemento antes de la posición apuntada por el iterador.
     * @param i Iterador que marca el punto de inserción.
     * @param dato Elemento a insertar.
     */
    void inserta(Iterador<T> &i, const T &dato) {

        if (i.nodo == nullptr) {
            insertaFin(dato);
        } else if (i.nodo == cabecera) {
            insertaInicio(dato);
        } else {
            Nodo<T>* nuevo = new Nodo<T>(dato, i.nodo->ant, i.nodo);
            i.nodo->ant->sig = nuevo;
            i.nodo->ant = nuevo;
            numElementos++;
        }

    }

    /**
     * @brief Elimina el primer elemento de la lista.
     * @throw std::out_of_range Si la lista está vacía.
     */
    void borraInicio() {
        if (cabecera == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        }

        Nodo<T>* aBorrar = cabecera;
        cabecera = cabecera->sig;

        if (cabecera != nullptr) {
            cabecera->ant = nullptr;
        } else {
            cola = nullptr;
        }

        delete aBorrar;
        numElementos--;
    }

    /**
     * @brief Elimina el último elemento de la lista.
     * @throw std::out_of_range Si la lista está vacía.
     */
    void borraFinal() {
        if (cola == nullptr) {
            throw std::out_of_range("La lista esta vacia.");
        }

        Nodo<T>* aBorrar = cola;
        cola = cola->ant;

        if (cola != nullptr) {
            cola->sig = nullptr;
        } else {
            cabecera = nullptr;
        }

        delete aBorrar;
        numElementos--;
    }

    /**
     * @brief Elimina el elemento apuntado por el iterador y avanza dicho iterador al siguiente nodo.
     * @param i Iterador posicionado sobre el elemento a borrar.
     * @throw std::out_of_range Si el iterador apunta a nulo.
     */
    void borra(Iterador<T> &i) {
        if (i.nodo == nullptr) {
            throw std::out_of_range("El iterador apunta a nulo.");
        }

        Nodo<T>* aBorrar = i.nodo;

        i.nodo = i.nodo->sig;

        if (aBorrar == cabecera) {
            borraInicio();
        } else if (aBorrar == cola) {
            borraFinal();
        } else {
            aBorrar->ant->sig = aBorrar->sig;
            aBorrar->sig->ant = aBorrar->ant;
            delete aBorrar;
            numElementos--;
        }
    }

    /**
     * @brief Devuelve el número total de elementos en la lista.
     * @return Cantidad de elementos actuales.
     */
    int tam() const{
        return numElementos;
    }

    /**
     * @brief Concatena la lista actual con otra lista parámetro.
     * @param l Lista cuyos elementos se agregarán al final de una nueva lista.
     * @return Nueva lista resultante de la concatenación.
     */
    ListaDEnlazada<T> concatena(const ListaDEnlazada<T> &l) const{
        ListaDEnlazada<T> resultado;

        Nodo<T>* actual = cabecera;
        while (actual != nullptr) {
            resultado.insertaFin(actual->dato);
            actual = actual->sig;
        }

        actual = l.cabecera;
        while (actual != nullptr) {
            resultado.insertaFin(actual->dato);
            actual = actual->sig;
        }

        return resultado;
    }

    /**
     * @brief Sobrecarga del operador + para concatenar dos listas.
     * @param l Lista a concatenar.
     * @return Nueva lista resultante.
     */
    ListaDEnlazada<T> operator+(const ListaDEnlazada<T> &l) const {
        return concatena(l);
    }

};

#endif //PRÁCTICA_2_LISTADENLAZADA_H