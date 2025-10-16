file(GLOB SOURCES src/**/*.c src/*.c)
add_library(mock_esp_idf SHARED ${SOURCES})

target_include_directories(
    mock_esp_idf
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
