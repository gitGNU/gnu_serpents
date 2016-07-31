/*
Copyright 2016 Jochem Raat <jchmrt@riseup.net>

This file is part of serpents.

serpents is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your
option) any later version.

serpents is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with serpents.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef GAME_H_
#define GAME_H_

#include "state.h"
#include "color.h"
#include "board.h"
#include "input_buffer.h"
#include "interface.h"
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct
{
  int tile_size,
    snake_padding,
    food_padding,
    board_width,
    board_height,
    number_of_snakes;
  RGBA_Color background_color,
    *snake_colors;
} Game_Settings;

Game_Settings default_game_settings;

void run_game (Game_Settings);

static Game_State *initialize_game (Game_Settings);
static void initialize_SDL (Game_State *, int, int);
static void game_loop (Game_State *);
static int step_game (Game_State *);
static int move (Game_State *);

static void get_all_input (Game_State *);
static Snake *current_snake (Game_State *);
static Direction pop_next_direction (Game_State *);
static Direction current_direction (Game_State *);
static int is_valid_direction_change (Direction, Direction);
static void delay (Game_State *);

#endif
