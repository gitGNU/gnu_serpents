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
#include "../src/board.h"

#include "check_board.h"

START_TEST (dir_to_vector_left_test)
{
  ck_assert_int_eq (-1, dir_to_vector (DIR_LEFT).x);
  ck_assert_int_eq (0, dir_to_vector (DIR_LEFT).y);
}
END_TEST

START_TEST (dir_to_vector_right_test)
{
  ck_assert_int_eq (1, dir_to_vector (DIR_RIGHT).x);
  ck_assert_int_eq (0, dir_to_vector (DIR_RIGHT).y);
}
END_TEST

START_TEST (dir_to_vector_up_test)
{
  ck_assert_int_eq (0, dir_to_vector (DIR_UP).x);
  ck_assert_int_eq (-1, dir_to_vector (DIR_UP).y);
}
END_TEST

START_TEST (dir_to_vector_down_test)
{
  ck_assert_int_eq (0, dir_to_vector (DIR_DOWN).x);
  ck_assert_int_eq (1, dir_to_vector (DIR_DOWN).y);
}
END_TEST

START_TEST (initial_board_test)
{
  Board *b = initialize_board (10, 10);
  int i, j;

  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      ck_assert (TILE_EMPTY == get_tile (b, i, j)->type);
}
END_TEST

START_TEST (add_vectors_positive_test)
{
  Board *b = initialize_board (10, 10);
  Vector v1 = {8, 2}, v2 = {1, 2};
  Vector result = add_vectors_on_board (*b, v1, v2);

  ck_assert_int_eq (9, result.x);
  ck_assert_int_eq (4, result.y);
}
END_TEST

START_TEST (add_vectors_negative_test)
{
  Board *b = initialize_board (10, 10);
  Vector v1 = {8, 2}, v2 = {-1, -2};
  Vector result = add_vectors_on_board(*b, v1, v2);

  ck_assert_int_eq (7, result.x);
  ck_assert_int_eq (0, result.y);
}
END_TEST

START_TEST (add_vectors_top_test)
{
  Board *b = initialize_board (10, 10);
  Vector v1 = {5, 0}, v2 = {0, -1};
  Vector result = add_vectors_on_board(*b, v1, v2);

  ck_assert_int_eq (9, result.y);
}
END_TEST

START_TEST (add_vectors_bottom_test)
{
  Board *b = initialize_board (10, 10);
  Vector v1 = {5, 9}, v2 = {0, 1};
  Vector result = add_vectors_on_board(*b, v1, v2);

  ck_assert_int_eq (0, result.y);
}
END_TEST

START_TEST (add_vectors_left_test)
{
  Board *b = initialize_board (10, 10);
  Vector v1 = {0, 5}, v2 = {-1, 0};
  Vector result = add_vectors_on_board(*b, v1, v2);

  ck_assert_int_eq (9, result.x);
}
END_TEST

START_TEST (add_vectors_right_test)
{
  Board *b = initialize_board (10, 10);
  Vector v1 = {9, 5}, v2 = {1, 0};
  Vector result = add_vectors_on_board(*b, v1, v2);

  ck_assert_int_eq (0, result.x);
}
END_TEST

START_TEST (add_food_initial_test)
{
  Board *b = initialize_board(10, 10);
  int i, j;
  add_food (b, 0);

  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      if (get_tile (b, i, j)->type == TILE_FOOD)
        ck_assert (get_tile (b, i, j)->id == 0);
}
END_TEST

START_TEST (add_food_full_test)
{
  Board *b = initialize_board (2, 2);

  add_food (b, 0);
  add_food (b, 0);
  add_food (b, 0);
  add_food (b, 0);
  add_food (b, 1);

  ck_assert (get_tile (b, 0, 0)->id == 0);
  ck_assert (get_tile (b, 0, 1)->id == 0);
  ck_assert (get_tile (b, 1, 0)->id == 0);
  ck_assert (get_tile (b, 1, 1)->id == 0);
}
END_TEST

START_TEST (initial_snake_test)
{
  Board *b = initialize_board (10, 10);
  initialize_snake (b, 0, 2, 2, 3, DIR_DOWN);

  ck_assert (get_tile (b, 2, 2)->type == TILE_SNAKE);
  ck_assert (get_tile (b, 2, 3)->type == TILE_SNAKE);
  ck_assert (get_tile (b, 2, 4)->type == TILE_SNAKE);
}
END_TEST

