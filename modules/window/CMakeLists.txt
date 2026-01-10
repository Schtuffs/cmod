add_library(Window STATIC IMPORTED GLOBAL)

set_target_properties(Window PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libWindow.a
    LINKER_LANGUAGE CXX
)

target_include_directories(Window
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}
)

find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Window INTERFACE glfw)
