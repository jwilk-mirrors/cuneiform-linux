include_directories(h)

add_library(cuneiform ${LIBTYPE}
${SNP_SRC}
c/common.cpp 
c/debug.cpp 
c/enum.cpp
c/initdone.cpp 
c/out.cpp 
c/partlayout.cpp 
c/partrecog.cpp 
c/snp_sjtl.c 
main/mymem.cpp 
main/puma.cpp 
main/dll.cpp 
)
set_property(TARGET cuneiform PROPERTY COMPILE_DEFINITIONS __PUMA__)

target_link_libraries(cuneiform
ced
cfio
cimage
cline
cpage
rblock
rcorrkegl
rfrmt
rimage
rline
rmarker
rout
rpic
rselstr
rshelllines
rstuff
exc
rreccom
rpstr
)

library_hook(cuneiform)
