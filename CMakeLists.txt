cmake_minimum_required(VERSION 3.10)
project(TextSearchEngine)

# Use C++17 and set standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Try to detect filesystem support (for older compilers)
include(CheckCXXSourceCompiles)

# Define sources and headers
set(SOURCE_FILES
    src/main.cpp
    src/SearchCore.cpp
)

set(HEADER_FILES
    include/SearchCore.h
)

include_directories(include)
add_executable(TextSearchEngine ${SOURCE_FILES} ${HEADER_FILES})

# Handle std::filesystem compatibility
# For GCC < 9, link with stdc++fs
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_LESS 9)
        target_link_libraries(TextSearchEngine stdc++fs)
    endif()
endif()

# Copy data/ and output/ to the build directory after build
add_custom_command(TARGET TextSearchEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:TextSearchEngine>/data
)

add_custom_command(TARGET TextSearchEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    $<TARGET_FILE_DIR:TextSearchEngine>/output
)

