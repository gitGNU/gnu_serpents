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
#include <stdlib.h>
#include "board.h"

static void set_tile (Board *, int, int, char, Tile_Type, Direction);
static int dir_x (Direction);
static int dir_y (Direction);
static Vector add_vectors (Vector, Vector);
static Vector on_board (Board, Vector);

Board *
initialize_board (int width, int height)
{
  Tile *board_data = calloc (width * height, sizeof (Tile));
  Board *board = malloc (sizeof (Board));
  if (!board_data)
    return NULL;
  if (!board)
    return NULL;

  board->width = width;
  board->height = height;
  board->data = board_data;
  return board;
}

Snake
initialize_snake (Board *board, char id,
                  int x, int y, int length, Direction dir)
{
  Snake snake;
  Vector point = { x, y };
  snake.id = id;
  snake.tail.x = x;
  snake.tail.y = y;

  for (; length > 1; length--)
    {
      set_tile (board, point.x, point.y, id, TILE_SNAKE, dir);
      point = add_vectors_on_board (*board, point,
                                    dir_to_vector (dir));
    }

  set_tile (board, point.x, point.y, id, TILE_SNAKE, dir);
  snake.head = point;

  return snake;
}

Tile
tile_from_head (Board *board, Snake *snake, Direction dir)
{
  Vector point =
    add_vectors_on_board (*board, snake->head, dir_to_vector (dir));

  return *get_tile (board, point.x, point.y);
}

void
move_snake (Board *board, Snake *snake, Direction dir, int keep_tail)
{
  Vector new_head =
    add_vectors_on_board (*board, snake->head, dir_to_vector (dir));

  if (!keep_tail)
    {
      Direction tail_dir =
        get_tile (board, snake->tail.x, snake->tail.y)->dir;
      set_tile (board, snake->tail.x, snake->tail.y, 0,
                TILE_EMPTY, 0);

      snake->tail = add_vectors_on_board (*board, snake->tail,
                                         dir_to_vector (tail_dir));
    }

  set_tile (board, snake->head.x, snake->head.y,
            snake->id, TILE_SNAKE, dir);
  set_tile (board, new_head.x, new_head.y,
            snake->id, TILE_SNAKE, dir);
  snake->head = new_head;
}

void
add_food (Board *board, char id)
{
  int i,
    n_empty = 0,
    length = board->width * board->height,
    random_number;
  Tile *board_data = board->data;

  for (i = 0; i < length; i++)
    if (board_data[i].type == TILE_EMPTY)
      n_empty++;

  random_number = rand () % n_empty;

  for (i = 0; i < length; i++)
    {
      if (board_data[i].type == TILE_EMPTY)
        {
          if (random_number == 0)
            {
              board_data[i].id = id;
              board_data[i].type = TILE_FOOD;
              return;
            }
          random_number--;
        }
    }
}

Tile *
get_tile (Board *board, int x, int y)
{
  return board->data + (x + y * board->width);
}

Vector
dir_to_vector (Direction dir)
{
  Vector v = { dir_x (dir), dir_y (dir) };
  return v;
}

Vector
add_vectors_on_board (Board board, Vector v1, Vector v2)
{
  return on_board (board, add_vectors (v1, v2));
}



static void
set_tile (Board *board, int x, int y,
          char id, Tile_Type type, Direction dir)
{
  Tile *tile = board->data + (x + board->width * y);

  tile->id = id;
  tile->type = type;
  tile->dir = dir;
}

static int
dir_x (Direction dir)
{
  switch (dir)
    {
    case DIR_LEFT:
      return -1;
    case DIR_RIGHT:
      return 1;
    default:
      return 0;
    }
}

static int
dir_y (Direction dir)
{
  switch (dir)
    {
    case DIR_UP:
      return -1;
    case DIR_DOWN:
      return 1;
    default:
      return 0;
    }
}

static Vector
add_vectors (Vector v1, Vector v2)
{
  v1.x += v2.x;
  v1.y += v2.y;
  return v1;
}

static Vector
on_board (Board board, Vector v)
{
  v.x = ((v.x % board.width) + board.width) % board.width;
  v.y = ((v.y % board.height) + board.height) % board.height;
  return v;
}
