if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sandbox/CMakeLists.txt")
    add_subdirectory(sandbox)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/morrowind_like/CMakeLists.txt")
    add_subdirectory(morrowind_like)
endif()