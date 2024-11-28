cmake_minimum_required(VERSION 3.27)

project(sprint)

set(CMAKE_CXX_STANDARD 17)

# Aggiungi il percorso per nlohmann JSON
include_directories("C:/Sprint-master/json-develop/include")

# Configurazione Boost
set(Boost_USE_STATIC_LIBS OFF)

# Specifica manualmente i percorsi degli header e delle librerie
set(BOOST_INCLUDEDIR "C:/Boost/include/boost-1_86")  # Header principali
set(Boost_INCLUDE_DIRS "C:/Boost/include/boost-1_86") # Aggiunto per compatibilità
set(Boost_LIBRARIES
        "C:/filesystem/lib/libboost_filesystem-vc143-mt-x64-1_86.lib"
        "C:/test/lib/libboost_unit_test_framework-vc143-mt-x64-1_86.lib"
)

# Debug per verificare percorsi
message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

# Includi manualmente le directory degli header
include_directories(${Boost_INCLUDE_DIRS})

# Collega manualmente le directory delle librerie
link_directories("C:/filesystem/lib" "C:/test/lib")

set(
        COMMON_SOURCES
        src/map.cpp
        src/map_objects.cpp
        include/setup.h
        include/primitives.h
        src/primitives.cpp
        src/setup.cpp
        src/algorithms_utilities.cpp
        include/algorithms_utilities.h
        src/heuristics.cpp
        include/algorithms.h
        src/algorithms.cpp
        include/hash_functions.h
)

set(
        TESTS_SOURCES
        tests/nodeCreationTest.cpp
)

add_executable(sprint
        src/main.cpp
        include/map.h
        include/control_levels.h
        include/map_objects.h
)


add_subdirectory(Boost_test)

add_library(sprint_lib OBJECT ${COMMON_SOURCES})

target_link_libraries(sprint PRIVATE sprint_lib ${Boost_LIBRARIES})

