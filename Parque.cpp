/**
 * @file Parque.cpp
 * @brief Implementación de la clase Parque para la gestión de parques y especies que alberga.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#include "Parque.h"

/**
 * @brief Constructor parametrizado de Parque.
 * @param cod Código identificador del parque.
 * @param nombre Nombre asignado al parque.
 */
Parque::Parque(int cod, const std::string &nombre): cod_parque(cod), nbre_parque(nombre) {}

/**
 * @brief Obtiene una referencia modificable al vector dinámico de punteros a especies.
 * @return Referencia a VDinamico de punteros a Especie.
 */
VDinamico<Especie*>& Parque::getContains() {
    return especies;
}

/**
 * @brief Obtiene una referencia constante al vector dinámico de punteros a especies.
 * @return Referencia constante a VDinamico de punteros a Especie.
 */
const VDinamico<Especie*>& Parque::getContains() const {
    return especies;
}

/**
 * @brief Obtiene el código identificador del parque.
 * @return Código numérico del parque.
 */
int Parque::getCodParque() const {
    return cod_parque;
}

/**
 * @brief Establece el código identificador del parque.
 * @param codparque Nuevo código numérico.
 */
void Parque::setCodParque(int codparque) {
    cod_parque = codparque;
}

/**
 * @brief Obtiene el nombre del parque.
 * @return Cadena de texto con el nombre.
 */
const std::string &Parque::getNbreParque() const {
    return nbre_parque;
}

/**
 * @brief Establece el nombre del parque.
 * @param nombre Cadena de texto con el nuevo nombre.
 */
void Parque::setNbreParque(const std::string &nombre) {
    nbre_parque = nombre;
}

/**
 * @brief Inserta el puntero de una especie en el vector de especies del parque.
 * @param esp Referencia a la especie a almacenar.
 */
void Parque::insertarEspecie(Especie &esp) {
    especies.insertar(&esp);
}

/**
 * @brief Verifica si en el parque habita alguna especie que contenga el nombre común especificado.
 * @param ncomun Nombre común o subcadena de búsqueda.
 * @return true si se encuentra al menos una coincidencia, false en caso contrario.
 * @throw std::invalid_argument Si el nombre ingresado es una cadena vacía.
 */
bool Parque::existeNbreCom(const std::string &ncomun) const {
    if (ncomun.empty()) throw std::invalid_argument("El nombre no puede ser vacio.");

    for (int i = 0; i < especies.tamlogico(); ++i) {
        if (especies[i]->getNbreComun().find(ncomun) != std::string::npos) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica si en el parque habita alguna especie que contenga el nombre científico especificado.
 * @param ncient Nombre científico o subcadena de búsqueda.
 * @return true si se encuentra al menos una coincidencia, false en caso contrario.
 * @throw std::invalid_argument Si el nombre ingresado es una cadena vacía.
 */
bool Parque::existeNbreCie(const std::string &ncient) const {
    if (ncient == "") throw std::invalid_argument("El nombre no puede ser vacio.");
    for (int i = 0; i < especies.tamlogico(); ++i) {
        if (especies[i]->getNbreCientif() == ncient || especies[i]->getNbreCientif().find(ncient) != std::string::npos) {
            return true;
        }
    }
    return false;
}