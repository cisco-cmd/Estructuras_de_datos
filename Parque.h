/**
 * @file Parque.h
 * @brief Declaración de la clase Parque para la gestión de parques y especies que alberga.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#ifndef PRACTICA_2_PARQUE_H
#define PRACTICA_2_PARQUE_H

#include <string>
#include "Especie.h"
#include "VDinamico.h"

/**
 * @brief Clase que representa un parque botánico y gestiona la colección de especies que alberga.
 */
class Parque {
private:
    int cod_parque;                 /**< Código identificador único del parque. */
    std::string nbre_parque;        /**< Nombre del parque. */
    VDinamico<Especie*> especies;   /**< Vector dinámico de punteros a las especies presentes en el parque. */
public:
    Parque() = default;
    Parque(int cod, const std::string &nombre);
    ~Parque() = default;

    VDinamico<Especie*>& getContains();
    const VDinamico<Especie*>& getContains() const;

    int getCodParque() const;
    void setCodParque(int codparque);

    const std::string &getNbreParque() const;
    void setNbreParque(const std::string &nombre);

    void insertarEspecie(Especie &esp);
    bool existeNbreCom(const std::string &ncomun) const;
    bool existeNbreCie(const std::string &ncient) const;
};



#endif //PRACTICA_2_PARQUE_H
