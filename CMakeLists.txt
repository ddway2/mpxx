cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SAMPLE OFF)

project(MPXX)

# check for demangling support
try_compile(DEMANGLER_FOUND
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/check_demangle.cpp
)

add_library(mpxx
    sources/libraries/mpxx/mpxx/utils.cpp
)

if(DEMANGLER_FOUND)
    target_compile_definitions(mpxx
        PRIVATE MPXX_HAVE_DEMANGLER
    )
endif()

target_include_directories(mpxx
    PUBLIC sources/include/mpxx
    PUBLIC generated
)

if(BUILD_SAMPLE)
    add_executable(mstruct_example
        samples/mstruct_example.cpp
    )

    target_link_libraries(mstruct_example
        PRIVATE mpxx
    )
endif()

