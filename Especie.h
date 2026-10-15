/**
 * @file Especie.h
 * @brief Declaración de la clase Especie y el enumerado TipoPlanta.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#ifndef PRACTICA_2_ESPECIE_H
#define PRACTICA_2_ESPECIE_H

#include <string>
#include <iostream>

/**
 * @enum TipoPlanta
 * @brief Categorías y tipos de clasificación para las plantas.
 */
enum class TipoPlanta {
    HIERBA,
    ARBUSTO,
    ARBOL,
    MATA,
    CONIFERA,
    PALMACEA,
    HERB_PERENNES,
    FRONDOSA,
    TAPIZANTE_TREPADORA,
    CACTACEA_SUCULENTA,
    SUBTROPICAL_TROPICAL,
    HERB_ANUAL,
    HERB_ANUALES
};

/**
 * @brief Sobrecarga del operador << para la impresión del tipo de planta en flujo de salida (Hecho con IA puesto que no encontraba la forma de que me cuadrase con LectorCSV).
 * @param os Flujo de salida ostream.
 * @param tp TipoPlanta a imprimir.
 * @return Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const TipoPlanta& tp);

/**
 * @brief Clase que representa una especie vegetal botánica con sus nombres y clasificación.
 */
class Especie {
private:

    std::string cod_especie;   /**< Código único identificador de la especie. */
    std::string nbre_comun;    /**< Nombre común de la especie. */
    std::string nbre_cientif;  /**< Nombre científico de la especie. */
    TipoPlanta tipo_planta;    /**< Tipo de planta al que pertenece la especie. */

public:

    Especie();
    Especie(std::string &cod, std::string &nbrecomun, std::string &nbrecien, TipoPlanta tipoplanta);
    ~Especie() = default;

    const std::string& getCodEspecie() const;
    const std::string& getNbreComun() const;
    const std::string& getNbreCientif() const;
    TipoPlanta getTipoPlanta() const;

    void setCodEspecie(const std::string &cod);
    void setNbreComun(const std::string &nbrecomun);
    void setNbreCientif(const std::string &nbrecien);
    void setTipoPlanta(TipoPlanta tipo);
    static TipoPlanta stringToTipo(const std::string& str);

    void mostrarInfo() const;

};

#endif //PRACTICA_2_ESPECIE_H
