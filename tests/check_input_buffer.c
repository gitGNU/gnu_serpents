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
#include "../src/input_buffer.h"
#include "../src/board.h"

#include "check_input_buffer.h"

START_TEST (initial_buffer_empty_test)
{
  Input_Buffer *buf = create_input_buffer ();
  ck_assert_msg (!input_left (buf));
}
END_TEST

START_TEST (buffer_add_input_test)
{
  Input_Buffer *buf = create_input_buffer ();
  add_input (buf, DIR_UP);
  ck_assert (input_left (buf));
}
END_TEST

START_TEST (buffer_pop_input_test)
{
  Input_Buffer *buf = create_input_buffer ();
  add_input (buf, DIR_UP);
  ck_assert (pop_input (buf) == DIR_UP);
}
END_TEST

START_TEST (buffer_last_pop_test)
{
  Input_Buffer *buf = create_input_buffer ();
  add_input (buf, DIR_UP);
  pop_input (buf);
  ck_assert (!input_left (buf));
}
END_TEST

START_TEST (buffer_clear_test)
{
  Input_Buffer *buf = create_input_buffer ();
  add_input (buf, DIR_UP);
  clear_buffer (buf);
  ck_assert (!input_left (buf));
}
END_TEST

START_TEST (buffer_more_than_size_test)
{
  Input_Buffer *buf = create_input_buffer ();
  add_input (buf, DIR_UP);
  add_input (buf, DIR_LEFT);
  add_input (buf, DIR_RIGHT);
  ck_assert (pop_input (buf) == DIR_LEFT);
  ck_assert (pop_input (buf) == DIR_RIGHT);
  ck_assert (!input_left (buf));
}
END_TEST


Suite *
input_buffer_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("input_buffer");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, initial_buffer_empty_test);
  tcase_add_test(tc_core, buffer_add_input_test);
  tcase_add_test(tc_core, buffer_pop_input_test);
  tcase_add_test(tc_core, buffer_last_pop_test);
  tcase_add_test(tc_core, buffer_clear_test);
  tcase_add_test(tc_core, buffer_more_than_size_test);

  suite_add_tcase(s, tc_core);

  return s;
}
