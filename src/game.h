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

#endif
