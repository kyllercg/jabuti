INCLUDES			= -I$(top_srcdir)/src \
					  -I$(top_srcdir)/src/petri \
					  -I$(top_srcdir)/src/sg

LDADD				= $(top_builddir)/src/petri/libpetrinet.a \
					  $(top_builddir)/src/sg/libsg.a
					  
pkglib_LIBRARIES	= libacms.a
libacms_a_SOURCES	= StateGraph.cpp StateGraph.h \
					  Penknife.cpp Penknife.h \
					  Simulator.cpp Simulator.h

# AM_CPPFLAGS			= -O3
AUTOMAKE_OPTIONS	= foreign
