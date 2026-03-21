add_library(eldrun_render
    src/renderer.cpp
)

add_library(Eldrun::render ALIAS eldrun_render)

target_include_directories(eldrun_render
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(eldrun_render
    PUBLIC
        eldrun_core
        SDL3::SDL3
    PRIVATE
        eldrun_warnings
)

target_compile_features(eldrun_render PUBLIC cxx_std_20)

if(ELDRUN_ENABLE_BGFX)
    target_sources(eldrun_render
        PRIVATE
            src/renderer_backend_bgfx.cpp
            src/bgfx_platform.cpp
    )

    target_compile_definitions(eldrun_render PRIVATE ELDRUN_ENABLE_BGFX=1)

    target_link_libraries(eldrun_render
        PRIVATE
            bgfx
            bx
            bimg
    )
else()
    target_sources(eldrun_render
        PRIVATE
            src/renderer_backend_sdl.cpp
    )
endif()

set_target_properties(eldrun_render PROPERTIES
    FOLDER "engine"
)

if(ELDRUN_ENABLE_INSTALL)
    install(TARGETS eldrun_render
        EXPORT EldrunTargets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )

    install(DIRECTORY include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endif()