file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(mockoc STATIC ${SOURCES})