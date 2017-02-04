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
#include "input_buffer.h"

struct input_buffer_s
{
  int remaining;
  Direction buffer[INPUT_BUFFER_LENGTH];
};

Input_Buffer *
create_input_buffer ()
{
  Input_Buffer *buf = malloc (sizeof (Input_Buffer));

  if (!buf)
    return NULL;

  buf->remaining = 0;

  return buf;
}

void
clear_buffer (Input_Buffer *buf)
{
  buf->remaining = 0;
}

void
add_input (Input_Buffer *buf, Direction dir)
{
  if (buf->remaining < INPUT_BUFFER_LENGTH)
    buf->buffer[buf->remaining++] = dir;
  else
    {
      int i;

      for (i = 0; i < INPUT_BUFFER_LENGTH - 1; i++)
        buf->buffer[i] = buf->buffer[i+1];

      buf->buffer[INPUT_BUFFER_LENGTH - 1] = dir;
    }
}

int
input_left (Input_Buffer *buf)
{
  return buf->remaining > 0;
}

Direction
pop_input (Input_Buffer *buf)
{
  Direction popped = buf->buffer[0];
  int i;

  for (i = 0; i < INPUT_BUFFER_LENGTH - 1; i++)
    buf->buffer[i] = buf->buffer[i+1];

  buf->remaining--;

  return popped;
}