START_TEST (tile_from_head_test)
{
  Board *b = initialize_board (10, 10);
  Snake s = initialize_snake (b, 0, 2, 9, 3, DIR_UP);

  ck_assert (tile_from_head (b, &s, DIR_RIGHT).type == TILE_EMPTY);
}
END_TEST

START_TEST (move_snake_test)
{
  Board *b = initialize_board (10, 10);
  Snake s = initialize_snake (b, 0, 0, 1, 4, DIR_RIGHT);

  move_snake (b, &s, DIR_UP, 0);
  move_snake (b, &s, DIR_LEFT, 0);

  /* Shape of snake should be (x is empty, arrow is direction of snake):
     x x < ^
     x x > >
  */
  ck_assert (get_tile (b, 2, 1)->type == TILE_SNAKE);
  ck_assert (get_tile (b, 3, 1)->type == TILE_SNAKE);
  ck_assert (get_tile (b, 2, 0)->type == TILE_SNAKE);
  ck_assert (get_tile (b, 3, 0)->type == TILE_SNAKE);
}
END_TEST

START_TEST (change_from_up_test)
{
  ck_assert (!is_valid_direction_change (DIR_UP, DIR_UP));
  ck_assert (is_valid_direction_change (DIR_UP, DIR_RIGHT));
  ck_assert (is_valid_direction_change (DIR_UP, DIR_LEFT));
  ck_assert (!is_valid_direction_change (DIR_UP, DIR_DOWN));
}
END_TEST

START_TEST (change_from_right_test)
{
  ck_assert (is_valid_direction_change (DIR_RIGHT, DIR_UP));
  ck_assert (!is_valid_direction_change (DIR_RIGHT, DIR_RIGHT));
  ck_assert (!is_valid_direction_change (DIR_RIGHT, DIR_LEFT));
  ck_assert (is_valid_direction_change (DIR_RIGHT, DIR_DOWN));
}
END_TEST

START_TEST (change_from_left_test)
{
  ck_assert (is_valid_direction_change (DIR_LEFT, DIR_UP));
  ck_assert (!is_valid_direction_change (DIR_LEFT, DIR_RIGHT));
  ck_assert (!is_valid_direction_change (DIR_LEFT, DIR_LEFT));
  ck_assert (is_valid_direction_change (DIR_LEFT, DIR_DOWN));
}
END_TEST

START_TEST (change_from_down_test)
{
  ck_assert (!is_valid_direction_change (DIR_DOWN, DIR_UP));
  ck_assert (is_valid_direction_change (DIR_DOWN, DIR_RIGHT));
  ck_assert (is_valid_direction_change (DIR_DOWN, DIR_LEFT));
  ck_assert (!is_valid_direction_change (DIR_DOWN, DIR_DOWN));
}
END_TEST



Suite *
board_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("board");
  tc_core = tcase_create("core");

  tcase_add_test (tc_core, dir_to_vector_left_test);
  tcase_add_test (tc_core, dir_to_vector_right_test);
  tcase_add_test (tc_core, dir_to_vector_up_test);
  tcase_add_test (tc_core, dir_to_vector_down_test);
  tcase_add_test (tc_core, initial_board_test);
  tcase_add_test (tc_core, add_vectors_positive_test);
  tcase_add_test (tc_core, add_vectors_negative_test);
  tcase_add_test (tc_core, add_vectors_top_test);
  tcase_add_test (tc_core, add_vectors_bottom_test);
  tcase_add_test (tc_core, add_vectors_left_test);
  tcase_add_test (tc_core, add_vectors_right_test);
  tcase_add_test (tc_core, add_food_initial_test);
  tcase_add_test (tc_core, add_food_full_test);
  tcase_add_test (tc_core, initial_snake_test);
  tcase_add_test (tc_core, tile_from_head_test);
  tcase_add_test (tc_core, move_snake_test);
  tcase_add_test (tc_core, change_from_up_test);
  tcase_add_test (tc_core, change_from_right_test);
  tcase_add_test (tc_core, change_from_left_test);
  tcase_add_test (tc_core, change_from_down_test);

  suite_add_tcase(s, tc_core);

  return s;
}
