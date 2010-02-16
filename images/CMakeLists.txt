set(test_script ${CMAKE_CURRENT_SOURCE_DIR}/test_output.sh)

macro(output_test testname imagefile)
    add_test(${testname} ${test_script} ${CMAKE_CURRENT_SOURCE_DIR}/${imagefile} ${ARGN})
endmacro()

output_test(BasicTest phototest.tif --singlecolumn)
