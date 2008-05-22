INCLUDES		= -I$(top_srcdir)/src/acms \
			  -I$(top_srcdir)/src/petri \
			  -I$(top_srcdir)/src/sg

LDADD			= $(top_builddir)/src/acms/libacms.a \
			  $(top_builddir)/src/petri/libpetrinet.a \
			  $(top_builddir)/src/sg/libsg.a
						  
bin_PROGRAMS		= jabuti

# sg_test_SOURCES	= sg_test.cpp $(top_srcdir)/src/sg/sg.h
# sg_test_LDADD		= $(top_builddir)/src/sg/libsg.a
					  
# sgp_test_SOURCES	= sgp_test.cpp $(top_srcdir)/src/sg/sg.h
# sgp_test_LDADD	= $(top_builddir)/src/sg/libsg.a

# codep_test_SOURCES	= codep_test.cpp $(top_srcdir)/src/code/code.h
# cpdep_test_LDADD		= $(top_builddir)/src/sg/libcodegen.a

jabuti_SOURCES		= jabuti.cpp $(top_srcdir)/src/config.h
jabuti_LDADD		= $(top_builddir)/src/acms/libacms.a \
			  $(top_builddir)/src/sg/libsg.a \
			  $(top_builddir)/src/petri/libpetrinet.a

# AM_CPPFLAGS		= -O3
SUBDIRS			= sg petri acms
AUTOMAKE_OPTIONS	= foreign
# EXTRA_DIST		= config.h
