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
#include <stdlib.h>

#include "high_score.h"

/* Date string of the form: YYYY-MM-DD\0 */
#define DATE_STR_SIZE 11

/**
 * Return a new string containing the current date.
 *
 * It is formatted according to the ISO 8601 date format
 * (YYYY-MM-DD). This also means that it has a maximum size of
 * DATE_STR_SIZE, at least until the year 10000.
 */
static char *
current_date_string ()
{
  time_t now = time (NULL);
  struct tm *local = localtime (&now);
  char *str = (char *) malloc (sizeof (char) * DATE_STR_SIZE);

  strftime (str, DATE_STR_SIZE, "%F", local);

  return str;
}

/**
 * Create a new High_Score.
 *
 * It will have SCORE as its score and the current date as the date.
 */
static High_Score
new_high_score (int score)
{
  High_Score hs;

  hs.date = current_date_string ();
  hs.score = score;

  return hs;
}

High_Score *
initial_high_scores ()
{
  High_Score *high_scores = (High_Score *)
    calloc (NUMBER_OF_HIGH_SCORES, sizeof (High_Score));
  int i;

  for (i = 0; i < NUMBER_OF_HIGH_SCORES; i++)
    high_scores[i].score = -1;

  return high_scores;
}

High_Score *
read_high_scores (FILE *f)
{
  High_Score *high_scores = initial_high_scores ();
  int i = 0,
    score;
  char *date = (char *) malloc (sizeof (char) * DATE_STR_SIZE);

  while (fscanf (f, "%u %s\n", &score, date) != EOF)
    {
      high_scores[i].score = score;
      high_scores[i].date = date;

      date = (char *) malloc (sizeof (char) * DATE_STR_SIZE);
      i++;
    }
  free (date);

  return high_scores;
}

void
write_high_scores (FILE *f, High_Score *high_scores)
{
  int i;

  for (i = 0; i < NUMBER_OF_HIGH_SCORES
         && high_scores[i].score >= 0; i++)
    {
      fprintf (f, "%d %s\n",
               high_scores[i].score, high_scores[i].date);
    }
}

void
free_high_scores (High_Score *high_scores)
{
  int i;

  for (i = 0; i < NUMBER_OF_HIGH_SCORES; i++)
    {
      if (high_scores[i].date)
        free (high_scores[i].date);
    }

  free (high_scores);
}

void
add_score (High_Score *high_scores, int score)
{
  High_Score new = new_high_score (score);
  int i;

  for (i = 0; i < NUMBER_OF_HIGH_SCORES; i++)
    {
      if (score > high_scores[i].score)
        break;
    }

  for (; i < NUMBER_OF_HIGH_SCORES; i++)
    {
      High_Score tmp = high_scores[i];
      high_scores[i] = new;
      new = tmp;
    }

  free (new.date);
}
