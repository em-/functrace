/**
 * \file trace.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include "functrace.h" 
#include "trace.h"

// the symbol hash table
static struct sym_entry *sym_table;
// current size of hash table 
static uint sym_hash_size = FT_HASH_SIZE; 


void ft_trace_init(void)
{
	sym_table = malloc(sizeof(struct sym_entry) * FT_HASH_SIZE);
	printf("%p\n",sym_table);
	// FIXME: failure ? 
	memset(sym_table, 0, sizeof(struct sym_entry) * FT_HASH_SIZE);
}
 
 
static inline uint sym_hash(void * address)
{
	uint a = (uint)address; 

	// FIXME: can do better
 
	a ^= a >> 9;
	a ^= a << 3;

	return a % sym_hash_size;
}
 

static void ft_get_new_entry(uint hash, void * address)
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
	uint hash = sym_hash(address);
 
	if (!sym_table[hash].valid) {
		ft_get_new_entry(hash, address);
		goto out;
	} else if (sym_table[hash].address == address)
		goto out;

	// FIXME
	while (sym_table[hash].valid && sym_table[hash].address != address) {
		hash = (hash + 1) % sym_hash_size;
	}
 
out:
	return &sym_table[hash];
}
 
 
static void ft_update_stats_e(struct sym_entry * entry)
{
	entry->count++;
}

 
static void ft_update_stats_x(struct sym_entry * entry)
{
}

 
/**
 * ft_interesting_entry - is the entry interesting ?
 * @entry: the entry to check
 *
 * Returns 1 if the entry should be reported, 0 otherwise. 
 */
static int ft_interesting_entry(struct sym_entry * entry)
{
	// FIXME
	return 1;
}

 
static void ft_output_entry(struct sym_entry * entry, uint is_entry)
{
	// FIXME
	fprintf(stderr, "%c %s\n", is_entry ? 'e' : 'x', entry->name); 
}
 
 
void __cyg_profile_func_enter(void (*fn)(), void (*parent)())
{
	struct sym_entry * entry;

	entry = ft_get_entry(fn);

	ft_update_stats_e(entry);
 
	if (ft_interesting_entry(entry))
		ft_output_entry(entry, 1);
}
 
 
void __cyg_profile_func_exit(void (*fn)(), void (*parent)())
{
	struct sym_entry * entry = ft_get_entry(fn);

	ft_update_stats_x(entry);
 
	if (ft_interesting_entry(entry))
		ft_output_entry(entry, 0);
}
 
void CONSTRUCTOR functrace_init(void)
{
	// read the config file
	ft_read_config("FIXME");

	// open the binary image
	ft_open_image();

	// initialise tracing structures
	ft_trace_init();
}


void DESTRUCTOR functrace_exit(void)
{
}
