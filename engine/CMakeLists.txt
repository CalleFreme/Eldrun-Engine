# Shared warning target
add_library(eldrun_warnings INTERFACE)
add_library(Eldrun::warnings ALIAS eldrun_warnings)
eldrun_apply_warnings(eldrun_warnings)

add_subdirectory(core)
add_subdirectory(render)
add_subdirectory(runtime)
add_subdirectory(platform)

# Placeholder interface modules for systems not yet implemented
eldrun_add_interface_module(eldrun_assets    assets    "${CMAKE_CURRENT_SOURCE_DIR}/assets")
eldrun_add_interface_module(eldrun_world     world     "${CMAKE_CURRENT_SOURCE_DIR}/world")
eldrun_add_interface_module(eldrun_gameplay  gameplay  "${CMAKE_CURRENT_SOURCE_DIR}/gameplay")
eldrun_add_interface_module(eldrun_tools     tools     "${CMAKE_CURRENT_SOURCE_DIR}/tools")
eldrun_add_interface_module(eldrun_net       net       "${CMAKE_CURRENT_SOURCE_DIR}/net")

# Module relationships
target_link_libraries(eldrun_render   PUBLIC eldrun_core)
target_link_libraries(eldrun_platform
    PUBLIC
        eldrun_core
        eldrun_render
        eldrun_runtime
)
target_link_libraries(eldrun_assets   INTERFACE eldrun_core)
target_link_libraries(eldrun_world    INTERFACE eldrun_core)
target_link_libraries(eldrun_gameplay INTERFACE eldrun_core eldrun_world eldrun_assets)
target_link_libraries(eldrun_tools    INTERFACE eldrun_core eldrun_render eldrun_world)
target_link_libraries(eldrun_net      INTERFACE eldrun_core eldrun_world)

# Aggregate engine target
add_library(eldrun_engine INTERFACE)
add_library(Eldrun::engine ALIAS eldrun_engine)

target_link_libraries(eldrun_engine INTERFACE
    eldrun_core
    eldrun_platform
    eldrun_render
    eldrun_runtime
    eldrun_assets
    eldrun_world
    eldrun_gameplay
    eldrun_tools
    eldrun_net
)

target_compile_features(eldrun_engine INTERFACE cxx_std_20)

if(ELDRUN_ENABLE_INSTALL)
    install(TARGETS
        eldrun_warnings
        eldrun_engine
        EXPORT EldrunTargets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endif()