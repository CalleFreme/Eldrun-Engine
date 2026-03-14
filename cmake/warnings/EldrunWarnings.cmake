function(eldrun_apply_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} INTERFACE
            /W4
            /permissive-
            /Zc:preprocessor
        )
        if(ELDRUN_WARNINGS_AS_ERRORS)
            target_compile_options(${target_name} INTERFACE /WX)
        endif()
    else()
        target_compile_options(${target_name} INTERFACE
            -Wall
            -Wextra
            -Wpedantic
        )
        if(ELDRUN_WARNINGS_AS_ERRORS)
            target_compile_options(${target_name} INTERFACE -Werror)
        endif()
    endif()
endfunction()