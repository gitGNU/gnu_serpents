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
#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "state.h"
#include "color.h"
#include "board.h"
#include <SDL.h>

void draw (Game_State *);
int draw_game_over (Game_State *);

static char *itoa (int);
static void draw_text (Game_State *, TTF_Font *, char *,
                       SDL_Color, int, int, int, int);
static void draw_overlay (Game_State *, SDL_Color, int);
static void draw_snake (Game_State *, char);
static void draw_tail (Game_State *, Vector, Direction);
static void draw_snake_tile (Game_State *, Vector, Direction, Direction);
static void draw_food (Game_State *, char, int, int);
static void set_color (Game_State *, RGBA_Color col);
static Direction reverse_dir (Direction);

#endif
