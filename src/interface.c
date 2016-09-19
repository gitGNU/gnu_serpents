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
#include <math.h>

#include "interface.h"

void
draw (Game_State *state)
{
  int i, x, y;

  char *score_text = itoa (state->score);
  SDL_Color score_color = { 255, 255, 255 };

  set_color (state, state->background_color);
  SDL_RenderClear (state->renderer);

  for (i = 0; i < state->number_of_snakes; i++)
    draw_snake (state, i);

  for (y = 0; y < state->board->height; y++)
    for (x = 0; x < state->board->width; x++)
      if (get_tile (state->board, x, y)->type
          == TILE_FOOD)
        draw_food (state, get_tile (state->board, x, y)->id,
                   x, y);

  draw_text (state, state->score_font, score_text,
             score_color, 230, 8, -3, 0);

  free (score_text);

  SDL_RenderPresent (state->renderer);
}

static char *
itoa (int n)
{
  int base = 10;
  int text_len = (n ? (log (n) / log (base)) + 1 : 1) + 1;
  char *text = (char *) malloc (sizeof (char) * text_len);

  snprintf (text, text_len, "%d", n);

  return text;
}

static void
draw_text (Game_State *state, TTF_Font *font, char *text,
           SDL_Color color, int alpha, int x, int y, int is_centered)
{
  SDL_Surface *surf = TTF_RenderText_Blended (font, text, color);
  SDL_Texture *tex =
    SDL_CreateTextureFromSurface (state->renderer, surf);
  SDL_Rect rect;

  TTF_SizeText (font, text, &rect.w, &rect.h);

  if (is_centered)
    {
      rect.x = x - (rect.w / 2);
      rect.y = y - (rect.h / 2);
    }
  else
    {
      rect.x = x;
      rect.y = y;
    }

  SDL_SetTextureAlphaMod (tex, alpha);
  SDL_RenderCopy (state->renderer, tex, NULL, &rect);

  SDL_DestroyTexture (tex);
  SDL_FreeSurface (surf);
}

