/**
 * @file vdinamico.h
 * @brief Declaración e implementación de la plantilla de clase VDinamico.
 * @author Juan Carlos Navidad García
 * @date 18/09/2026
 */

#ifndef PRACTICA_1_VDINAMICO_H
#define PRACTICA_1_VDINAMICO_H

#include <stdexcept>
#include <climits>
#include <algorithm>

/**
 * @class VDinamico
 * @brief Plantilla de clase que implementa un vector dinámico de capacidad auto-ajustable.
 * @tparam T Tipo de los elementos almacenados en el vector.
 */
template <typename T>
class VDinamico {
private:
    unsigned int tamlog; ///< Tamaño lógico (número de elementos realmente almacenados)
    unsigned int tamfis; ///< Tamaño físico (capacidad de memoria reservada)
    T *v;                ///< Puntero al bloque de memoria donde se guardan los elementos

    /**
     * @brief Calcula e inicializa el tamaño físico (tamfis) a la potencia de 2 superior o igual al tamaño lógico indicado.
     * @param logico Cantidad mínima de elementos a albergar.
     * @post El atributo tamfis se ajusta al valor adecuado en potencias de 2.
     */
    void potencia2(unsigned int logico) {
        tamfis = 1;
        while (tamfis < logico) tamfis *= 2;
    }

public:
    /**
     * @brief Constructor por defecto.
     * @post Crea un vector vacío con tamaño lógico 0 y tamaño físico inicial de 1.
     */
    VDinamico() : tamlog(0), tamfis(1) {
        v = new T[tamfis];
    }

    /**
     * @brief Constructor parametrizado para rellenar con un valor por defecto.
     * @param tamlogico Cantidad de elementos a inicializar.
     * @param dato Referencia al elemento con el que se poblará el vector.
     * @post Reserva memoria ajustada a potencia de 2 y copia 'dato' en cada posición.
     */
    VDinamico(unsigned int tamlogico, T &dato) : tamlog(tamlogico) {
        potencia2(tamlogico);
        v = new T[tamfis];
        for (unsigned int i = 0; i < tamlog; ++i) v[i] = dato;
    }

    /**
     * @brief Constructor de copia.
     * @param orig Instancia de VDinamico que se desea duplicar.
     * @post Genera una copia exacta en memoria independiente de los datos del vector original.
     */
    VDinamico(const VDinamico<T> &orig) : tamlog(orig.tamlog), tamfis(orig.tamfis) {
        v = new T[tamfis];
        for (unsigned int i = 0; i < tamlog; ++i) v[i] = orig.v[i];
    }

    /**
     * @brief Constructor de copia parcial desde una posición dada.
     * @param orig Vector de origen.
     * @param posicionInicial Índice a partir del cual comenzar la copia.
     * @param numElementos Cantidad de elementos a copiar.
     * @throws std::out_of_range Si la suma de posicionInicial y numElementos supera el tamaño lógico del origen.
     */
    VDinamico(const VDinamico<T> &orig, unsigned int posicionInicial, unsigned int numElementos) {
        if (posicionInicial + numElementos > orig.tamlog) throw std::out_of_range("Rango fuera del limite.");

        tamlog = numElementos;
        potencia2(tamlog);

        v = new T[tamfis];
        for (unsigned int i = 0; i < tamlog; ++i) v[i] = orig.v[posicionInicial + i];
    }

    /**
     * @brief Operador de asignación.
     * @param orig Vector origen a asignar.
     * @return Referencia al propio objeto (*this).
     * @post Libera la memoria previa y realiza una copia profunda del vector 'orig'.
     */
    VDinamico<T> &operator=(const VDinamico<T> &orig) {
        if (&orig != this) {
            delete[] v;
            tamlog = orig.tamlog;
            tamfis = orig.tamfis;
            v = new T[tamfis];
            for (unsigned int i = 0; i < tamlog; ++i) v[i] = orig.v[i];
        }

        return *this;
    }

    /**
     * @brief Operador de acceso no constante por índice.
     * @param posicion Índice del elemento al que se quiere acceder.
     * @return T& Referencia modificable al elemento en la posición solicitada.
     * @throws std::out_of_range Si la posición es mayor o igual que el tamaño lógico.
     */
    T &operator[](unsigned int posicion) {
        if (posicion >= tamlog) throw std::out_of_range("Posicion incorrecta.");
        return v[posicion];
    }

