file(GLOB SOURCES sabre_esp32/**/*.cpp sabre_esp32/*.cpp)
add_library(sabre_esp32 SHARED ${SOURCES})

if(BUILD_TESTS STREQUAL "ON")
    target_compile_options(sabre_esp32 PRIVATE --coverage)
    target_link_options(sabre_esp32 PRIVATE --coverage)
endif()

target_include_directories(
    sabre_esp32
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

