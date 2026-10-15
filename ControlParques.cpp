/**
 * @file ControlParques.cpp
 * @brief Implementación de los métodos de la clase ControlParques.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#include "ControlParques.h"

/**
 * @brief Constructor parametrizado. Carga los datos iniciales desde los archivos CSV especificados.
 * @param ficheroEspecies Ruta del fichero CSV de especies vegetales.
 * @param ficheroParques Ruta del fichero CSV de parques botánicos.
 * @throw std::runtime_error Si no se puede abrir o cargar alguno de los dos ficheros.
 */
ControlParques::ControlParques(const std::string &ficheroEspecies, const std::string &ficheroParques) {
    LectorCSV lector;

    if (!lector.cargar(varieties, ficheroEspecies)) {
        throw std::runtime_error("Error al abrir el fichero de especies: " + ficheroEspecies);
    }

    if (!lector.cargar(parks, ficheroParques)) {
        throw std::runtime_error("Error al abrir el fichero de parques: " + ficheroParques);
    }
}

/**
 * @brief Obtiene la referencia modificable a la lista de parques.
 * @return Referencia a la lista doblemente enlazada de parques.
 */
ListaDEnlazada<Parque>& ControlParques::getParks() {
    return parks;
}

/**
 * @brief Obtiene la referencia constante a la lista de parques.
 * @return Referencia constante a la lista doblemente enlazada de parques.
 */
const ListaDEnlazada<Parque>& ControlParques::getParks() const{
    return parks;
}

/**
 * @brief Obtiene la referencia modificable al vector dinámico de especies.
 * @return Referencia al vector dinámico de especies.
 */
VDinamico<Especie>& ControlParques::getVarieties() {
    return varieties;
}

/**
 * @brief Obtiene la referencia constante al vector dinámico de especies.
 * @return Referencia constante al vector dinámico de especies.
 */
const VDinamico<Especie>& ControlParques::getVarieties() const {
    return varieties;
}

/**
 * @brief Asigna una especie a un parque insertándola en su colección interna.
 * @param esp Referencia a la especie que se desea añadir.
 * @param parq Referencia al parque en el que se incluirá la especie.
 */
void ControlParques::asignarEspecieParque(Especie &esp, Parque &parq) {
    parq.insertarEspecie(esp);
}

/**
 * @brief Recorre la lista de parques y cuenta cuántos contienen una especie por su nombre común.
 * @param ncomun Nombre común de la especie que se quiere contabilizar.
 * @return Número de parques en los que está presente dicha especie.
 */
int ControlParques::contarEspecieParque(const std::string &ncomun) const{

    int cont = 0;

    Iterador<Parque> it = parks.iterador();
    while (it.haySiguiente()) {
        if (it.dato().existeNbreCom(ncomun)) {
            cont++;
        }
        it.siguiente();
    }
    return cont;
}

/**
 * @brief Busca especies cuyo nombre científico contenga una subcadena dada.
 * @param cadena Subcadena a buscar dentro del nombre científico.
 * @return Vector dinámico con los punteros a las especies coincidentes.
 */
VDinamico<Especie*> ControlParques::listadoEspeciesSubNbre(const std::string &cadena) {
    VDinamico<Especie*> resultado;

    for (int i = 0; i < varieties.tamlogico(); ++i) {
        if (varieties[i].getNbreCientif().find(cadena) != std::string::npos) {
            resultado.insertar(&varieties[i]);
        }
    }
    return resultado;

}

/**
 * @brief Busca un parque por su nombre recorriendo la lista doblemente enlazada.
 * @param nbre_parque Nombre exacto del parque que se busca.
 * @return Referencia al parque encontrado.
 * @throw std::invalid_argument Si no se encuentra ningún parque con ese nombre.
 */
Parque& ControlParques::buscarParque(const std::string &nbreparque) {
    Iterador<Parque> it = parks.iterador();
    while (it.haySiguiente()) {
        if (it.dato().getNbreParque() == nbreparque) {
            return it.dato();
        }
        it.siguiente();
    }

    throw std::invalid_argument("NO SE ENCONTRO EL PARQUE: " + nbreparque);
}

/**
 * @brief Elimina el parque a partir de su nombre introducido por parametro.
 * @param nbre_parque Nombre exacto del parque que se va a eliminar.
 * @throw std::invalid_argument Si no se encuentra ningún parque con ese nombre.
 */
void ControlParques::eliminarParque(const std::string &nbreparque) {
    Iterador<Parque> it = parks.iterador();

    while (!it.fin()) {
        if (it.dato().getNbreParque() == nbreparque) {
            parks.borra(it);
            return;
        }
        it.avanza();
    }
    throw std::invalid_argument("NO SE ENCONTRO EL PARQUE A ELIMINAR: " + nbreparque);
}