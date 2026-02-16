cmake_minimum_required(VERSION 3.20)
project(Talot LANGUAGES CXX)

# ---------------------------------------------------------
# Global Settings
# ---------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add custom Dist configuration
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

# Static runtime on MSVC (equivalent to staticruntime "On")
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if (MSVC)
    set(ARCH_NAME ${CMAKE_VS_PLATFORM_NAME})
else()
    set(ARCH_NAME ${CMAKE_SYSTEM_PROCESSOR})
endif()

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${ARCH_NAME})

# ---------------------------------------------------------
# Talot - Static Library
# ---------------------------------------------------------

file(GLOB_RECURSE TALOT_SOURCES
    Talot/src/*.h
    Talot/src/*.cpp
)

add_library(Talot STATIC ${TALOT_SOURCES})

target_include_directories(Talot PUBLIC
    Talot/src
    Talot/vendor/eigen
)

set_target_properties(Talot PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/Talot
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/Talot
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/Talot
)

# ---------------------------------------------------------
# Sandbox - Console Application
# ---------------------------------------------------------

file(GLOB_RECURSE SANDBOX_SOURCES
    Sandbox/src/*.h
    Sandbox/src/*.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

target_include_directories(Sandbox PRIVATE
    Talot/src
    Sandbox/vendor/CLI11/include
)

target_link_libraries(Sandbox PRIVATE Talot)

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/Sandbox
)

# ---------------------------------------------------------
# Optimization Flags
# ---------------------------------------------------------

target_compile_options(Talot PRIVATE
    $<$<CONFIG:Release>:/O2>
    $<$<CONFIG:Dist>:/O2>
)

target_compile_options(Sandbox PRIVATE
    $<$<CONFIG:Release>:/O2>
    $<$<CONFIG:Dist>:/O2>
)
