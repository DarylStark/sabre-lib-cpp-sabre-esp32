file(GLOB SOURCES sabre_esp32/**/*.cpp sabre_esp32/*.cpp)
add_library(sabre_esp32 SHARED ${SOURCES})

set(BUILD_TESTS OFF CACHE BOOL "Disable tests" FORCE)
include(FetchContent)
FetchContent_Declare(
    sabre
    URL https://github.com/DarylStark/sabre-lib-cpp-sabre/archive/refs/heads/dev.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(sabre)

target_link_libraries(sabre_esp32 PUBLIC sabre)

if(BUILD_TESTS STREQUAL "ON")
    target_compile_options(sabre_esp32 PRIVATE --coverage)
    target_link_options(sabre_esp32 PRIVATE --coverage)
endif()

target_include_directories(
    sabre_esp32
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${sabre_SOURCE_DIR}/src
)
