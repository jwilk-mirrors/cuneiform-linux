include_directories(BEFORE sources/main)

add_library(cimage ${LIBTYPE}
${SNP_SRC}
sources/main/cticontrol.cpp
sources/main/ctiimage.cpp
#sources/main/ctiimage.RC
sources/main/ctiimageheader.cpp
sources/main/ctiimagelist.cpp
sources/main/ctimask.cpp
sources/main/ctimaskline.cpp
sources/main/ctimasklinesegment.cpp
sources/main/ctimemory.cpp
sources/main/dll.cpp
)

set_property(TARGET cimage PROPERTY COMPILE_DEFINITIONS __CIMAGE__)

target_link_libraries(cimage cfio rdib)

library_hook(cimage)
