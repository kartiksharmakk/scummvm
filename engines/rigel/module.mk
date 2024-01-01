MODULE := engines/rigel

MODULE_OBJS = \
	rigel.o \
    console.o \
    metaengine.o \
	assets/actor_image_package.o \
	assets/audio_package.o \
	assets/cmp_file_package.o \
	assets/duke_script_loader.o \
	assets/file_utils.o \
	assets/ega_image_decoder.o \
	assets/level_loader.o \
	assets/movie_loader.o \
	assets/music_loader.o \
	assets/palette.o \
	assets/png_image.o \
	assets/resource_loader.o \
	assets/user_profile_import.o \
	assets/voc_decoder.o \
	audio/software_imf_player.o \
	audio/sound_system.o \
	base/string_utils.o \
	base/array_view.o \
	base/image.o \
	data/game_options.o \
	data/high_score_list.o \
	data/level_hints.o \
	data/map.o \
	data/player_model.o \
	data/tutorial_messages.o \
	data/unit_conversions.o \
	engine/collision_checker.o \
	game_logic_classic/game_world_classic.o \
	frontend/intro_demo_loop_mode.o \
	frontend/json_utils.o \
	frontend/menu_mode.o \
	renderer/fps_limiter.o \
	sdl_utils/platform.o \
	sdl_utils/error.o \
	ui/apogee_logo.o \
	ui/bonus_screen.o \
	ui/duke_3d_teaser_screen.o \
	ui/intro_movie.o \
	ui/movie_player.o \


# This module can be built as a plugin
ifeq ($(ENABLE_RIGEL), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o
