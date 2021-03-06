cmake_minimum_required(VERSION 3.8)

project(Bomberman VERSION 1.0.0.0 LANGUAGES CXX)

include(ExternalProject)

option(SMALL_SCREEN "Small screen support" ON)

set (BOMBERMAN_SOURCES
    "src/block.cpp"
    "src/bomb.cpp"
    "src/bonus.cpp"
    "src/compositescene.cpp"
    "src/computer.cpp"
    "src/corpse.cpp"
    "src/entity.cpp"
    "src/explosion.cpp"
    "src/fadescene.cpp"
    "src/floortile.cpp"
    "src/gamescene.cpp"
    "src/inputstate.cpp"
    "src/main.cpp"
    "src/map.cpp"
    "src/menuscene.cpp"
    "src/player.cpp"
    "src/printlog.cpp"
    "src/propbomb.cpp"
    "src/propexplosion.cpp"
    "src/resourcemanager.cpp"
    "src/scriptapi.cpp"
    "src/setupscene.cpp"
    "src/softblock.cpp"
    "src/umpire.cpp"
    "src/utils.cpp"
    "src/victoryscene.cpp"
)

set (BOMBERMAN_PRIVATE_HEADERS
    "src/block.hpp"
    "src/computer.hpp"
    "src/corpse.hpp"
    "src/fadescene.hpp"
    "src/map.hpp"
    "src/propbomb.hpp"
    "src/sceneresult.hpp"
    "src/umpire.hpp"
    "src/bomb.hpp"         
    "src/constants_game.hpp"        
    "src/entity.hpp"     
    "src/floortile.hpp"   
    "src/menuscene.hpp"  
    "src/propexplosion.hpp"    
    "src/scriptapi.hpp"    
    "src/utils.hpp"
    "src/bonus.hpp"           
    "src/constants_input.hpp"       
    "src/entityptr.hpp"  
    "src/gamescene.hpp"   
    "src/player.hpp"     
    "src/resourcemanager.hpp"  
    "src/setupscene.hpp"   
    "src/victoryscene.hpp"
    "src/compositescene.hpp"  
    "src/constants_resolution.hpp"  
    "src/explosion.hpp"  
    "src/inputstate.hpp"  
    "src/printlog.hpp"   
    "src/scene_interface.hpp"  
    "src/softblock.hpp"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
if (WIN32)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/thirdparty/build/cmake")
else ()
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/thirdparty/build/lib/cmake/SDL2")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/thirdparty/SDL")
add_subdirectory("${PROJECT_SOURCE_DIR}/thirdparty/SDL_image")
add_subdirectory("${PROJECT_SOURCE_DIR}/thirdparty/SDL_mixer")
add_subdirectory("${PROJECT_SOURCE_DIR}/thirdparty/SDL_ttf")

add_executable(${PROJECT_NAME} ${BOMBERMAN_SOURCES} ${BOMBERMAN_PRIVATE_HEADERS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

if (SMALL_SCREEN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SMALL_SCREEN)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/LuaCppInterface")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/lua/src")

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/SDL/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/SDL_image")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/SDL_mixer")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/SDL_ttf")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL_mixer)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL_ttf)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/x64/Release/LuaCppInterface.lib")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/x64/Release/LuaLib.lib")
else()

    ExternalProject_Add(luacppinterface
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=-fPIC"
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE true
    )

    ExternalProject_Add(lua
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/lua"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND make linux
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE true
    )

    add_dependencies(luacppinterface lua)
    add_dependencies(${PROJECT_NAME} luacppinterface)

    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/libluacppinterface.a")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/lua/src/liblua.a")
    target_link_libraries(${PROJECT_NAME} PRIVATE gcov)

endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/aiscripts" DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/drawable" DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/music" DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/sound" DESTINATION bin)