static void
draw_overlay (Game_State *state, SDL_Color color, int alpha)
{
  SDL_SetRenderDrawColor (state->renderer,
                          color.r, color.g, color.b, alpha);
  SDL_SetRenderDrawBlendMode (state->renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect (state->renderer, NULL);
}

int
draw_game_over (Game_State *state)
{
  char *game_over_text = "You scored: ",
    *score_text = itoa (state->score),
    *full_text = (char *)
      malloc (sizeof (char) *
              (strlen (game_over_text) + strlen (score_text) + 1));
  SDL_Color white = { 255, 255, 255 },
    black = { 0, 0, 0 };
  int x = state->width / 2,
    y = state->height / 2;
  SDL_Event event;

  strcpy (full_text, game_over_text);
  strcat (full_text, score_text);

  draw (state);
  draw_overlay (state, black, 150);
  
  draw_text (state, state->score_font, full_text, white,
             255, x, y, 1);

  SDL_RenderPresent (state->renderer);

  free (score_text);
  free (full_text);

  while (1)
    {
      while (SDL_PollEvent (&event))
        if (event.type == SDL_QUIT)
          return 0;
        else if (event.type == SDL_KEYDOWN)
          switch (event.key.keysym.sym)
            {
            case SDLK_n:
            case SDLK_q:
              return 0;
            case SDLK_SPACE:
            case SDLK_RETURN:
            case SDLK_y:
              return 1;
            }

      SDL_Delay (100);
    }
}


static void
draw_snake (Game_State *state, char id)
{
  Vector pos = state->snakes[id].tail,
    head_pos = state->snakes[id].head;
  Direction prev_dir = get_tile (state->board,
                                 pos.x, pos.y)->dir;
  RGBA_Color col = state->current_snake == id
    ? state->snake_colors[id]
    : scale_color (state->snake_colors[id], 0.6);

  set_color (state, col);

  draw_tail (state, pos, prev_dir);

  pos = add_vectors_on_board (*state->board, pos, dir_to_vector (prev_dir));
  while (!(pos.x == head_pos.x && pos.y == head_pos.y))
    {
      Direction new_dir =
        get_tile (state->board, pos.x, pos.y)->dir;
      draw_snake_tile (state, pos, prev_dir, new_dir);
      prev_dir = new_dir;
      pos = add_vectors_on_board (*state->board, pos, dir_to_vector (new_dir));
    }

  set_color (state, scale_color (col, 1.5));
  draw_tail (state, pos, reverse_dir (prev_dir));
}

static void
draw_tail (Game_State *state, Vector pos, Direction dir)
{
  int tile_size = state->tile_size,
    snake_padding = state->snake_padding;
  SDL_Rect rect = {pos.x * tile_size, pos.y * tile_size,
                   tile_size, tile_size};

  switch (dir)
    {
    case DIR_UP:
      rect.x += snake_padding;
      rect.w -= snake_padding * 2;
      rect.h -= snake_padding;
      break;
    case DIR_DOWN:
      rect.x += snake_padding;
      rect.w -= snake_padding * 2;
      rect.y += snake_padding;
      rect.h -= snake_padding;
      break;
    case DIR_LEFT:
      rect.y += snake_padding;
      rect.h -= snake_padding * 2;
      rect.w -= snake_padding;
      break;
    case DIR_RIGHT:
      rect.y += snake_padding;
      rect.h -= snake_padding * 2;
      rect.x += snake_padding;
      rect.w -= snake_padding;
      break;
    }

  SDL_RenderFillRect (state->renderer, &rect);
}

static void
draw_snake_tile (Game_State *state, Vector pos,
                 Direction dir1, Direction dir2)
{
  int tile_size = state->tile_size,
    snake_padding = state->snake_padding;
  SDL_Rect
    rect1 = { pos.x * tile_size + snake_padding,
              pos.y * tile_size + snake_padding,
              tile_size - 2 * snake_padding,
              tile_size - 2 * snake_padding },
    rect2 = { pos.x * tile_size + snake_padding,
              pos.y * tile_size + snake_padding,
              tile_size - 2 * snake_padding,
              tile_size - 2 * snake_padding };

    switch (dir1)
      {
      case DIR_DOWN:
        rect1.y -= snake_padding;
        rect1.h += snake_padding;
        break;
      case DIR_UP:
        rect1.h += snake_padding;
        break;
      case DIR_RIGHT:
        rect1.x -= snake_padding;
        rect1.w += snake_padding;
        break;
      case DIR_LEFT:
        rect1.w += snake_padding;
      }

    switch (dir2)
      {
      case DIR_UP:
        rect2.y -= snake_padding;
        rect2.h += snake_padding;
        break;
      case DIR_DOWN:
        rect2.h += snake_padding;
        break;
      case DIR_LEFT:
        rect2.x -= snake_padding;
        rect2.w += snake_padding;
        break;
      case DIR_RIGHT:
        rect2.w += snake_padding;
      }

    SDL_RenderFillRect (state->renderer, &rect1);
    SDL_RenderFillRect (state->renderer, &rect2);
}

static void
draw_food (Game_State *state, char id, int x, int y)
{
  int tile_size = state->tile_size,
    food_padding = state->food_padding;
  SDL_Rect food = { x * tile_size + food_padding,
                    y * tile_size + food_padding,
                    tile_size - food_padding * 2,
                    tile_size - food_padding * 2 };
  set_color (state, scale_color(state->snake_colors[id], 1.5));
  SDL_RenderFillRect (state->renderer, &food);
}

static void
set_color (Game_State *state, RGBA_Color col)
{
  SDL_SetRenderDrawColor
    (state->renderer, col.r, col.g, col.b, col.a);
}

static Direction
reverse_dir (Direction dir)
{
  switch (dir)
    {
    case DIR_UP:
      return DIR_DOWN;
    case DIR_DOWN:
      return DIR_UP;
    case DIR_LEFT:
      return DIR_RIGHT;
    case DIR_RIGHT:
      return DIR_LEFT;
    }
}
