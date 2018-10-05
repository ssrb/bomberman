cmake_minimum_required(VERSION 3.8)

project(SDL_image VERSION 1.0.0.0 LANGUAGES C CXX)

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

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/../build/cmake")
find_package(SDL2 REQUIRED)


add_library(${PROJECT_NAME} SHARED ${SDL_image_SOURCES} ${SDL_image_PRIVATE_HEADERS} ${SDL_image_PUBLIC_HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_BMP)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_GIF)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_JPG)
if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_JPG_DYNAMIC="libjpeg-9.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libjpeg-9.dll" DESTINATION bin)
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_LBM)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PCX)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PNG)
if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PNG_DYNAMIC="libpng16-16.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libpng16-16.dll" DESTINATION bin)
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_PNM)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_SVG)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_TGA)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_TIF)
if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_TIF_DYNAMIC="libtiff-5.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libtiff-5.dll" DESTINATION bin)
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_WEBP)
if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_WEBP_DYNAMIC="libwebp-7.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libwebp-7.dll" DESTINATION bin)
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_XPM)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOAD_XV)
target_compile_definitions(${PROJECT_NAME} PRIVATE PNG_USE_DLL)
target_compile_definitions(${PROJECT_NAME} PRIVATE ZLIB_DLL)

if (WIN32)
	target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/VisualC/external/include")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

set (showimage_SOURCES
    "showimage.c"
)

add_executable(showimage ${showimage_SOURCES})
target_link_libraries(showimage PRIVATE ${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2)

#include(CMakePackageConfigHelpers)
#
#configure_package_config_file(
#    cmake-src/8iturbovideo-config.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}/8iturbovideo-config-tmp
#    INSTALL_DESTINATION ${TURBOVIDEO_CONFIG_INSTALL_DIR}
#    PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR
#    )
#
#write_basic_package_version_file(
#    ${CMAKE_CURRENT_BINARY_DIR}/8iturbovideo-config-version.cmake
#    VERSION ${PROJECT_VERSION}
#    COMPATIBILITY SameMajorVersion
#    )

install(FILES ${SDL_image_PUBLIC_HEADERS} DESTINATION include)
install(TARGETS ${PROJECT_NAME}
	    EXPORT  SDL_image-targets
	    RUNTIME DESTINATION bin
	    LIBRARY DESTINATION lib
	    ARCHIVE DESTINATION lib
	)