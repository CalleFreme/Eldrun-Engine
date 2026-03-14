add_library(eldrun_core STATIC
    src/log.cpp
)

add_library(Eldrun::core ALIAS eldrun_core)

target_compile_features(eldrun_core PUBLIC cxx_std_20)

target_include_directories(eldrun_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(eldrun_core
    PUBLIC
        eldrun_warnings
)

set_target_properties(eldrun_core PROPERTIES
    FOLDER "engine"
)