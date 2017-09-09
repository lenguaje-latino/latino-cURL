################################################################################
# Para mas información de este archivo visite la pagina de cmake:
# https://cmake.org/documentation/
################################################################################

#Establece la versión mínima requerida de cmake para un proyecto.
cmake_minimum_required(VERSION 3.0.2)

#Establece un nombre para el proyecto
project (latino-curl)

#Agrega un subdirectorio a la compilación.
add_subdirectory(curl)

#Añade directorios de inclusión a la compilación
include_directories(curl/include)
include_directories(curl/src)
include_directories(include)

#Agrega una biblioteca al proyecto utilizando los
#archivos de origen especificados.
add_library(latino-curl SHARED src/latino-curl.c)

#Vincula un objetivo a bibliotecas determinadas.
target_link_libraries(latino-curl curl latino)

#Especifica las reglas que se ejecutarán en el momento de la instalación.
install(FILES liblatino-curl.so DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
