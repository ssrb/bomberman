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

add_library(${PROJECT_NAME} SHARED ${SDL_ttf_SOURCES} ${SDL_ttf_PRIVATE_HEADERS} ${SDL_ttf_PUBLIC_HEADERS})

if (WIN32)
	target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/VisualC/external/include")
	target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libfreetype-6.lib")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libfreetype-6.dll" DESTINATION bin)
	# We depend on zlib but we're getting it from SDL_Image instead (libpng dependency)
	#install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/zlib1.dll" DESTINATION bin)
else()

	include(ExternalProject)

	ExternalProject_Add(freetype
		SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12"
		PREFIX "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12"
		CONFIGURE_COMMAND 
			"${PROJECT_SOURCE_DIR}/external/freetype-2.4.12/configure"
			--prefix "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12/install"
		BUILD_COMMAND 
			make
		INSTALL_COMMAND 
			make install
	)
	
	add_dependencies(${PROJECT_NAME} freetype)
	target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12/install/include")
	target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12/install/include/freetype2")
	target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12/install/lib/libfreetype.so.6.10.1")
	install(FILES "${PROJECT_SOURCE_DIR}/external/freetype-2.4.12/objs/.libs/libfreetype.so.6.10.1" DESTINATION bin)

endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${SDL2_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)

set (glfont_SOURCES
    "glfont.c"
)

add_executable(glfont ${glfont_SOURCES})
target_include_directories(glfont PRIVATE "${SDL2_SOURCE_DIR}/include")
target_link_libraries(glfont PRIVATE ${PROJECT_NAME} SDL2main SDL2)

set (showfont_SOURCES
    "showfont.c"
)

add_executable(showfont ${showfont_SOURCES})
target_include_directories(showfont PRIVATE "${SDL2_SOURCE_DIR}/include")
target_link_libraries(showfont PRIVATE ${PROJECT_NAME} SDL2main SDL2)

install(FILES ${SDL_ttf_PUBLIC_HEADERS} DESTINATION include)
install(TARGETS ${PROJECT_NAME}
	    EXPORT  SDL_ttf-targets
	    RUNTIME DESTINATION bin
	    LIBRARY DESTINATION lib
	    ARCHIVE DESTINATION lib
	)