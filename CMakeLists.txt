cmake_minimum_required(VERSION 3.25)

project(WithlandCore-Rebuild
    VERSION      0.1.0
    DESCRIPTION  "Domain core for WithLand — a colony survival simulator"
    HOMEPAGE_URL "https://github.com/Sharzhukov/WithlandCore-Rebuild"
    LANGUAGES    CXX
)

# ============================================================
#  Common settings — identical on all OSes
# ============================================================
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Default build type for single-config generators (Ninja, Make)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        Debug Release RelWithDebInfo MinSizeRel)
endif()

# macOS: minimum deployment target + optional universal binary
if(APPLE AND NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version" FORCE)
endif()

# Linux: use pthreads
if(UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

# Windows: enable UTF-8 source and execution charset for MSVC
if(MSVC)
    add_compile_options(/utf-8)
endif()

# ============================================================
#  Options
# ============================================================
option(WITHLAND_CORE_BUILD_LIBRARY      "Build WithlandCore library"        ON)
option(WITHLAND_CORE_BUILD_APP          "Build main executable (withland)"  ON)
option(WITHLAND_CORE_BUILD_SANDBOX      "Build sandbox executable"          ON)
option(WITHLAND_CORE_BUILD_TESTS        "Build tests"                       ON)
option(WITHLAND_CORE_WARNINGS_AS_ERRORS "Treat warnings as errors"          OFF)
option(WITHLAND_CORE_ENABLE_SANITIZERS  "Enable ASan + UBSan (Debug only)"  OFF)

# Sanitizers unsupported with MSVC multi-config + Ninja in some setups
if(MSVC AND WITHLAND_CORE_ENABLE_SANITIZERS)
    message(WARNING "Sanitizers on MSVC are experimental; consider disabling.")
endif()

# ============================================================
#  Helpers
# ============================================================
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

function(withland_apply_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive- /EHsc)
        if(WITHLAND_CORE_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
            -Wcast-align -Wunused -Woverloaded-virtual
        )
        if(WITHLAND_CORE_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()

function(withland_apply_sanitizers target)
    if(NOT WITHLAND_CORE_ENABLE_SANITIZERS)
        return()
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    elseif(MSVC)
        target_compile_options(${target} PRIVATE /fsanitize=address)
    endif()
endfunction()

# ============================================================
#  Core library
# ============================================================
if(WITHLAND_CORE_BUILD_LIBRARY)

    set(WITHLAND_ROOT_SOURCES
        # src/version.cpp
    )

    set(WITHLAND_COMMON_SOURCES
        src/common/common.cpp
    )
    set(WITHLAND_COMMON_HEADERS
        include/withland/common/common.hpp
    )

    set(WITHLAND_CORE_MODULE_SOURCES
        #core
        src/core/colonist.cpp
        # src/core/Colonist.cpp

        #components
        src/core/components/entityStates.cpp
    )
    set(WITHLAND_CORE_MODULE_HEADERS
        #core
        include/withland/core/colonist.hpp
        # include/withland/core/Colonist.hpp

        #components
        include/withland/core/components/entityStates.hpp
    )

    set(WITHLAND_CORE_SOURCES
        ${WITHLAND_ROOT_SOURCES}
        ${WITHLAND_COMMON_SOURCES}
        ${WITHLAND_CORE_MODULE_SOURCES}
    )
    set(WITHLAND_CORE_HEADERS
        ${WITHLAND_COMMON_HEADERS}
        ${WITHLAND_CORE_MODULE_HEADERS}
    )

    # Placeholder until the first real .cpp lands — remove afterwards.
    if(NOT WITHLAND_CORE_SOURCES)
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp"
             "// placeholder — remove when the first real .cpp is added\n")
        list(APPEND WITHLAND_CORE_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp")
    endif()

    add_library(WithlandCore ${WITHLAND_CORE_SOURCES} ${WITHLAND_CORE_HEADERS})
    add_library(Withland::Core ALIAS WithlandCore)

    target_include_directories(WithlandCore
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_compile_features(WithlandCore PUBLIC cxx_std_17)

    if(UNIX AND NOT APPLE)
        target_link_libraries(WithlandCore PRIVATE Threads::Threads)
    endif()

    withland_apply_warnings(WithlandCore)
    withland_apply_sanitizers(WithlandCore)

    # ---- Install rules (only when top-level) ----
    if(PROJECT_IS_TOP_LEVEL)
        install(TARGETS WithlandCore
            EXPORT  WithlandCoreTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
            install(DIRECTORY include/
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
            )
        endif()

        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
            install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
                DESTINATION ${CMAKE_INSTALL_DATADIR}/WithlandCore
            )
        endif()

        install(EXPORT WithlandCoreTargets
            FILE      WithlandCoreTargets.cmake
            NAMESPACE Withland::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WithlandCore
        )

        set(_withland_config_in "${CMAKE_CURRENT_SOURCE_DIR}/cmake/WithlandCoreConfig.cmake.in")
        if(NOT EXISTS "${_withland_config_in}")
            message(FATAL_ERROR
                "Missing file: ${_withland_config_in}\n"
                "Create it with the contents shown in the project README."
            )
        endif()

        configure_package_config_file(
            "${_withland_config_in}"
            "${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WithlandCore
        )

        write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfigVersion.cmake"
            VERSION       ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
        )

        install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WithlandCore
        )
    endif()
endif()

# ============================================================
#  app / sandbox / tests
# ============================================================
if(WITHLAND_CORE_BUILD_APP AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app/CMakeLists.txt")
    add_subdirectory(app)
endif()

if(WITHLAND_CORE_BUILD_SANDBOX AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sandbox/CMakeLists.txt")
    add_subdirectory(sandbox)
endif()

if(WITHLAND_CORE_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    if(PROJECT_IS_TOP_LEVEL)
        enable_testing()
    endif()
    add_subdirectory(tests)
endif()

# ============================================================
#  Status report
# ============================================================
if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "")
    message(STATUS "WithlandCore-Rebuild ${PROJECT_VERSION}")
    message(STATUS "  Build type   : ${CMAKE_BUILD_TYPE}")
    message(STATUS "  C++ compiler : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "  Library      : ${WITHLAND_CORE_BUILD_LIBRARY}")
    message(STATUS "  App          : ${WITHLAND_CORE_BUILD_APP}")
    message(STATUS "  Sandbox      : ${WITHLAND_CORE_BUILD_SANDBOX}")
    message(STATUS "  Tests        : ${WITHLAND_CORE_BUILD_TESTS}")
    message(STATUS "  Werror       : ${WITHLAND_CORE_WARNINGS_AS_ERRORS}")
    message(STATUS "  Sanitizers   : ${WITHLAND_CORE_ENABLE_SANITIZERS}")
    message(STATUS "")
endif()