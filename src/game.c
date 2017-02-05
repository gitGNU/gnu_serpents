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
#include <time.h>

#include "game.h"
#include "config.h"

static Game_State *initialize_game (Game_Settings);
static void initialize_SDL (Game_State *, int, int);
static void game_loop (Game_State *);
static int step_game (Game_State *);
static int move (Game_State *);

static void get_all_input (Game_State *);
static Snake *current_snake (Game_State *);
static Direction pop_next_direction (Game_State *);
static Direction current_direction (Game_State *);
static void delay (Game_State *);

RGBA_Color default_snake_colors[3] =
    { { 255, 80, 80, 255 },
      { 80, 80, 255, 255 },
      { 60, 255, 60, 255 } };

Game_Settings default_game_settings =
  {
    32,                         /* tile_size */
    1,                          /* snake_padding */
    6,                          /* food_padding */
    16,                         /* board_width */
    12,                         /* board_height */
    3,                          /* number_of_snakes */
    { 20, 20, 20, 255 },           /* background_color */
    default_snake_colors        /* snake_colors */
  };

void
run_game (Game_Settings settings)
{
  Game_State *state = initialize_game (settings);
  game_loop (state);
}

static Game_State *
initialize_game (Game_Settings settings)
{
  int id;
  Game_State *state = malloc (sizeof (Game_State));
  Board *board = initialize_board (settings.board_width,
                                   settings.board_height);
  Snake *snakes = calloc (settings.number_of_snakes, sizeof (Snake));
  if (!(state && board && snakes))
    exit (2);                   /* FIXME */

  srand (time (NULL));

  for (id = 0; id < settings.number_of_snakes; id++)
    snakes[id] = initialize_snake (board, id, 0, id, 5, DIR_RIGHT);

  for (id = 0; id < settings.number_of_snakes; id++)
    add_food (board, id);

  state->board = board;

  state->number_of_snakes = settings.number_of_snakes;
  state->current_snake = 0;
  state->snakes = snakes;

  state->tile_size = settings.tile_size;
  state->width = settings.board_width * settings.tile_size;
  state->height = settings.board_height * settings.tile_size;
  state->snake_padding = settings.snake_padding;
  state->food_padding = settings.food_padding;
  state->background_color = settings.background_color;
  state->snake_colors = settings.snake_colors;

  state->input_buffer = create_input_buffer ();
  if (!state->input_buffer)
    exit (2);                   /* FIXME */

  state->score = 0;

  initialize_SDL (state, state->width, state->height);

  state->score_font = TTF_OpenFont (FONTS_PATH "/FreeSansBold.ttf", 32);

  if (!state->score_font)
    {
      printf ("Font file not found at '%s'\n",
              FONTS_PATH "/FreeSansBold.ttf");
      exit (0);
    }

  return state;
}

static void
initialize_SDL (Game_State *state, int width, int height)
{
  SDL_Init (SDL_INIT_VIDEO);

  state->window = SDL_CreateWindow
    (PACKAGE_NAME,
     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
     width, height,
     SDL_WINDOW_OPENGL);

  if (TTF_Init () < 0)
    {
      printf ("Unable to load SDL_ttf!");
      exit (1);
    }

  state->renderer = SDL_CreateRenderer (state->window, -1, 0);
}

static Game_State *
play_again (Game_State *state)
{
  int id;
  Board *new_board = initialize_board (state->board->width,
                                   state->board->height);

  free (state->board->data);
  free (state->board);
  free (state->input_buffer);

  state->board = new_board;

  for (id = 0; id < state->number_of_snakes; id++)
    state->snakes[id] =
      initialize_snake (state->board, id, 0, id, 5, DIR_RIGHT);

  for (id = 0; id < state->number_of_snakes; id++)
    add_food (state->board, id);

  state->input_buffer = create_input_buffer ();
  state->current_snake = 0;
  state->score = 0;
  state->time_to_delay = 0;

  return state;
}

static void
game_loop (Game_State *state)
{
  int game_over = 0;

  while (1)
    {
      state->time_to_delay = 200;
      game_over = step_game (state);
      draw (state);
      if (game_over)
        {
          if (draw_game_over (state))
            state = play_again (state);
          else
            exit (0);
        }
      delay (state);
    }
}

static int
step_game (Game_State *state)
{
  get_all_input (state);

  return move (state);
}

static int
move (Game_State *state)
{
  Direction next_dir = pop_next_direction (state);
  Vector new_pos, tail_pos;
  Tile next_tile =
    tile_from_head (state->board, current_snake (state), next_dir);
  char id;

  switch (next_tile.type)
    {
    case TILE_SNAKE:
      new_pos = add_vectors_on_board (*state->board,
                                      current_snake (state)->head,
                                      dir_to_vector (next_dir));
      tail_pos = current_snake (state)->tail;

      if (new_pos.x == tail_pos.x && new_pos.y == tail_pos.y)
        move_snake (state->board, current_snake (state), next_dir, 0);
      else
        return 1;

      break;
    case TILE_EMPTY:
      move_snake (state->board, current_snake (state), next_dir, 0);
      break;
    case TILE_FOOD:
      id = next_tile.id;

      if (state->current_snake != id)
        {
          clear_buffer (state->input_buffer);
          state->time_to_delay += 600;
        }

      move_snake (state->board, current_snake (state), next_dir, 1);
      add_food (state->board, rand () % state->number_of_snakes);
      state->current_snake = id;
      state->score++;
      break;
    }

  return 0;
}



static void
get_all_input (Game_State *state)
{
  SDL_Event event;

  while (SDL_PollEvent (&event))
    {
      if (event.type == SDL_QUIT)
        exit (0);
      else if (event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym)
          {
          case SDLK_UP:
          case SDLK_w:
            add_input (state->input_buffer, DIR_UP);
            break;
          case SDLK_DOWN:
          case SDLK_s:
            add_input (state->input_buffer, DIR_DOWN);
            break;
          case SDLK_LEFT:
          case SDLK_a:
            add_input (state->input_buffer, DIR_LEFT);
            break;
          case SDLK_RIGHT:
          case SDLK_d:
            add_input (state->input_buffer, DIR_RIGHT);
            break;
          case SDLK_p:
            SDL_Delay (5000);
            break;
          case SDLK_q:
            exit (0);
          }
    }
}

static Snake *
current_snake (Game_State *state)
{
  return state->snakes + state->current_snake;
}

static Direction
pop_next_direction (Game_State *state)
{
  Direction cur_dir = current_direction (state);

  while (input_left (state->input_buffer))
    {
      Direction input_dir = pop_input (state->input_buffer);
      if (is_valid_direction_change (cur_dir, input_dir))
        return input_dir;
    }

  return cur_dir;
}

static Direction
current_direction (Game_State *state)
{
  return get_tile (state->board, current_snake (state)->head.x,
                   current_snake (state)->head.y)->dir;
}

static void
delay (Game_State *state)
{
  SDL_Delay (state->time_to_delay);
  state->time_to_delay = 0;
}
