cmake_minimum_required(VERSION 2.8.12)
project(pkphysx)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()
include(${CMAKE_BINARY_DIR}/conan.cmake)

add_compile_definitions(PX_PHYSX_STATIC_LIB)
conan_add_remote(NAME conan-center URL https://center.conan.io)
conan_cmake_run(REQUIRES
        tinyobjloader/1.0.6
        pybind11/2.4.3
        eigen/3.3.7
        physx/4.1.1
        BASIC_SETUP BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(codecov)

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
pybind11_add_module(pkphysx MODULE NO_EXTRAS src/pyphysx.cpp)
target_link_libraries(pkphysx PUBLIC ${CONAN_LIBS})
add_custom_command(TARGET pkphysx POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pkphysx> ${PHYSX_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:pkphysx>
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests ${CMAKE_BINARY_DIR}/tests
        )
add_coverage(pkphysx)

coverage_evaluate()


# Copy to source directory
# https://stackoverflow.com/questions/57464766/copy-compile-commands-json-to-project-root-folder
message("Copying compile_commands.json to ${CMAKE_SOURCE_DIR}")
add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}
    )