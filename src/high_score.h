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
#ifndef HIGH_SCORE_H_
#define HIGH_SCORE_H_

#include <stdio.h>
#include "config.h"

typedef struct
{
  int score;
  char *date;
} High_Score;

High_Score *initial_high_scores (void);
High_Score *read_high_scores (FILE *);
void write_high_scores (FILE *, High_Score *);
void free_high_scores (High_Score *);
void add_score (High_Score *, int);

#endif
