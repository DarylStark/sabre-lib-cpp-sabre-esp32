file(GLOB SOURCES src/**/*.cpp src/*.cpp)
add_library(mock_esp_idf SHARED ${SOURCES})

target_include_directories(
    mock_esp_idf
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../mockoc/
)

target_link_libraries(mock_esp_idf PRIVATE mockoc)