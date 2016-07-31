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
#ifndef STATE_H_
#define STATE_H_

#include "board.h"
#include "color.h"
#include "input_buffer.h"
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct
{
  Board *board;

  int number_of_snakes;
  char current_snake;
  Snake *snakes;

  int tile_size,
    width,
    height,
    snake_padding,
    food_padding;
  RGBA_Color background_color;
  RGBA_Color *snake_colors;

  TTF_Font *score_font;

  SDL_Renderer *renderer;
  SDL_Window *window;

  Input_Buffer *input_buffer;
  int time_to_delay,
    score;
} Game_State;

#endif
