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
#ifndef BOARD_H_
#define BOARD_H_

typedef enum
  {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
  } Direction;

typedef enum
  {
    TILE_EMPTY,
    TILE_SNAKE,
    TILE_FOOD
  } Tile_Type;

typedef struct
{
  char id;
  Tile_Type type;
  Direction dir;
} Tile;

typedef struct
{
  int width,
    height;
  Tile *data;
} Board;

typedef struct
{
  int x, y;
} Vector;

typedef struct
{
  char id;
  Vector tail,
    head;
} Snake;



Board *initialize_board (int, int);
Snake initialize_snake (Board *, char, int, int, int, Direction);
Tile tile_from_head (Board *, Snake *, Direction);
void move_snake (Board *, Snake *, Direction, int);
void add_food (Board *, char);
Tile *get_tile (Board *, int, int);
Vector dir_to_vector (Direction);
Vector add_vectors_on_board (Board, Vector, Vector);

static void set_tile (Board *, int, int, char, Tile_Type, Direction);
static int dir_x (Direction);
static int dir_y (Direction);
static Vector add_vectors (Vector, Vector);
static Vector on_board (Board, Vector);

#endif
