cmake_minimum_required(VERSION 3.8)

project(SDL_image VERSION 1.0.0.0 LANGUAGES C CXX)

include(ExternalProject)

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
    "IMG_xv.c" 
)

set (SDL_image_PRIVATE_HEADERS
    "miniz.h"
    "nanosvg.h"
    "nanosvgrast.h"
)

set (SDL_image_PUBLIC_HEADERS
    "SDL_image.h"
)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/../build/cmake")
#find_package(SDL2 REQUIRED)

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
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/zlib1.dll" DESTINATION bin)
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
else()
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/jpeg-9b")
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/libpng-1.6.32")
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/libwebp-0.6.0")
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/zlib-1.2.11")
endif()
target_include_directories(${PROJECT_NAME} PRIVATE "${SDL2_SOURCE_DIR}/include")

if (NOT WIN32)

    ExternalProject_Add(tiff
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/tiff-4.0.8"
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/tiff-4.0.8/install"
    )
    add_dependencies(${PROJECT_NAME} tiff)
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/tiff-4.0.8/install/include")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/tiff-4.0.8/install/lib/libtiff.so")

    ExternalProject_Add(webp
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/libwebp-0.6.0"
        #PATCH_COMMAND patch < "${PROJECT_SOURCE_DIR}/external/libwebp-0.6.0.patch"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=-fPIC"
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE true
    )
    add_dependencies(${PROJECT_NAME} webp)
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/libwebp-0.6.0/src")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/libwebp-0.6.0/libwebp.a")

    ExternalProject_Add(png
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/libpng-1.6.32"
        #PATCH_COMMAND patch < "${PROJECT_SOURCE_DIR}/external/libpng-1.6.32.patch"
        CONFIGURE_COMMAND cmake . -DCMAKE_INSTALL_PREFIX=install
        BUILD_COMMAND make
        BUILD_IN_SOURCE true
    )
    add_dependencies(${PROJECT_NAME} png)
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/libpng-1.6.32/install/include")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/libpng-1.6.32/install/lib/libpng.so")

    ExternalProject_Add(jpeg
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/jpeg-9b"
        #PATCH_COMMAND patch < "${PROJECT_SOURCE_DIR}/external/jpeg-9b.patch"
        CONFIGURE_COMMAND 
			"${PROJECT_SOURCE_DIR}/external/jpeg-9b/configure"
			--prefix "${PROJECT_SOURCE_DIR}/external/jpeg-9b/install"
        BUILD_COMMAND 
			make
		INSTALL_COMMAND 
			make install
    )
    add_dependencies(${PROJECT_NAME} jpeg)
    target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/jpeg-9b/install/include")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/jpeg-9b/install/lib/libjpeg.so")

endif()

set (showimage_SOURCES
    "showimage.c"
)

add_executable(showimage ${showimage_SOURCES})
target_include_directories(showimage PRIVATE "${SDL2_SOURCE_DIR}/include")
target_link_libraries(showimage PRIVATE ${PROJECT_NAME} SDL2main SDL2)

install(FILES ${SDL_image_PUBLIC_HEADERS} DESTINATION include)
install(TARGETS ${PROJECT_NAME}
	    EXPORT  SDL_image-targets
	    RUNTIME DESTINATION bin
	    LIBRARY DESTINATION lib
	    ARCHIVE DESTINATION lib
)