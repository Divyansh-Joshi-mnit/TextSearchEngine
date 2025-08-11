cmake_minimum_required(VERSION 3.10)
project(TextSearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    src/main.cpp
    src/SearchCore.cpp
)

include_directories(include)
add_executable(TextSearchEngine ${SOURCE_FILES})

add_custom_command(TARGET TextSearchEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:TextSearchEngine>/data
)

add_custom_command(TARGET TextSearchEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    $<TARGET_FILE_DIR:TextSearchEngine>/output
)


