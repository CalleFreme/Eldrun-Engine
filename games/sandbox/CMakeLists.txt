add_executable(eldrun_sandbox
    src/main.cpp
)

add_executable(Eldrun::sandbox ALIAS eldrun_sandbox)

target_link_libraries(eldrun_sandbox
    PRIVATE
        eldrun_engine
)

target_compile_features(eldrun_sandbox PRIVATE cxx_std_20)

set_target_properties(eldrun_sandbox PROPERTIES
    OUTPUT_NAME "eldrun_sandbox"
    FOLDER "games"
)