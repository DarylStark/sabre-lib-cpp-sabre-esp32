file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(mock_mcu STATIC ${SOURCES})