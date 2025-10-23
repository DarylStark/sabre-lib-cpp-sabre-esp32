file(GLOB SOURCES CONFIGURE_DEPENDS main.cpp test_*.cpp)
add_executable(sabre_esp32_tests ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(sabre_esp32_tests PRIVATE gtest sabre_esp32 mock_esp_idf mockoc mock_mcu)

target_compile_options(sabre_esp32_tests PRIVATE --coverage)
target_link_options(sabre_esp32_tests PRIVATE --coverage)

target_include_directories(
    sabre_esp32_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        ${CMAKE_CURRENT_SOURCE_DIR}/mockoc/
        ${CMAKE_CURRENT_SOURCE_DIR}/mock_mcu/
)

include(GoogleTest)
gtest_discover_tests(sabre_esp32_tests)

add_subdirectory(mock_esp_idf)
add_subdirectory(mockoc)
add_subdirectory(mock_mcu)