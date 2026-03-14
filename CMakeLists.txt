cmake_minimum_required(VERSION 3.25)

project(Eldrun
    VERSION 0.1.0
    DESCRIPTION "Eldrun Engine"
    LANGUAGES CXX
)

# Better IDE organization where supported.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Helpful defaults for top-level development.
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/warnings"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchains")

include(EldrunOptions)
include(EldrunWarnings)
include(EldrunDependencies)
include(EldrunModule)

add_subdirectory(engine)

if(ELDRUN_BUILD_GAMES AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/games/CMakeLists.txt")
    add_subdirectory(games)
endif()

if(ELDRUN_BUILD_EDITOR AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/editor/CMakeLists.txt")
    add_subdirectory(editor)
endif()

if(ELDRUN_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# ---- Package export / install ----
# This keeps the project on a good path toward external consumption later.
if(ELDRUN_ENABLE_INSTALL)
    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/EldrunConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/EldrunConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Eldrun"
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/EldrunConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY SameMajorVersion
    )

    install(
        EXPORT EldrunTargets
        NAMESPACE Eldrun::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Eldrun"
    )

    install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/EldrunConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/EldrunConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Eldrun"
    )
endif()