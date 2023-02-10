file(GLOB LIBRARY_SOURCES "./*.cpp")
file(GLOB LIBRARY_HEADERS "./*.h")

add_library(next_win32 STATIC 
  ${LIBRARY_SOURCES}
  ${LIBRARY_HEADERS}
)