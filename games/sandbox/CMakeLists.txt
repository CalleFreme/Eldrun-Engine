add_executable(eldrun_sandbox
    src/main.cpp
    src/sandbox_app_state.cpp
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

if(WIN32 AND TARGET SDL3-shared)
    add_custom_command(TARGET eldrun_sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:eldrun_sandbox>"
    )
endif()

