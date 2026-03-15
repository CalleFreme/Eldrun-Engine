add_library(eldrun_render
    src/renderer.cpp
 "src/renderer_backend_sdl.cpp" "src/renderer_backend_bgfx.cpp")

add_library(Eldrun::render ALIAS eldrun_render)

target_include_directories(eldrun_render
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(eldrun_render
    PUBLIC
        eldrun_core
        SDL3::SDL3
    PRIVATE
        eldrun_warnings
)

target_compile_features(eldrun_render PUBLIC cxx_std_20)

if(ELDRUN_ENABLE_INSTALL)
    install(TARGETS eldrun_render
        EXPORT EldrunTargets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )

    install(DIRECTORY include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endif()