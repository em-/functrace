AC_PREREQ(2.60)
AC_INIT([abc],
        [0.0.2])
AC_CONFIG_SRCDIR([src/functrace.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([
	check-news
	foreign
	1.11
	-Wall
	-Wno-portability
	silent-rules
	tar-pax
	no-dist-gzip
	dist-xz
	subdir-objects
])
AC_PROG_CC_STDC
AC_USE_SYSTEM_EXTENSIONS
AC_SYS_LARGEFILE
AC_CONFIG_MACRO_DIR([m4])
AM_SILENT_RULES([yes])
LT_INIT([
	 disable-shared
])
AC_PREFIX_DEFAULT([/usr])

AC_PROG_SED
AC_PROG_MKDIR_P

AC_CHECK_FUNCS([ \
	__secure_getenv \
	secure_getenv\
])

AX_CHECK_LIBRARY([LIBBFD], [bfd.h], [bfd],
		 [LIBBFD_LDFLAGS='-lbfd'],
		 [AC_MSG_ERROR([Unable to find libbfd])])
AX_CHECK_LIBRARY([LIBIBERTY], [libiberty/libiberty.h], [iberty],
		 [LIBIBERTY_LDFLAGS='-liberty'],
		 [AC_MSG_ERROR([Unable to find libiberty])])
AX_CHECK_LIBRARY([LIBDL], [dlfcn.h], [dl],
		 [LIBDL_LDFLAGS='-ldl'],
		 [AC_MSG_ERROR([Unable to find libdl])])

my_CFLAGS="\
-Wall \
-Wchar-subscripts \
-Wformat-security \
-Wmissing-declarations \
-Wmissing-prototypes \
-Wnested-externs \
-Wpointer-arith \
-Wshadow \
-Wsign-compare \
-Wstrict-prototypes \
-Wtype-limits \
"
AC_SUBST([my_CFLAGS])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([
        Makefile
])

AC_OUTPUT
AC_MSG_RESULT([
        $PACKAGE $VERSION
        =====

        prefix:                 ${prefix}
        sysconfdir:             ${sysconfdir}
        libdir:                 ${libdir}
        includedir:             ${includedir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}
])