    /**
     * @brief Operador de acceso constante por índice.
     * @param posicion Índice del elemento al que se quiere acceder.
     * @return const T& Referencia constante (solo lectura) al elemento solicitado.
     * @throws std::out_of_range Si la posición es mayor o igual que el tamaño lógico.
     */
    const T &operator[](unsigned int posicion) const {
        if (posicion >= tamlog) throw std::out_of_range("Posicion incorrecta.");
        return v[posicion];
    }

    /**
     * @brief Inserta un elemento en la posición indicada (por defecto al final).
     * @param dato Elemento que se desea insertar.
     * @param pos Posición donde insertar el dato (por defecto UINT_MAX para insertar al final).
     * @throws std::out_of_range Si la posición introducida es superior al tamaño lógico actual.
     * @post Si el tamaño lógico alcanza al físico, la capacidad del vector se duplica.
     */
    void insertar(const T& dato, unsigned int pos = UINT_MAX) {
        if (pos == UINT_MAX) pos = tamlog;

        if (pos > tamlog) throw std::out_of_range("Posicion incorrecta.");

        if (tamlog == tamfis) {
            tamfis *= 2;
            T *vaux = new T[tamfis];
            for (unsigned int i = 0; i < tamlog; ++i) vaux[i] = v[i];
            delete[] v;
            v = vaux;
        }

        for (unsigned int i = tamlog; i > pos; --i) v[i] = v[i - 1];

        v[pos] = dato;

        tamlog++;
    }

    /**
     * @brief Elimina un elemento del vector en la posición especificada.
     * @param pos Posición del elemento a borrar (por defecto UINT_MAX para borrar el último).
     * @return T Copia del elemento borrado.
     * @throws std::out_of_range Si el vector está vacío o la posición es inválida.
     * @post Desplaza los elementos a la izquierda y decrementa el tamaño lógico.
     */
    T borrar(unsigned int pos = UINT_MAX) {
        if (tamlog == 0) throw std::out_of_range("El vector esta vacio.");

        if (pos == UINT_MAX) pos = tamlog - 1;

        if (pos >= tamlog) throw std::out_of_range("Posicion invalida.");

        T elementoBorrado = v[pos];

        for (unsigned int i = pos; i < tamlog - 1; ++i) v[i] = v[i + 1];

        --tamlog;

        //Fallo en la defensa anterior (olvidarme de reducir el tamaño físico), utilizar un umbral de 1/3 en lugar de 1/2 para garantizar que el coste promedio por operación (tiempo amortizado) siga siendo de orden constante O(1) en vez de O(N)

        if (tamlog < tamfis / 3 && tamfis > 1) {
            tamfis /= 2;
            T *vNuevo = new T[tamfis];
            for (unsigned int i = 0; i < tamlog; ++i) {
                vNuevo[i] = v[i];
            }
            delete[] v;
            v = vNuevo;
        }

        return elementoBorrado;
    }

    /**
     * @brief Ordena los elementos del vector en orden ascendente mediante std::sort.
     * @note Requiere que el tipo T tenga implementado el operador <.
     */
    void ordenar() {
        std::sort(v, v + tamlog);
    }

    /**
     * @brief Realiza una búsqueda binaria/dicotómica sobre el vector.
     * @param dato Elemento a buscar.
     * @return int Índice del elemento si es encontrado; -1 en caso de no existir.
     * @note Presupone que el vector se encuentra previamente ordenado y que T implementa los operadores == y <.
     */
    int busquedaDicotomica(const T& dato) const {
        int inf = 0;
        int sup = tamlog - 1;
        int curIn;

        while (inf <= sup) {
            curIn = (inf + sup) / 2;
            if (v[curIn] == dato) return curIn;
            else if (v[curIn] < dato) inf = curIn + 1;
            else sup = curIn - 1;
        }
        return -1;
    }

    /**
     * @brief Devuelve el tamaño lógico actual del vector.
     * @return unsigned int Número de elementos almacenados.
     */
    unsigned int gettLogico() const {
        return tamlog;
    }

    /**
     * @brief Devuelve el tamaño lógico actual del vector (alias).
     * @return unsigned int Número de elementos almacenados.
     */
    unsigned int tamlogico() const {
        return tamlog;
    }

    /**
     * @brief Destructor de la clase VDinamico.
     * @post Libera la memoria dinámica reservada para el vector interno.
     */
    virtual ~VDinamico() {
        delete[] v;
    }
};

#endif //PRACTICA_1_VDINAMICO_H