cmake_minimum_required(VERSION 3.8)

project(SDL_ttf VERSION 1.0.0.0 LANGUAGES C CXX)

set (SDL_ttf_SOURCES
    "SDL_ttf.c"
    )

set (SDL_ttf_PRIVATE_HEADERS
)

set (SDL_ttf_PUBLIC_HEADERS
    "SDL_ttf.h"
)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/../build/cmake")
find_package(SDL2 REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SDL_ttf_SOURCES} ${SDL_ttf_PRIVATE_HEADERS} ${SDL_ttf_PUBLIC_HEADERS})

if (WIN32)
	target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/VisualC/external/include")
	target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libfreetype-6.lib")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libfreetype-6.dll" DESTINATION bin)
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/zlib1.dll" DESTINATION bin)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

set (glfont_SOURCES
    "glfont.c"
)

add_executable(glfont ${glfont_SOURCES})
target_link_libraries(glfont PRIVATE ${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2)

set (showfont_SOURCES
    "showfont.c"
)

add_executable(showfont ${showfont_SOURCES})
target_link_libraries(showfont PRIVATE ${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2)

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

install(FILES ${SDL_ttf_PUBLIC_HEADERS} DESTINATION include)
install(TARGETS ${PROJECT_NAME}
	    EXPORT  SDL_ttf-targets
	    RUNTIME DESTINATION bin
	    LIBRARY DESTINATION lib
	    ARCHIVE DESTINATION lib
	)