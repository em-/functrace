EXTRA_DIST =
CLEANFILES =
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-I${top_srcdir}/src

AM_CFLAGS = ${my_CFLAGS} \
	${LIBBFD_CFLAGS} \
	${LIBIBERTY_CFLAGS} \
	${LIBDL_CFLAGS} \
	-fvisibility=hidden \
	-ffunction-sections \
	-fdata-sections

AM_LDFLAGS = \
	${LIBBFD_LDFLAGS} \
	${LIBIBERTY_LDFLAGS} \
	${LIBDL_LDFLAGS} \
	-Wl,--gc-sections \
	-Wl,--as-needed

SED_PROCESS = \
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(SED) \
	-e 's,@VERSION\@,$(VERSION),g' \
	-e 's,@prefix\@,$(prefix),g' \
	-e 's,@exec_prefix\@,$(exec_prefix),g' \
	-e 's,@libdir\@,$(libdir),g' \
	-e 's,@includedir\@,$(includedir),g' \
	< $< > $@ || rm $@

%.pc: %.pc.in Makefile
	$(SED_PROCESS)

LIBFUNCTRACE_CURRENT=1
LIBFUNCTRACE_REVISION=0
LIBFUNCTRACE_AGE=0

lib_LTLIBRARIES = src/libfunctrace.la

src_libfunctrace_la_SOURCES =\
	src/config.c \
	src/ft_util.h \
	src/ft_util.c \
	src/functrace.h \
	src/symbols.c \
	src/trace.h \
	src/trace.c

EXTRA_DIST += src/libfunctrace.sym

src_libfunctrace_la_LDFLAGS = $(AM_LDFLAGS) \
	-version-info $(LIBFUNCTRACE_CURRENT):$(LIBFUNCTRACE_REVISION):$(LIBFUNCTRACE_AGE) \
	-Wl,--version-script=$(top_srcdir)/src/libfunctrace.sym
src_libfunctrace_la_DEPENDENCIES = ${top_srcdir}/src/libfunctrace.sym

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libfunctrace.pc
EXTRA_DIST += src/libfunctrace.pc.in
CLEANFILES += src/libfunctrace.pc
