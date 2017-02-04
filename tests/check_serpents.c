#include <stdlib.h>
#include <check.h>
#include "../src/input_buffer.h"
#include "../src/board.h"

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
serpents_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("serpents");
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

int
main (void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = serpents_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
