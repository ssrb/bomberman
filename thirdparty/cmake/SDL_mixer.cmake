cmake_minimum_required(VERSION 3.8)

project(SDL_mixer VERSION 1.0.0.0 LANGUAGES C CXX)

if (NOT WIN32)
	option(MUSIC_CMD "Enable CMD support" OFF)
endif()
option(MUSIC_WAV "Enable WAV support" ON)
option(MUSIC_FLAC "Enable FLAC support" ON)
option(MUSIC_OGG "Enable OGG support" ON)
option(MUSIC_OPUS "Enable OPUS support" ON)
option(MUSIC_MP3_MPG123 "Enable MPG123 MP3 support" ON)
option(MUSIC_MP3_MAD "Enable MAD MP3 support" OFF)
option(MUSIC_MP3_SMPEG "Enable smpeg MP3 support" OFF)
option(MUSIC_MOD_MODPLUG "Enable modplug support" ON)
option(MUSIC_MOD_MIKMOD "Enable mikmod support" OFF)
option(MUSIC_MID_FLUIDSYNTH "Enable fluidsynth support" OFF)
option(MUSIC_MID_TIMIDITY "Enable timidity support" ON)
option(MUSIC_MID_NATIVE "Enable native MIDI support" ON)

set (SDL_mixer_SOURCES
    "effect_position.c"
    "load_aiff.c"
    "music.c"
    "music_fluidsynth.c"
    "music_modplug.c"
    "music_ogg.c"
    "music_timidity.c"
    "effects_internal.c"
    "load_voc.c"
    "music_cmd.c"
    "music_mad.c"
    "music_mpg123.c"
    "music_opus.c"
    "music_wav.c"
    "effect_stereoreverse.c"
    "mixer.c"
    "music_flac.c"
    "music_mikmod.c"
    "music_nativemidi.c"
    "music_smpeg.c"
)

set (SDL_mixer_PRIVATE_HEADERS
    "effects_internal.h"
    "mixer.h"
    "music_fluidsynth.h"
    "music_mikmod.h"
    "music_nativemidi.h"
    "music_smpeg.h"
    "load_aiff.h"
    "music_cmd.h"
    "music.h"
    "music_modplug.h"
    "music_ogg.h"
    "music_timidity.h"
    "load_voc.h"
    "music_flac.h"
    "music_mad.h"
    "music_mpg123.h"
    "music_opus.h"
    "music_wav.h"
)

set (SDL_mixer_PUBLIC_HEADERS
    "SDL_mixer.h"
)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/../build/cmake")
find_package(SDL2 REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SDL_mixer_SOURCES} ${SDL_mixer_PRIVATE_HEADERS} ${SDL_mixer_PUBLIC_HEADERS})

if (WIN32)
	target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/VisualC/external/include")
endif()

if (MUSIC_CMD)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_CMD)
endif()
if (MUSIC_WAV)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_WAV)
endif()
if (MUSIC_FLAC)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_FLAC)
	target_compile_definitions(${PROJECT_NAME} PRIVATE FLAC_DYNAMIC="libFLAC-8.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libFLAC-8.dll" DESTINATION bin)
endif()
if (MUSIC_OGG)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_OGG)
	target_compile_definitions(${PROJECT_NAME} PRIVATE OGG_DYNAMIC="libvorbisfile-3.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libvorbisfile-3.dll" DESTINATION bin)
endif()
if (MUSIC_OPUS)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_OPUS)
	target_compile_definitions(${PROJECT_NAME} PRIVATE OPUS_DYNAMIC="libopusfile-0.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libopusfile-0.dll" DESTINATION bin)
endif()
if (MUSIC_MP3_MPG123)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MP3_MPG123)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MPG123_DYNAMIC="libmpg123-0.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libmpg123-0.dll" DESTINATION bin)
endif()
if (MUSIC_MP3_MAD)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MP3_MAD)
endif()
if (MUSIC_MP3_SMPEG)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MP3_SMPEG)
endif()
if (MUSIC_MOD_MODPLUG)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MOD_MODPLUG)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MODPLUG_DYNAMIC="libmodplug-1.dll")
	install(FILES "${PROJECT_SOURCE_DIR}/VisualC/external/lib/x64/libmodplug-1.dll" DESTINATION bin)
endif()
if (MUSIC_MOD_MIKMOD)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MOD_MIKMOD)
endif()
if (MUSIC_MID_FLUIDSYNTH)
	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MID_FLUIDSYNTH)
endif()

if (MUSIC_MID_TIMIDITY)

	set (timidity_SOURCES
		"timidity/common.c"
		"timidity/instrum.c"
		"timidity/mix.c"
		"timidity/output.c"
		"timidity/playmidi.c"
		"timidity/readmidi.c"
		"timidity/resample.c"
		"timidity/tables.c"
		"timidity/timidity.c"
	)

	set (timidity_PRIVATE_HEADERS
		"timidity/common.h"
		"timidity/instrum.h"
		"timidity/mix.h"
		"timidity/options.h"
		"timidity/output.h"
		"timidity/playmidi.h"
		"timidity/readmidi.h"
		"timidity/resample.h"
		"timidity/tables.h"
	)

	set (timidity_PUBLIC_HEADERS
		"timidity/timidity.h"
	)

	add_library(timidity STATIC ${timidity_SOURCES} ${timidity_PRIVATE_HEADERS} ${timidity_PUBLIC_HEADERS})
	target_link_libraries(timidity PRIVATE SDL2::SDL2)

	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MID_TIMIDITY)
	target_link_libraries(${PROJECT_NAME} PRIVATE timidity)

endif()

if (MUSIC_MID_NATIVE)

	set (native_midi_SOURCES
		"native_midi/native_midi_common.c"
	)

	if (WIN32)
		set (native_midi_SOURCES
			${native_midi_SOURCES}
			"native_midi/native_midi_win32.c"
		)
	endif()

	#	"native_midi/native_midi_mac.c"
	#	"native_midi/native_midi_macosx.c"

	set (native_midi_PRIVATE_HEADERS
		"native_midi/native_midi_common.h"
	)

	set (native_midi_PUBLIC_HEADERS
		"native_midi/native_midi.h"
	)

	add_library(native_midi STATIC ${native_midi_SOURCES} ${native_midi_PRIVATE_HEADERS} ${native_midi_PUBLIC_HEADERS})
	target_link_libraries(native_midi PRIVATE SDL2::SDL2)

	target_compile_definitions(${PROJECT_NAME} PRIVATE MUSIC_MID_NATIVE)
	target_link_libraries(${PROJECT_NAME} PRIVATE native_midi)

endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

set (playmus_SOURCES
	"playmus.c"
)

add_executable(playmus ${playmus_SOURCES})
target_link_libraries(playmus PRIVATE SDL2::SDL2main SDL2::SDL2 ${PROJECT_NAME})

set (playwave_SOURCES
	"playwave.c"
)

add_executable(playwave ${playwave_SOURCES})
target_link_libraries(playwave PRIVATE SDL2::SDL2main SDL2::SDL2 ${PROJECT_NAME})

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

install(FILES ${SDL_mixer_PUBLIC_HEADERS} DESTINATION include)
install(TARGETS ${PROJECT_NAME}
	    EXPORT  SDL_mixer-targets
	    RUNTIME DESTINATION bin
	    LIBRARY DESTINATION lib
	    ARCHIVE DESTINATION lib
	)