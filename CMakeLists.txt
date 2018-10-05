cmake_minimum_required(VERSION 3.8)

project(Bomberman VERSION 1.0.0.0 LANGUAGES CXX)

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
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/LuaCppInterface")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/luacppinterface/lua/src")

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/build/include/SDL2")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/build/SDL_image/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/build/SDL_mixer/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/thirdparty/build/SDL_ttf/include")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL_mixer)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL_ttf)