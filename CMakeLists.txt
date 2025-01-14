cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GEOAProject)


file(GLOB SOURCES 
    "main.cpp"
    "FlyFish.cpp" 
    "Game.cpp" 
    "Structs.cpp" 
    "Utils.cpp" 
    "FlyStructs.cpp"
    "FlyUtils.cpp"
    "Globals.cpp" 
    "src/*.cpp"
)

add_executable( ${PROJECT_NAME} ${SOURCES} )


# Simple Directmedia Layer
set(SDL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/SDL2-2.30.9")
add_library(SDL STATIC IMPORTED)
set_target_properties(SDL PROPERTIES
    IMPORTED_LOCATION "${SDL_DIR}/lib/SDL2.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL_DIR}/include"
)


# Simple Directmedia Layer TTF
set(SDL_TTF_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/SDL2_ttf-2.22.0")
add_library(SDL_TTF STATIC IMPORTED)
set_target_properties(SDL_TTF PROPERTIES
    IMPORTED_LOCATION "${SDL_TTF_DIR}/lib/SDL2_ttf.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL_TTF_DIR}/include"
)

# Link SDL2main.lib explicitly if available
if(EXISTS "${SDL_DIR}/lib/SDL2main.lib")
    set_target_properties(SDL PROPERTIES
        IMPORTED_LINK_INTERFACE_LIBRARIES "${SDL_DIR}/lib/SDL2main.lib")
else()
    message(FATAL_ERROR "SDL2main.lib not found in ${SDL_DIR}/lib.")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL SDL_TTF opengl32)


file(GLOB_RECURSE DLL_FILES
    "${SDL_DIR}/lib/*.dll"
    "${SDL_DIR}/lib/*.manifest"
    "${SDL_TTF_DIR}/lib/*.dll"
    "${SDL_TTF_DIR}/lib/*.manifest"
)


foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${DLL}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endforeach(DLL)
