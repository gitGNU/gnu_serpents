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
#include "../src/color.h"

#include "check_color.h"

START_TEST (scale_up_test)
{
  RGBA_Color test = {0, 50, 210, 255};

  ck_assert_uint_eq (127, scale_color (test, 2).r);
  ck_assert_uint_eq (152, scale_color (test, 2).g);
  ck_assert_uint_eq (232, scale_color (test, 2).b);
  ck_assert_uint_eq (255, scale_color (test, 2).a);
}
END_TEST

START_TEST (scale_down_test)
{
  RGBA_Color test = {0, 50, 210, 255};

  ck_assert_uint_eq (0, scale_color (test, 0.5).r);
  ck_assert_uint_eq (25, scale_color (test, 0.5).g);
  ck_assert_uint_eq (105, scale_color (test, 0.5).b);
  ck_assert_uint_eq (255, scale_color (test, 0.5).a);
}
END_TEST


Suite *
color_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("color");
  tc_core = tcase_create("core");

  tcase_add_test (tc_core, scale_up_test);
  tcase_add_test (tc_core, scale_down_test);

  suite_add_tcase(s, tc_core);

  return s;
}
