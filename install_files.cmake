
set(RELATIVE_DATADIR "share/cuneiform")
set(INSTALL_DATADIR "${CMAKE_INSTALL_PREFIX}/${RELATIVE_DATADIR}")

include(CheckTypeSize)
check_type_size("void*" PTRSIZE)
if(PTRSIZE EQUAL 8 AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LIBDIR "lib64")
else()
    set(LIBDIR "lib")
endif()

# Library versioning done as instructed in
# http://techbase.kde.org/index.php?title=Development/Tutorials/Creating_Libraries

macro(library_hook name)
  set_target_properties(${name} PROPERTIES VERSION ${CF_VERSION} SOVERSION ${ABI_VERSION})
  install(
    TARGETS "${name}"
    ARCHIVE DESTINATION ${LIBDIR}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIBDIR}
  )
endmacro()

macro(install_exe name)
  install(
    TARGETS "${name}"
    RUNTIME DESTINATION bin
  )
endmacro()
