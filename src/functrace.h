/**
 * \file functrace.h
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include <stdio.h> 
#include <stdlib.h>
 
/* missing from libiberty.h */
#ifndef DMGL_PARAMS
# define DMGL_PARAMS     (1 << 0)        /* Include function args */
#endif 
#ifndef DMGL_ANSI 
# define DMGL_ANSI       (1 << 1)        /* Include const, volatile, etc */
#endif
 
#ifndef uint
#define uint unsigned int
#endif
 
#define CONSTRUCTOR __attribute__((constructor, no_instrument_function))
#define DESTRUCTOR __attribute__((destructor, no_instrument_function))
 
char * cplus_demangle (const char * mangled, int options);
 
void CONSTRUCTOR functrace_init(void);
void DESTRUCTOR functrace_exit(void);
 
void __cyg_profile_func_enter(void (*fn)(), void (*parent)()) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void (*fn)(), void (*parent)()) __attribute__((no_instrument_function));


int ft_open_image(void);
char * ft_get_symbol(void * address);
