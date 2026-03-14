option(ELDRUN_BUILD_GAMES "Build game/sample executables under games/" ON)
option(ELDRUN_BUILD_EDITOR "Build the editor executable" ON)
option(ELDRUN_BUILD_TESTS "Build automated tests" ON)

option(ELDRUN_ENABLE_INSTALL "Enable install/export/package generation" ${PROJECT_IS_TOP_LEVEL})
option(ELDRUN_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

option(ELDRUN_ENABLE_SDL "Enable SDL3 integration" ON)
option(ELDRUN_USE_SYSTEM_SDL "Use a system-installed SDL3 instead of vendored external/SDL" OFF)

# Keep bgfx opt-in until bridge/build strategy is ready.
option(ELDRUN_ENABLE_BGFX "Enable bgfx integration (currently expected through a custom bridge)" OFF)