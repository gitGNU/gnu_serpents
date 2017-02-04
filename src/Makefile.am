## Copyright 2016 Jochem Raat <jchmrt@riseup.net>
##
## This file is part of serpents.
##
## serpents is free software: you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free
## Software Foundation, either version 3 of the License, or (at your
## option) any later version.
##
## serpents is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License
## along with serpents.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

bin_PROGRAMS = serpents
serpents_SOURCES = main.c


serpents_CFLAGS = $(SDL_CFLAGS) $(TTF_CFLAGS) \
                  -DFONTS_PATH=\"$(fontsdir)\"

serpents_LDADD = $(top_builddir)/src/libserpents.a \
	$(SDL_LIBS) $(TTF_LIBS) -lm

# We create a static library, so that we can unit test the functions
# with check.
noinst_LIBRARIES = libserpents.a
libserpents_a_SOURCES = board.h board.c \
	game.h game.c \
	color.h color.c \
	input_buffer.h input_buffer.c \
	interface.h interface.c \
	state.h
libserpents_a_CFLAGS = $(SDL_CFLAGS) $(TTF_CFLAGS) \
                  -DFONTS_PATH=\"$(fontsdir)\"
