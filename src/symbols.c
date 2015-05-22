/**
 * \file symbols.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include <bfd.h>
 
#include "functrace.h"
 
// bfd of current image
static bfd * ibfd;
// sorted symbols array
static asymbol ** symbols;
// number of symbols
static uint nr_symbols;
 
static int ft_get_symbols();
 
char * ft_get_symbol(void * address)
{
	char const * name;
	char const * cp;
	char * unmangled;
	uint i; 

	for (i=0; i < nr_symbols; i++) {
		if ((symbols[i]->section->vma + symbols[i]->value) == (uint)address)
			break;
	}

	if (i == nr_symbols)
		return "";
 
	name = symbols[i]->name;
	cp = unmangled = name;
	while (*cp && *cp == '_')
		cp++;

	if (*cp) {
		unmangled = cplus_demangle(cp, DMGL_PARAMS | DMGL_ANSI);
		if (!unmangled) {
			unmangled = (char *)name;
		}
			// FIXME: free ?
	}
	return unmangled;
}

 
int ft_open_image()
{
	char ** matching;
	 
	ibfd = bfd_openr("/proc/self/exe", NULL);
 
	if (!ibfd) {
		fprintf(stderr, "libfunctrace: bfd_openr failed.\n");
		return -1;
	}
	 
	if (!bfd_check_format_matches(ibfd, bfd_object, &matching)) { 
		fprintf(stderr, "libfunctrace: BFD format failure.\n");
		return -1;
	}

	// collect symbols
	if (!ft_get_symbols()) {
		fprintf(stderr, "libfunctrace: couldn't get symbols.\n");
		return -1;
	}

	return 0;
}

 
static int symcomp(const void * a, const void * b)
{
	//void * va = (*((asymbol **)a))->value + (*((asymbol **)a))->section->filepos; 
	//void * vb = (*((asymbol **)b))->value + (*((asymbol **)b))->section->filepos; 
	uint va = (*((asymbol **)a))->value;
	uint vb = (*((asymbol **)b))->value;

	if (va < vb)
		return -1;
	return (va > vb);
}

 
/* need a better filter, but only this gets rid of _start
 * and other crud easily. 
 */
static int interesting_symbol(asymbol *sym)
{
	if (!(sym->section->flags & SEC_CODE))
		return 0;

	if (!strcmp("", sym->name))
		return 0;

	if (!strcmp("_init", sym->name))
		return 0;

	if (!(sym->flags & BSF_FUNCTION))
		return 0;

	return 1;
}

 
/**
 * ft_get_symbols - get symbols from bfd
 * @ibfd: bfd to read from
 * @symsp: pointer to array of symbol pointers
 *
 * Parse and sort in ascending order all symbols
 * in the file pointed to by @ibfd that reside in
 * a %SEC_CODE section. Returns the number
 * of symbols found. @symsp will be set to point
 * to the symbol pointer array.
 */
int ft_get_symbols()
{
	uint nr_all_syms;
	uint i; 
	size_t size;
	asymbol **syms; 

	if (!(bfd_get_file_flags(ibfd) & HAS_SYMS))
		return 0;

	size = bfd_get_symtab_upper_bound(ibfd);

	/* HAS_SYMS can be set with no symbols */
	if (size<1)
		return 0;

	syms = malloc(size);
	// FIXME
	nr_all_syms = bfd_canonicalize_symtab(ibfd, syms);
	if (nr_all_syms < 1) {
	        free(syms);
	        return 0;
	}

	for (i=0; i < nr_all_syms; i++) {
		if (interesting_symbol(syms[i]))
			nr_symbols++;
	}
 
	symbols = malloc(sizeof(asymbol *) * nr_symbols);
	// FIXME

	for (nr_symbols = 0,i = 0; i < nr_all_syms; i++) {
		if (interesting_symbol(syms[i])) {
			symbols[nr_symbols] = syms[i];
			nr_symbols++;
		}
	}
 
	qsort(symbols, nr_symbols, sizeof(asymbol *), symcomp);
 
	return 1;
}
