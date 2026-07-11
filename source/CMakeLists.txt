file(GLOB_RECURSE GameSourceFiles 
	${CMAKE_SOURCE_DIR}/source/*.cpp
)
	
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME}
	${GameSourceFiles}
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets directory to build folder"
    VERBATIM
)

target_compile_features(${PROJECT_NAME} 
    PRIVATE 
        cxx_std_23
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/source
)

target_link_libraries(${PROJECT_NAME}
    AnguishEngine
)