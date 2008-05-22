#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.57)
AC_INIT(jabuti, 0.4.2, kyller@lsi.upc.edu)
#AC_CONFIG_SRCDIR([src/config.h])
#AC_CONFIG_HEADER([src/config.h])
AM_INIT_AUTOMAKE(jabuti, 0.4.2)

# Checks for programs.
AC_PROG_CXX
#AC_PROG_CC
#AC_STDC_HEADERS
AC_PROG_LEX
AC_PROG_YACC
#AC_PROG_INSTALL
AC_PROG_RANLIB

# This is to call doxygen
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(ON)
DX_INIT_DOXYGEN(jabuti, Doxyfile, docs/doxygen)

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stddef.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_OUTPUT([Makefile
           src/Makefile
           src/acms/Makefile
           src/petri/Makefile
           src/sg/Makefile])
