/**
 * \file trace.h
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

// size of the hash table
#define FT_HASH_SIZE 4093
 
// structure holding details of a function
struct sym_entry {
	// is this hash table entry used ? 
	int valid;
	// symbol name
	char const * name;
	// address of function
	void * address;
	// total number of times this function has been entered
	unsigned int count;
	// is the function explicitly disabled ?
	int show_disable;
};


void ft_trace_init(void);
