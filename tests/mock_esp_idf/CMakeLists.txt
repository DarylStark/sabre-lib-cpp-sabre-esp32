file(GLOB SOURCES CONFIGURE_DEPENDS src/**/*.cpp src/*.cpp)
add_library(mock_esp_idf STATIC ${SOURCES})

target_include_directories(
    mock_esp_idf
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../mockoc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../mock_mcu/
)

target_link_libraries(mock_esp_idf PUBLIC mockoc mock_mcu)