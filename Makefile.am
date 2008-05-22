SUBDIRS			= src
AUTOMAKE_OPTIONS	= foreign

include aminclude.am

MOSTLYCLEANFILES	= $(DX_CLEANFILES)

EXTRA_DIST		= cleanup bootstrap $(DX_CONFIG) $(doc_DATA) docs

docdir			= $(datadir)/doc/jabuti
doc_DATA		= $(top_builddir)/AUTHORS \
			  $(top_builddir)/ChangeLog \
			  $(top_builddir)/DEBIAN \
			  $(top_builddir)/copyright \
			  $(top_builddir)/NEWS

exdir			= $(datadir)/doc/jabuti/examples
ex_DATA			= $(top_builddir)/docs/examples/[ro]*

if DX_COND_pdf

pdfdir			= $(datadir)/doc/jabuti
pdf_DATA		= @DX_DOCDIR@/jabuti.pdf

endif

if DX_COND_ps

psdir			= $(datadir)/doc/jabuti
ps_DATA			= @DX_DOCDIR@/jabuti.ps

endif

man3dir			= $(datadir)/man/man3
man3_MANS		= @DX_DOCDIR@/man/man3/*

if DX_COND_man

$(man3_MANS): doxygen-doc

endif

if DX_COND_html

htmldir			= $(datadir)/doc/jabuti/html
html_DATA		= @DX_DOCDIR@/html/*

$(html_DATA): doxygen-doc

endif

