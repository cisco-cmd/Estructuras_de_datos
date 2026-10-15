#include <iostream>
#include <conio.h>
#include <string>

#include "ControlParques.h"
#include "LectorCSV.h"
#include "ListaDEnlazada.h"
#include "Parque.h"
#include "windows.h"

using namespace std;

template <class T>
void mostrarLista(ListaDEnlazada<T> l)
{
    for (Iterador<T> it = l.iterador(); !it.fin(); it.avanza())
    {
        std::cout << std::to_string(it.getdato()) << "  ";
    }
    std::cout << std::endl;
}


Iterador<Parque> buscaParque(ListaDEnlazada<Parque>& lista, string nombre)
{
    Iterador<Parque> it = lista.iterador();
    for (it; !it.fin(); it.avanza())
    {
        if (it.getdato().getNbreParque() == nombre)
        {
            return it;
        }
    }
    return it;
}

bool buscaEspecieNbrComun(VDinamico<Especie*>& vector, string nombreComun)
{
    int n = vector.gettLogico();
    for (int i = 0; i < n; ++i)
    {
        if (vector[i]->getNbreComun() == nombreComun)
        {
            return true;
        }
    }
    return false;
}

bool buscaEspecieNbrCientif(VDinamico<Especie*>& vector, string nombreCentif)
{
    int n = vector.gettLogico();
    for (int i = 0; i < n; ++i)
    {
        string s = vector[i]->getNbreCientif();
        if (vector[i]->getNbreCientif() == nombreCentif)
        {
            return true;
        }
    }
    return false;
}

const std::string RUTA_ESPECIES = "data/arbolado-especies.csv";
const std::string RUTA_PARQUES = "data/parques.csv";

