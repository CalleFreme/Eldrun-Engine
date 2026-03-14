add_executable(eldrun_editor
    src/main.cpp
)

add_executable(Eldrun::editor ALIAS eldrun_editor)

target_link_libraries(eldrun_editor
    PRIVATE
        eldrun_engine
)

target_compile_features(eldrun_editor PRIVATE cxx_std_20)

set_target_properties(eldrun_editor PROPERTIES
    OUTPUT_NAME "eldrun_editor"
    FOLDER "editor"
)