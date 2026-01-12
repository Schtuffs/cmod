cmake_minimum_required(VERSION 3.25)
project(cmod CXX)

set(CMAKE_CXX_STANDARD 23)
set(SRC ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)
set(LIB ${CMAKE_CURRENT_LIST_DIR}/lib)

add_executable(${PROJECT_NAME}
    ${SRC}/DirHandler.cpp
    ${SRC}/main.cpp
    ${SRC}/Modules.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE} ${MOD})
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
        ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

