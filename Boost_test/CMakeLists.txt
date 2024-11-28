# Disattiva la ricerca automatica delle librerie
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
message(STATUS "Boost library dirs: ${BOOST_LIBRARYDIR}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

# Includi manualmente le directory degli header
include_directories("C:/Boost/include/boost-1_86")

# Collega manualmente le directory delle librerie
link_directories(${BOOST_LIBRARYDIR} "C:/filesystem/lib" "C:/test/lib")

# Configura il target
enable_testing()
add_executable (Boost_Tests_run $<TARGET_OBJECTS:sprint_lib>
        execute_all_tests.cpp
        nodeTest.cpp
        mapTest.cpp
        primitiveTest.cpp
        setupTest.cpp
        algoTest.cpp
)

# Collega manualmente le librerie richieste
target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})

# Aggiungi il test
add_test(NAME allMyTests COMMAND execute_all_tests)





