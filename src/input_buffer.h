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
#ifndef INPUT_BUFFER_H_
#define INPUT_BUFFER_H_

#include "board.h"
#include <stdlib.h>

#define INPUT_BUFFER_LENGTH 2

typedef struct input_buffer_s Input_Buffer;

Input_Buffer *create_input_buffer (void);
void clear_buffer (Input_Buffer *);
void add_input (Input_Buffer *, Direction);
int input_left (Input_Buffer *);
Direction pop_input (Input_Buffer *);

#endif
