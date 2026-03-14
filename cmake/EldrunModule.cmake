function(eldrun_add_interface_module target alias module_dir)
    add_library(${target} INTERFACE)
    add_library(Eldrun::${alias} ALIAS ${target})

    target_compile_features(${target} INTERFACE cxx_std_20)

    target_include_directories(${target} INTERFACE
        $<BUILD_INTERFACE:${module_dir}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    target_link_libraries(${target} INTERFACE eldrun_warnings)

    set_target_properties(${target} PROPERTIES
        FOLDER "engine"
    )

    if(ELDRUN_ENABLE_INSTALL)
        install(TARGETS ${target}
            EXPORT EldrunTargets
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )
    endif()
endfunction()