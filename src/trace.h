/**
 * \file trace.h
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

struct sym_entry {
	char const * name;
	void * address; 
	unsigned int count;
	int show_disable;
	int valid;
};
