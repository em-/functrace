/**
 * \file trace.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include "functrace.h" 
 
void __cyg_profile_func_enter(void (*fn)(), void (*parent)())
{
	char * name;
	char * parent_name;

	functrace_init();
 
	name = ft_get_symbol(fn);
	parent_name = ft_get_symbol(parent);

	fprintf(stderr, "Entered \"%s\" (%p, parent \"%s\" (%p)\n", name, fn, parent_name, parent);
}
 
 
void __cyg_profile_func_exit(void (*fn)(), void (*parent)())
{
	char * name;
	char * parent_name;

	name = ft_get_symbol(fn);
	parent_name = ft_get_symbol(parent);

	fprintf(stderr, "Exited \"%s\", back to parent \"%s\" (%p)\n", name, parent_name, parent);
}
