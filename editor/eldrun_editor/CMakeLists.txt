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

if(WIN32 AND TARGET SDL3-shared)
    add_custom_command(TARGET eldrun_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:eldrun_editor>
        VERBATIM
    )
endif()