/**
 * \file trace.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include "functrace.h" 

#include "trace.h"

struct sym_entry *sym_table;

static inline unsigned int sym_hash(void * address)
{
	unsigned int a = (unsigned int)address; 

	a ^= a >> 14;
	a ^= a << 3;

	return a % 4000;
}

static void ft_get_new_entry(unsigned int hash, void * address)
{
	struct sym_entry * sym = &sym_table[hash]; 
	 
	sym->name = ft_get_symbol(address);
	sym->address = address; 
	sym->count = 0;
	sym->show_disable = 0;
	sym->valid = 1;
}

static struct sym_entry * ft_get_entry(void * address)
{
	unsigned int hash = sym_hash(address);
 
	if (!sym_table[hash].valid) {
		ft_get_new_entry(hash, address);
		goto out;
	} else if (sym_table[hash].address == address)
		goto out;

	while (sym_table[hash].valid && sym_table[hash].address != address) {
		hash = (hash + 1) % 4000;
	// FIXME !!!!!! 
	}
 
out:
	sym_table[hash].count++;
	return &sym_table[hash];
}
 
 
void __cyg_profile_func_enter(void (*fn)(), void (*parent)())
{
	struct sym_entry * entry;

	// FIXME
	functrace_init();
 
	entry = ft_get_entry(fn);


	if (entry->count < 2000)
		fprintf(stderr, "e \"%s\" (%p) %d\n", entry->name, entry->address, entry->count);
}
 
 
void __cyg_profile_func_exit(void (*fn)(), void (*parent)())
{
	struct sym_entry * entry;

	entry = ft_get_entry(fn);

	if (entry->count < 2000)
		fprintf(stderr, "x \"%s\" (%p) %d\n", entry->name, entry->address, entry->count);
}
