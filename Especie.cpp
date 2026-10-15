/**
 * @file Especie.cpp
 * @brief Implementación de la clase Especie y utilidades del enumerado TipoPlanta.
 * @author Juan Carlos Navidad García
 * @date 08/10/2026
 */

#include "Especie.h"

/**
 * @brief Constructor por defecto. Inicializa los miembros con valores vacíos o por defecto.
 */
Especie::Especie(): cod_especie(""), nbre_comun(""), nbre_cientif(""), tipo_planta(TipoPlanta::HIERBA) {}

/**
 * @brief Constructor parametrizado de Especie.
 * @param cod Código identificador de la Especie.
 * @param nbrecomun Nombre común de la Especie.
 * @param nbrecien Nombre cientifico de la Especie.
 * @param tipoplanta Enum de tipo TipoPlanta para seleccionar el tipo de Especie.
 */
Especie::Especie(std::string &cod, std::string &nbrecomun, std::string &nbrecien, TipoPlanta tipoplanta):cod_especie(cod),nbre_comun(nbrecomun), nbre_cientif(nbrecien), tipo_planta(tipoplanta) {};

/**
 * @brief Obtiene el código identificador de la especie.
 * @return Referencia constante a la cadena con el código.
 */
const std::string& Especie::getCodEspecie() const {
    return cod_especie;
}

/**
 * @brief Obtiene el nombre común de la especie.
 * @return Referencia constante a la cadena con el nombre común.
 */
const std::string& Especie::getNbreComun() const {
    return nbre_comun;
}

/**
 * @brief Obtiene el nombre científico de la especie.
 * @return Referencia constante a la cadena con el nombre científico.
 */
const std::string& Especie::getNbreCientif() const {
    return nbre_cientif;
}

/**
 * @brief Obtiene el tipo de planta de la especie.
 * @return Valor del enumerado TipoPlanta.
 */
TipoPlanta Especie::getTipoPlanta() const {
    return tipo_planta;
}

/**
 * @brief Establece el código identificador de la especie.
 * @param cod Cadena con el nuevo código.
 */
void Especie::setCodEspecie(const std::string &cod) {
    cod_especie = cod;
}

/**
 * @brief Establece el nombre común de la especie.
 * @param nbrecomun Cadena con el nuevo nombre común.
 */
void Especie::setNbreComun(const std::string &nbrecomun) {
    nbre_comun = nbrecomun;
}

/**
 * @brief Establece el nombre científico de la especie.
 * @param nbrecien Cadena con el nuevo nombre científico.
 */
void Especie::setNbreCientif(const std::string &nbrecien) {
    nbre_cientif = nbrecien;
}

/**
 * @brief Establece el tipo de planta de la especie.
 * @param tipo Valor de TipoPlanta.
 */
void Especie::setTipoPlanta(TipoPlanta tipo) {
    tipo_planta = tipo;
}

/**
 * @brief Arreglo de cadenas de caracteres para mapear representaciones textuales de TipoPlanta.
 */
const char* const NOMBRES_TIPO[] = {
    "HIERBA", "ARBUSTO", "ARBOL", "MATA", "CONIFERA", "PALMACEA",
    "HERB_PERENNES", "FRONDOSA", "TAPIZANTE_TREPADORA",
    "CACTACEA_SUCULENTA", "SUBTROPICAL_TROPICAL", "HERB_ANUAL", "HERB_ANUALES"
};

/**
 * @brief Convierte una cadena de texto al correspondiente valor del enum TipoPlanta (Hecho con IA puesto que no encontraba la forma de que me cuadrase con LectorCSV).
 * @param str Cadena con el texto descriptivo del tipo.
 * @return Valor del enum TipoPlanta (o TipoPlanta::HIERBA si no se encuentra coincidencia).
 */
TipoPlanta Especie::stringToTipo(const std::string& str) {
    for (int i = 0; i < 13; ++i) {
        if (str == NOMBRES_TIPO[i]) return static_cast<TipoPlanta>(i);
    }
    return TipoPlanta::HIERBA;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo para TipoPlanta (Hecho con IA puesto que no encontraba la forma de que me cuadrase con LectorCSV).
 * @param os Flujo de salida ostream.
 * @param tp Valor del enum TipoPlanta.
 * @return Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const TipoPlanta& tp) {
    static const std::string NOMBRES_TIPO[] = {
        "HIERBA", "ARBUSTO", "ARBOL", "MATA", "CONIFERA", "PALMACEA",
        "HERB_PERENNES", "FRONDOSA", "TAPIZANTE_TREPADORA",
        "CACTACEA_SUCULENTA", "SUBTROPICAL_TROPICAL", "HERB_ANUAL", "HERB_ANUALES"
    };
    return os << NOMBRES_TIPO[static_cast<int>(tp)];
}

/**
 * @brief Imprime en la consola la información formateada de la especie.
 */
void Especie::mostrarInfo() const {
    std::cout << "Especie [" << cod_especie << "]: "
              << nbre_comun << " (" << nbre_cientif << ") - Tipo: ";

    switch (tipo_planta) {
        case TipoPlanta::ARBUSTO:               std::cout << "Arbusto"; break;
        case TipoPlanta::CONIFERA:              std::cout << "Conífera"; break;
        case TipoPlanta::PALMACEA:              std::cout << "Palmácea"; break;
        case TipoPlanta::HERB_PERENNES:         std::cout << "Herbácea Perenne"; break;
        case TipoPlanta::FRONDOSA:              std::cout << "Frondosa"; break;
        case TipoPlanta::TAPIZANTE_TREPADORA:   std::cout << "Tapizante / Trepadora"; break;
        case TipoPlanta::CACTACEA_SUCULENTA:    std::cout << "Cactácea / Suculenta"; break;
        case TipoPlanta::SUBTROPICAL_TROPICAL:  std::cout << "Subtropical / Tropical"; break;
        case TipoPlanta::HERB_ANUAL:
        case TipoPlanta::HERB_ANUALES:          std::cout << "Herbácea Anual"; break;
        default:                                std::cout << "Mata / Hierba"; break;
    }
    std::cout << std::endl;
}
