/**
 * @file ControlParques.h
 * @brief Declaración de la clase ControlParques para la gestión de parques y especies botánicas.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#ifndef PRACTICA_2_CONTROLPARQUES_H
#define PRACTICA_2_CONTROLPARQUES_H

#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Parque.h"
#include "Especie.h"
#include "LectorCSV.h"
#include <fstream>

/**
 * @brief Clase gestora principal que coordina la carga de datos, asignación de especies y búsquedas en los parques.
 */
class ControlParques {

private:

    ListaDEnlazada <Parque> parks; /**< Lista doblemente enlazada con los parques del sistema. */
    VDinamico<Especie> varieties;  /**< Vector dinámico con la colección de especies registradas. */

public:

    ControlParques() = default;
    ControlParques(const std::string &ficheroEspecies, const std::string &ficheroParques);
    ~ControlParques() = default;

    ListaDEnlazada<Parque>& getParks();
    const ListaDEnlazada<Parque>& getParks() const;

    VDinamico<Especie>& getVarieties();
    const VDinamico<Especie>& getVarieties() const;

    void asignarEspecieParque(Especie &e, Parque &p);
    int contarEspecieParque(const std::string &ncomun) const;
    VDinamico<Especie*> listadoEspeciesSubNbre(const std::string &cadena);
    Parque& buscarParque(const std::string &nbre_parque);
    void eliminarParque(const std::string &nbreparque);

};

#endif //PRACTICA_2_CONTROLPARQUES_H
