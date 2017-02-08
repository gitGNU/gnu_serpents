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
#include "../src/high_score.h"

#include "check_high_score.h"

START_TEST (initial_high_scores_test)
{
  High_Score *hs = initial_high_scores ();
  int i;

  for (i = 0; i < NUMBER_OF_HIGH_SCORES; i++)
    {
      ck_assert_int_eq (hs[i].score, -1);
      ck_assert_ptr_eq (hs[i].date, NULL);
    }

  free_high_scores (hs);
}
END_TEST

START_TEST (add_zero_score_test)
{
  High_Score *hs = initial_high_scores ();

  add_score (hs, 0);

  ck_assert_int_eq (hs[0].score, 0);
  ck_assert_int_eq (strlen (hs[0].date), 10);

  free_high_scores (hs);
}
END_TEST

START_TEST (add_normal_score_test)
{
  High_Score *hs = initial_high_scores ();
  
  add_score (hs, 50);

  ck_assert_int_eq (hs[0].score, 50);

  free_high_scores (hs);
}
END_TEST

START_TEST (add_multiple_scores_test)
{
  High_Score *hs = initial_high_scores ();

  add_score (hs, 30);
  add_score (hs, 0);
  add_score (hs, 40);
  add_score (hs, 20);
  add_score (hs, 10);
  add_score (hs, 50);

  ck_assert_int_eq (hs[0].score, 50);
  ck_assert_int_eq (hs[1].score, 40);
  ck_assert_int_eq (hs[2].score, 30);
  ck_assert_int_eq (hs[3].score, 20);
  ck_assert_int_eq (hs[4].score, 10);
  ck_assert_int_eq (hs[5].score, 0);

  ck_assert_int_eq (hs[6].score, -1);
  ck_assert_int_eq (hs[7].score, -1);
  ck_assert_int_eq (hs[8].score, -1);
  ck_assert_int_eq (hs[9].score, -1);

  free_high_scores (hs);
}
END_TEST

START_TEST (add_multiple_same_test)
{
  High_Score *hs = initial_high_scores ();

  add_score (hs, 0);
  add_score (hs, 0);
  add_score (hs, 10);
  add_score (hs, 30);
  add_score (hs, 10);
  add_score (hs, 20);
  add_score (hs, 30);

  ck_assert_int_eq (hs[0].score, 30);
  ck_assert_int_eq (hs[1].score, 30);
  ck_assert_int_eq (hs[2].score, 20);
  ck_assert_int_eq (hs[3].score, 10);
  ck_assert_int_eq (hs[4].score, 10);
  ck_assert_int_eq (hs[5].score, 0);
  ck_assert_int_eq (hs[6].score, 0);

  ck_assert_int_eq (hs[7].score, -1);
  ck_assert_int_eq (hs[8].score, -1);
  ck_assert_int_eq (hs[9].score, -1);

  free_high_scores (hs);
}
END_TEST

START_TEST (add_more_than_ten_test)
{
  High_Score *hs = initial_high_scores ();

  add_score (hs, 35);
  add_score (hs, 0);
  add_score (hs, 15);
  add_score (hs, 25);
  add_score (hs, 30);
  add_score (hs, 20);
  add_score (hs, 5);
  add_score (hs, 30);
  add_score (hs, 15);
  add_score (hs, 40);
  add_score (hs, 45);
  add_score (hs, 10);
  add_score (hs, 50);
  add_score (hs, 15);

  ck_assert_int_eq (hs[0].score, 50);
  ck_assert_int_eq (hs[1].score, 45);
  ck_assert_int_eq (hs[2].score, 40);
  ck_assert_int_eq (hs[3].score, 35);
  ck_assert_int_eq (hs[4].score, 30);
  ck_assert_int_eq (hs[5].score, 30);
  ck_assert_int_eq (hs[6].score, 25);
  ck_assert_int_eq (hs[7].score, 20);
  ck_assert_int_eq (hs[8].score, 15);
  ck_assert_int_eq (hs[9].score, 15);

  free_high_scores (hs);
}
END_TEST

START_TEST (write_read_less_than_ten_test)
{
  High_Score *old = initial_high_scores (), *new;
  FILE *tmp = tmpfile ();
  int i;

  add_score (old, 30);
  add_score (old, 0);
  add_score (old, 10);
  add_score (old, 20);

  write_high_scores (tmp, old);

  fseek (tmp, 0, SEEK_SET);
  new = read_high_scores (tmp);

  for (i = 0; i < NUMBER_OF_HIGH_SCORES; i++)
    {
      ck_assert_int_eq (old[i].score, new[i].score);

      if (old[i].date != NULL && new[i].date != NULL)
        ck_assert_str_eq (old[i].date, new[i].date);
      else
        ck_assert_ptr_eq (old[i].date, new[i].date);
    }

  free_high_scores (old);
  free_high_scores (new);
  fclose (tmp);
}
END_TEST

START_TEST (write_read_more_than_ten_test)
{
  High_Score *old = initial_high_scores (), *new;
  FILE *tmp = tmpfile ();
  int i;

  add_score (old, 35);
  add_score (old, 0);
  add_score (old, 15);
  add_score (old, 25);
  add_score (old, 30);
  add_score (old, 20);
  add_score (old, 5);
  add_score (old, 30);
  add_score (old, 15);
  add_score (old, 40);
  add_score (old, 45);
  add_score (old, 10);
  add_score (old, 50);
  add_score (old, 15);

  write_high_scores (tmp, old);

  fseek (tmp, 0, SEEK_SET);
  new = read_high_scores (tmp);

  for (i = 0; i < NUMBER_OF_HIGH_SCORES; i++)
    {
      ck_assert_int_eq (old[i].score, new[i].score);

      if (old[i].date != NULL && new[i].date != NULL)
        ck_assert_str_eq (old[i].date, new[i].date);
      else
        ck_assert_ptr_eq (old[i].date, new[i].date);
    }

  free_high_scores (old);
  free_high_scores (new);
  fclose (tmp);
}
END_TEST


Suite *
high_score_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("high_score");
  tc_core = tcase_create("core");

  tcase_add_test (tc_core, initial_high_scores_test);
  tcase_add_test (tc_core, add_zero_score_test);
  tcase_add_test (tc_core, add_normal_score_test);
  tcase_add_test (tc_core, add_multiple_scores_test);
  tcase_add_test (tc_core, add_multiple_same_test);
  tcase_add_test (tc_core, add_more_than_ten_test);
  tcase_add_test (tc_core, write_read_less_than_ten_test);
  tcase_add_test (tc_core, write_read_more_than_ten_test);

  suite_add_tcase(s, tc_core);

  return s;
}
