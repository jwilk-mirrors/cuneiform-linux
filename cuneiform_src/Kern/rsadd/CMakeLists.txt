include_directories(BEFORE src)

add_library(rsadd ${LIBTYPE} src/rsadd.c)

set_property(TARGET rsadd PROPERTY COMPILE_DEFINITIONS __RSADD__)

target_link_libraries(rsadd cstr)

library_hook(rsadd)
