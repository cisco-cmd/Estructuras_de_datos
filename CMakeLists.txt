cmake_minimum_required(VERSION 4.2)
project(Practica_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_executable(Practica_2 main.cpp
        ListaDEnlazada.h
        ControlParques.cpp
        ControlParques.h
        Parque.cpp
        Parque.h
        Especie.cpp
        Especie.h
        LectorCSV.h
        LectorCSV.cpp
        VDinamico.h)
