cmake_minimum_required(VERSION 3.19)
project(TP1_POO LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(TP1_POO
    main.cpp
    elementos.h elementos.cpp
    jugador.h
    jugador.cpp
    tabladedanios.h
    matrizdanio.cpp
    partida.h
    partida.cpp



)

target_link_libraries(TP1_POO
    PRIVATE
        Qt::Core
)

install(TARGETS TP1_POO
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
