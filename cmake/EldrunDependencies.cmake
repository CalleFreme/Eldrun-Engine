# SDL3 ------------------------------------------------------------

set(ELDRUN_SDL_TARGET "" CACHE INTERNAL "Resolved SDL target for Eldrun")

if(ELDRUN_ENABLE_SDL)
    if(ELDRUN_USE_SYSTEM_SDL)
        find_package(SDL3 REQUIRED CONFIG)
    else()
        set(ELDRUN_VENDORED_SDL_DIR "${PROJECT_SOURCE_DIR}/external/SDL")

        if(EXISTS "${ELDRUN_VENDORED_SDL_DIR}/CMakeLists.txt")
            add_subdirectory(
                "${ELDRUN_VENDORED_SDL_DIR}"
                "${CMAKE_BINARY_DIR}/external/SDL"
                EXCLUDE_FROM_ALL
            )
        else()
            message(FATAL_ERROR
                "ELDRUN_ENABLE_SDL is ON, but no vendored SDL checkout was found at:\n"
                "  ${ELDRUN_VENDORED_SDL_DIR}\n"
                "Expected SDL source with a top-level CMakeLists.txt.\n"
                "Fix this by either:\n"
                "  1) adding SDL under external/SDL, or\n"
                "  2) configuring with ELDRUN_USE_SYSTEM_SDL=ON."
            )
        endif()
    endif()

    set(ELDRUN_SDL_TARGET SDL3::SDL3 CACHE INTERNAL "Resolved SDL target for Eldrun" FORCE)
endif()

# bgfx ------------------------------------------------------------
# Official bgfx builds are centered on GENie. Keep root CMake clean and stable
# by enabling bgfx only after you have a deliberate bridge/wrapper strategy.
if(ELDRUN_ENABLE_BGFX)
    message(FATAL_ERROR
        "ELDRUN_ENABLE_BGFX is ON, but bgfx integration has not been wired into the CMake build yet.\n"
        "Recommended approach: integrate bgfx through engine/thirdparty_bridge or a dedicated wrapper target."
    )
endif()