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
#include <getopt.h>

#include "config.h"
#include "game.h"

void
version ()
{
 printf
    (PACKAGE_STRING "\n"
     COPYRIGHT_STRING "\n"
     "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
     "This is free software: you are free to change and redistribute it.\n"
     "There is NO WARRANTY, to the extent permitted by law.\n");
}

void
help ()
{
  printf
    (PACKAGE_STRING "\n"
     COPYRIGHT_STRING "\n"
     "\n"
     "Serpents is a snake-like game where you control 3 serpents.\n"
     "Use WASD or the arrow keys to control your serpent and Q to quit.\n"
     "\n"
     "Usage: serpents\n"
     "\n");
  printf
    ("  -v, --version           Output version information and exit\n"
     "  -h, --help              Display this help and exit\n"
     "  -s, --tile-size=SIZE    Set the tile size to SIZE\n"
     "\n");
}

int
main (int argc, char **argv)
{
  struct option long_options[] =
    {
      {"version", no_argument, NULL, 'v'},
      {"help", no_argument, NULL, 'h'},
      {"tile-size", required_argument, NULL, 's'},
      {0, 0, 0, 0}
    };
  int c, option_index = 0;
  Game_Settings settings = default_game_settings;

  while ((c = getopt_long (argc, argv, "hvs:",
                           long_options, &option_index))
         != -1)
    {
      switch (c)
        {
        case 0:
          break;
        case 'v':
          version ();
          return 0;
        case 'h':
          help ();
          return 0;
        case 's':
          settings.tile_size = atoi (optarg);
          if (settings.tile_size < 7)
            {
              printf ("Tile size should be greater than 7.\n");
              return 1;
            }
          settings.snake_padding = settings.tile_size < 32
            ? 1 : settings.tile_size / 32;
          settings.food_padding = settings.tile_size < 10
            ? 2 : settings.tile_size / 5;
          break;
        }
    }

  run_game (settings);
}
