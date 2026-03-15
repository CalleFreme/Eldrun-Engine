add_library(eldrun_runtime STATIC
    src/app_state.cpp
)

add_library(Eldrun::runtime ALIAS eldrun_runtime)

target_compile_features(eldrun_runtime PUBLIC cxx_std_20)

target_include_directories(eldrun_runtime
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(eldrun_runtime
    PUBLIC
        eldrun_core
        eldrun_render
    PRIVATE
        eldrun_warnings
)

set_target_properties(eldrun_runtime PROPERTIES
    FOLDER "engine"
)