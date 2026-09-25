cmake_minimum_required(VERSION 3.21)

project(WithlandCore
    VERSION     0.1.0
    DESCRIPTION "WithLand core logic — pure C++17, no external deps"
    LANGUAGES   CXX
)

# ============================================================
#  Общие настройки — одинаково на всех ОС
# ============================================================
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(APPLE AND NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version" FORCE)
endif()

if(UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

# ============================================================
#  Опции
# ============================================================
option(WITHLAND_CORE_BUILD_LIBRARY      "Build WithlandCore library"        ON)
option(WITHLAND_CORE_BUILD_APP          "Build main executable (withland)"  ON)
option(WITHLAND_CORE_BUILD_SANDBOX      "Build sandbox executable"          ON)
option(WITHLAND_CORE_BUILD_TESTS        "Build tests"                       ON)
option(WITHLAND_CORE_WARNINGS_AS_ERRORS "Treat warnings as errors"          OFF)

# ============================================================
#  Helpers
# ============================================================
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

function(withland_apply_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8 /EHsc)
        if(WITHLAND_CORE_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
            -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
        )
        if(WITHLAND_CORE_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()

# ============================================================
#  Библиотека ядра
# ============================================================
if(WITHLAND_CORE_BUILD_LIBRARY)

    # --- src/*.cpp (верхнеуровневые) ---
    set(WITHLAND_ROOT_SOURCES
        # src/version.cpp
    )

    # --- модуль common (src/common/*.cpp) ---
    set(WITHLAND_COMMON_SOURCES
        # src/common/Utils.cpp
    )
    set(WITHLAND_COMMON_HEADERS
        # include/withland/common/Utils.hpp
    )

    # --- модуль core (src/core/*.cpp) ---
    set(WITHLAND_CORE_MODULE_SOURCES
        # src/core/Colony.cpp
        # src/core/Colonist.cpp
    )
    set(WITHLAND_CORE_MODULE_HEADERS
        # include/withland/core/Colony.hpp
        # include/withland/core/Colonist.hpp
    )

    # --- агрегируем ---
    set(WITHLAND_CORE_SOURCES
        ${WITHLAND_ROOT_SOURCES}
        ${WITHLAND_COMMON_SOURCES}
        ${WITHLAND_CORE_MODULE_SOURCES}
    )
    set(WITHLAND_CORE_HEADERS
        ${WITHLAND_COMMON_HEADERS}
        ${WITHLAND_CORE_MODULE_HEADERS}
    )

    # Заглушка, пока нет ни одного .cpp. Удалить, когда появится первый файл.
    if(NOT WITHLAND_CORE_SOURCES)
        file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_placeholder.cpp"
             "// placeholder — remove when first real .cpp is added\n")
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

    # --- установка ---
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

    install(EXPORT WithlandCoreTargets
        FILE      WithlandCoreTargets.cmake
        NAMESPACE Withland::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WithlandCore
    )

    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/WithlandCoreConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WithlandCore
    )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfigVersion.cmake
        VERSION       ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/WithlandCoreConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WithlandCore
    )
endif()

# ============================================================
#  exe / sandbox / tests
# ============================================================
if(WITHLAND_CORE_BUILD_APP)
    add_subdirectory(app)
endif()

if(WITHLAND_CORE_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()

if(WITHLAND_CORE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()