int main()
{

    SetConsoleOutputCP(65001);

    cout << "PROGRAMA DE PRUEBA 1" << endl;

    //Crear la lista vacía
    ListaDEnlazada<int> lista;

    cout<<"Insetar al final del 101 al 200"<<endl;

    for (int i = 101; i <= 200; ++i)
    {
        lista.insertaFin(i);
    }
    mostrarLista(lista);

    cout<<endl<<"Insertar por el comienzo del 1 al 98"<<endl;
    for (int i = 98; i >= 1; --i)
    {
        lista.insertaInicio(i);
    }
    mostrarLista(lista);

    cout<<endl<<"insertar el dato 100 delante del 101"<<endl;
    Iterador<int> itint = lista.iterador();
    while (itint.getdato() != 102)
    {
        itint.avanza();
    }
    lista.inserta(itint, 100);
    mostrarLista(lista);

    itint = lista.iterador();
    while (itint.getdato() != 98)
    {
        itint.avanza();
    }
    lista.inserta(itint, 99);
    mostrarLista(lista);

    cout<<endl<<"Borrar los 10 primeros y los 10 últimos"<<endl;
    for (int i = 0; i < 10; ++i)
    {
        lista.borraInicio();
        lista.borraFinal();
    }
    mostrarLista(lista);

    cout<<endl<<"PULSAR CUALQUIER TECLA PARA CONTINUAR"<<endl;
    getch();

    cout << "PROGRAMA DE PRUEBA 2" << endl;
    ControlParques cp(RUTA_ESPECIES, RUTA_PARQUES);

    //Variables fuera del bucle por eficiencia
    VDinamico<Especie>* especies = &cp.getVarieties();
    ListaDEnlazada<Parque> *parques = &cp.getParks();

    for (int i = 0; i < especies->gettLogico(); ++i)
    {
        Iterador<Parque> it = parques->iterador();
        Especie& esp = (*especies)[i];
        TipoPlanta tipo = esp.getTipoPlanta();
        for (it; !it.fin(); it.avanza())
        {
            Parque& pq = it.getdato();
            int resto = pq.getCodParque() % 2;

            //parques con codigo par
            if ((tipo == TipoPlanta::ARBUSTO || tipo == TipoPlanta::CONIFERA || tipo == TipoPlanta::PALMACEA ||
                tipo == TipoPlanta::HERB_PERENNES || tipo == TipoPlanta::FRONDOSA) && (resto == 0))
            {
                pq.insertarEspecie(esp);
                //Parques con codigo impar
            }
            else if ((tipo == TipoPlanta::TAPIZANTE_TREPADORA || tipo == TipoPlanta::CACTACEA_SUCULENTA ||
                tipo == TipoPlanta::SUBTROPICAL_TROPICAL ||
                tipo == TipoPlanta::HERB_ANUAL || tipo == TipoPlanta::HERB_ANUALES) && (resto == 1))
            {
                pq.insertarEspecie(esp);
            }
        }
    }

    cout << endl << "ASIGNACIÓN DE ESPECIES A LOS PARQUES" << endl;
    for (Iterador<Parque> it = parques->iterador(); !it.fin(); it.avanza())
    {
        cout << "  Codigo: " << to_string(it.getdato().getCodParque()) << " nombre: " << it.getdato().
            getNbreParque() << " total especies: " << to_string(
                it.getdato().getContains().gettLogico()) << endl;
    }


    cout << endl << "BUSCAR EN PARQUE PRINCESA LEONOR LOS NOMBRES COMUNES EUCALIPTO ROJO Y ARCE DE SIERRA" << endl;
    Parque& princLeonor = buscaParque(cp.getParks(), "PARQUE PRINCESA LEONOR").getdato();
    //Debe estar
    if (buscaEspecieNbrComun(princLeonor.getContains(), "Eucalipto rojo"))
    {
        cout << "  Encontrado Eucalipto rojo" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Eucalipto rojo" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(princLeonor.getContains(), "Arce de sierra"))
    {
        cout << "  Encontrado Arce de sierra" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Arce de sierra" << endl;
    }

    cout << endl << "BUSCAR EN PARQUE MADRID RIO LOS NOMBRES CIENTÍFICOS HEBE FLORIBUNDA Y ANANAS COMOSA" << endl;
    Parque& madridRio = buscaParque(cp.getParks(), "PARQUE MADRID RIO").getdato();
    //No debe estar
    if (buscaEspecieNbrCientif(madridRio.getContains(), "Hebe floribunda"))
    {
        cout << "  Encontrado Hebe floribunda" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Hebe floribunda" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(madridRio.getContains(), "Ananas comosa"))
    {
        cout << "  Encontrado Ananas comosa" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Ananas comosa" << endl;
    }

    cout << endl << "BUSCAR PARQUES JUAN CARLOS III Y VIVERO DE MIGAS CALIENTES" << endl;
    //No debe estar
    Iterador<Parque> it = buscaParque(cp.getParks(), "JUAN CARLOS III");
    if (it.fin())
    {
        cout << "  No se ha encontrado parque JUAN CARLOS III" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.getdato().getCodParque()) <<" nombre: "<< it.getdato().getNbreParque()<< endl;
    }

    Iterador<Parque> it2 = buscaParque(cp.getParks(), "VIVERO DE MIGAS CALIENTES");
    //Sí debe estar
    if (it2.fin())
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it2.getdato().getCodParque()) <<" nombre: "<< it2.getdato().getNbreParque()<< endl;
    }

    cout<< endl<<"BUSCAR ESPECIES CON LA SUBCADENA ROSA EN SU NOMBRE CIENTÍFICO"<<endl;
    for (int i =0; i < especies->gettLogico(); ++i)
    {
        string ncientif = (*especies)[i].getNbreCientif();
        if (ncientif.find("rosa") != string::npos)
        {
            (*especies)[i].mostrarInfo();
        }
    }

    cout<< endl<<"CONTAR CUÁNTOS PARQUES TIENEN LA ESPECIE CON NOMBRE COMÚN ABETO"<<endl;
    it = cp.getParks().iterador();
    int total = 0;
    for (it; !it.fin(); it.avanza())
    {
       VDinamico<Especie*>  esp = it.getdato().getContains();
        for (int i =0; i < esp.gettLogico(); ++i)
        {
            string nombreComun = esp[i]->getNbreComun();
            if (nombreComun.find("Abeto") != string::npos)
            {
                ++total;
                break;
            }
        }
    }
    cout<<"  Total: "<<total<<endl;

    cout << endl << "ELIMINAR PARQUE 'VIVERO DE MIGAS CALIENTES'" << endl;

    try {
        cp.eliminarParque("VIVERO DE MIGAS CALIENTES");
        cout << endl << "PARQUE ELIMINADO." << endl;
    } catch (const std::invalid_argument &e) {
        cout << e.what() << endl;
    }

    cout << endl << "COMPROBAR QUE YA NO EXISTE" << endl;
    try {
        Parque& p = cp.buscarParque("VIVERO DE MIGAS CALIENTES");
        cout << " EL PARQUE AUN EXISTE: " << p.getNbreParque() << endl;
    } catch (const std::invalid_argument &e) {
        cout << e.what() << endl;
    }

}