/**
 * \file init.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include <string.h> 
 
#include "functrace.h"
#include "trace.h" 
 
extern struct sym_entry * sym_table;

void CONSTRUCTOR functrace_init(void)
{
	static int init = 0;
	if (init)
		return;
	init = 1; 
 
	// open the binary image
	ft_open_image();

	sym_table = malloc(sizeof(struct sym_entry) * 4000);
	// FIXME
	memset(sym_table, 0, sizeof(struct sym_entry) * 4000); 
}


void DESTRUCTOR functrace_exit(void)
{
}
