INCLUDES			= -I$(top_srcdir)/src

pkglib_LIBRARIES	= libsg.a
libsg_a_SOURCES		= sg.h \
					  State.cpp State.h \
					  Arc.cpp Arc.h \
					  Process.cpp Process.h \
					  Channel.cpp Channel.h \
					  sg_yacc.ypp sg_lex.lpp \
					  SGParser.cpp SGParser.h

AM_YFLAGS			= -d 

# AM_CPPFLAGS			= -O3
AUTOMAKE_OPTIONS	= foreign
