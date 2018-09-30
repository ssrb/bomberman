cmake_minimum_required(VERSION 3.8)

project(SDL_image VERSION 1.0.0.0 LANGUAGES C CXX)

#LOAD_BMP
#LOAD_GIF
#LOAD_JPG
#LOAD_JPG_DYNAMIC="libjpeg-9.dll"
#LOAD_LBM
#LOAD_PCX
#LOAD_PNG
#LOAD_PNG_DYNAMIC="libpng16-16.dll"
#LOAD_PNM
#LOAD_SVG
#LOAD_TGA
#LOAD_TIF
#LOAD_TIF_DYNAMIC="libtiff-5.dll"
#LOAD_WEBP
#LOAD_WEBP_DYNAMIC="libwebp-7.dll"
#LOAD_XPM
#LOAD_XV
#PNG_USE_DLL
#ZLIB_DLL


set (SDL_image_SOURCES
    "IMG_bmp.c"
    "IMG_gif.c"
    "IMG_lbm.c"
    "IMG_png.c"
    "IMG_svg.c"
    "IMG_tif.c"
    "IMG_WIC.c"
    "IMG_xpm.c"
    "IMG_xxx.c"
    "IMG.c"
    "IMG_jpg.c"
    "IMG_pcx.c"
    "IMG_pnm.c"
    "IMG_tga.c"
    "IMG_webp.c"
    "IMG_xcf.c"
    "IMG_xv.c" )

set (SDL_image_PRIVATE_HEADERS
    "miniz.h"
    "nanosvg.h"
    "nanosvgrast.h"
)

set (SDL_image_PUBLIC_HEADERS
    "SDL_image.h"
)



#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/../build/cmake")
find_package(SDL2 REQUIRED)


add_library(${PROJECT_NAME} SHARED ${SDL_image_SOURCES} ${SDL_image_PRIVATE_HEADERS} ${SDL_image_PUBLIC_HEADERS})
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${PROJECT_NAME} PRIVATE SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

set (showimage_SOURCES
    "showimage.c"
)

add_executable(showimage ${showimage_SOURCES})
target_link_libraries(showimage PRIVATE ${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2)