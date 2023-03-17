file(GLOB_RECURSE SRC_BUILD_FILES 
"*.cpp"
 "*.h" 
 "*.c"
 "*.hpp"  
)

set(ProjectName "SunEngine") 

add_executable(${ProjectName}   ${SRC_BUILD_FILES})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
         FILES ${SRC_BUILD_FILES})

add_library(STB_IMAGE 
"${PROJECT_SOURCE_DIR}/other/stb_image.cpp")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_library(GLAD 
"${PROJECT_SOURCE_DIR}/other//glad.c")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if(WIN32)
target_include_directories(${ProjectName} PUBLIC 
${PROJECT_SOURCE_DIR}/3rd/EnTT/include
${PROJECT_SOURCE_DIR}/src
${PROJECT_SOURCE_DIR}/src/runtime
)

target_link_libraries(${ProjectName} 
STB_IMAGE 
GLAD
opengl32
${PROJECT_SOURCE_DIR}/libs/assimp.lib
${PROJECT_SOURCE_DIR}/libs/freetype.lib
${PROJECT_SOURCE_DIR}/libs/glfw3.lib
${PROJECT_SOURCE_DIR}/libs/irrKlang.lib
)


file(GLOB DLLS 
"${PROJECT_SOURCE_DIR}/dlls/*.dll"
)

add_custom_command(TARGET ${ProjectName} POST_BUILD 
COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${DLLS}
        "${PROJECT_SOURCE_DIR}/Bin/${CMAKE_BUILD_TYPE}")

add_definitions(-DUNICODE -D_UNICODE)

endif(WIN32)
