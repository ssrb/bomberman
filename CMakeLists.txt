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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(${PROJECT_NAME} ${BOMBERMAN_SOURCES} ${BOMBERMAN_PRIVATE_HEADERS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_include_directories(${PROJECT_NAME} PRIVATE "thirdparty/boost")
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE "thirdparty/luacppinterface/LuaCppInterface")
target_include_directories(${PROJECT_NAME} PRIVATE "thirdparty/luacppinterface/lua/src")