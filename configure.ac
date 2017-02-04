dnl Copyright 2016 Jochem Raat
dnl
dnl This file is part of serpents.
dnl
dnl serpents is free software: you can redistribute it and/or modify it under
dnl the terms of the GNU General Public License as published by the Free
dnl Software Foundation, either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl serpents is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with serpents.  If not, see <http://www.gnu.org/licenses/>.

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([Serpents], [0.1], [jchmrt@riseup.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/main.c])

AC_PROG_CC

# Programs needed for building the static library
AC_PROG_RANLIB
AM_PROG_AR


AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                src/Makefile
                data/Makefile
                tests/Makefile])

# Check for SDL2
SDL_VERSION=2.0.0
AM_PATH_SDL2($SDL_VERSION,
             :,
             AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

AC_DEFINE(COPYRIGHT_STRING,
          ["Copyright 2016 Jochem Raat <jchmrt@riseup.net>"])
AH_TEMPLATE([COPYRIGHT_STRING],
            [Define to the copyright notice for this package])

AC_SUBST(fontsdir, "\$(datadir)/fonts")

AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

# Check for SDL_ttf
PKG_CHECK_MODULES([TTF], [SDL2_ttf], :,
                         AC_MSG_ERROR([*** SDL_ttf not found!]))

AC_SUBST([TTF_CFLAGS])
AC_SUBST([TTF_LIBS])

# Check for Check, used for testing
PKG_CHECK_MODULES([CHECK], [check], :,
  [AC_MSG_WARN([Check was not found, this means you will not be able \
to run the unit tests (using `make check').])])

AC_CHECK_HEADERS([stdlib.h])

AC_OUTPUT
