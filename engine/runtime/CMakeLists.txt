add_library(eldrun_runtime INTERFACE)
add_library(Eldrun::runtime ALIAS eldrun_runtime)

target_include_directories(eldrun_runtime
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(eldrun_runtime
    INTERFACE
        eldrun_core
        eldrun_render
)

target_compile_features(eldrun_runtime INTERFACE cxx_std_20)

set_target_properties(eldrun_runtime PROPERTIES
    FOLDER "engine"
)