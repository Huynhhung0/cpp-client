
cmake_minimum_required(VERSION 3.2)

project(ark_cpp_client)

# ------------------------------------------------------------------------------
# Set the Environment Variables
# ------------------------------------------------------------------------------

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(EXTERNAL_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/extern)

set(BUILD_SHARED_LIBS OFF)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS
                    -D_SCL_SECURE_NO_WARNINGS
                    -DNOMINMAX)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
endif()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Coverage 1:2
# ------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    add_definitions(-Wno-unused-command-line-argument)
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Clang Tidy
# ------------------------------------------------------------------------------

if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_BIN clang-tidy-5.0)
  find_program(RUN_CLANG_TIDY_BIN run-clang-tidy-5.0.py)

    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy-5.0")
    endif()

    if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate run-clang-tidy-5.0.py")
    endif()

    list(APPEND RUN_CLANG_TIDY_BIN_ARGS
         -clang-tidy-binary ${CLANG_TIDY_BIN}
         -header-filter="\".*\\b(cpp-client/src)\""
         -checks=clan*,cert*,misc*,perf*,cppc*,read*,mode*,-cert-err58-cpp,-misc-noexcept-move-constructor,-cppcoreguidelines-*)

    add_custom_target(tidy
                      COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
                      COMMENT "running clang tidy")
endif()

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Add the ARK C++ Client Library Subdirectory
# ------------------------------------------------------------------------------

add_subdirectory(src)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Add the ARK C++ Client Test Subdirectory
#
# Disabled by default.
#
# Use `cmake -DUNIT_TEST=ON ..` to enable Test building.
# ------------------------------------------------------------------------------

option(UNIT_TEST "Tests disabled by default" OFF)

if(UNIT_TEST)
    add_subdirectory(test)
endif()

# ------------------------------------------------------------------------------
