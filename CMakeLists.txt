cmake_minimum_required(VERSION 2.8)

project (latino-curl)

add_subdirectory(curl)
include_directories(curl/include)
include_directories(curl/src)
include_directories(include)

add_library(latino-curl SHARED src/latino-curl.c)

link_libraries(curl latino)

target_link_libraries(latino-curl curl latino)
#optional install in /usr/local/lib
install(FILES liblatino-curl.so DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
