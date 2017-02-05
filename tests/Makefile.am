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

TESTS = check_serpents
check_PROGRAMS = check_serpents
check_serpents_SOURCES = check_serpents.c \
	check_input_buffer.c check_input_buffer.h \
	check_board.c check_board.h \
	check_color.c check_color.h \
	$(top_builddir)/src/input_buffer.h

check_serpents_CFLAGS = @CHECK_CFLAGS@
check_serpents_LDADD = $(top_builddir)/src/libserpents.a @CHECK_LIBS@
