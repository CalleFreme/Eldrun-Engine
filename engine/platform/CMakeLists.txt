add_library(eldrun_platform STATIC
    src/application.cpp
)

add_library(Eldrun::platform ALIAS eldrun_platform)

target_compile_features(eldrun_platform PUBLIC cxx_std_20)

target_include_directories(eldrun_platform
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(eldrun_platform
    PUBLIC
        eldrun_core
        eldrun_render
        eldrun_runtime
    PRIVATE
        eldrun_warnings
        ${ELDRUN_SDL_TARGET}
)

set_target_properties(eldrun_platform PROPERTIES
    FOLDER "engine"
)