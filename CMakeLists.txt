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

set (BOMBERMAN_PUBLIC_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)

set (BOMBERMAN_PUBLIC_HEADERS
        "include/8iTurboVideo/turbovideo_decodeErr.h"
        "include/8iTurboVideo/turbovideo_sdk.h"
    )


add_library(${PROJECT_NAME} STATIC ${TURBOVIDEOLIB_SOURCES} ${TURBOVIDEOLIB_PRIVATE_HEADERS} ${TURBOVIDEOLIB_PUBLIC_HEADERS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} PUBLIC
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                            $<INSTALL_INTERFACE:include> )

install(EXPORT 8iTurboVideo-targets DESTINATION ${TURBOVIDEO_CONFIG_INSTALL_DIR})
