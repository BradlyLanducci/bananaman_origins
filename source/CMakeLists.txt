file(GLOB_RECURSE GameSourceFiles 
	${CMAKE_SOURCE_DIR}/source/*.cpp
)
	
add_executable(${PROJECT_NAME}
	${GameSourceFiles}
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