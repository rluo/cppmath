cmake_minimum_required(VERSION 3.14)
project(cppmath)

# Add the vcpkg toolchain
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find raylib via vcpkg
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)


# Collect all source files in the src directory
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

if(SRC_FILES) # Check if any source files were found
    message(STATUS "Source files: ${SRC_FILES}")
else()
    message(FATAL_ERROR "No source files found in src/")
endif()

# Generate an executable for each source file
foreach(SRC_FILE ${SRC_FILES})
    # Extract the filename without extension
    get_filename_component(EXECUTABLE_NAME ${SRC_FILE} NAME_WE)

    # Add an executable for this file
    add_executable(${EXECUTABLE_NAME} ${SRC_FILE})

    # Link raylib to this executable
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE raylib)
    if(APPLE)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" glfw)
    elseif(UNIX)
        # Linux-specific linking
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw GL X11 pthread dl)
    endif()

    # Add custom include directories if needed
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
endforeach()
