/**
 * \file ft_util.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */
 
#include "functrace.h"

/**
 * ft_malloc - allocate memory
 * @size: size in bytes
 *
 * Allocate memory of size @size bytes.
 *
 * The memory may be freed with standard C library
 * free().
 *
 * Returns a void pointer to the memory allocated.
 */ 
void *ft_malloc(size_t size)
{
	return malloc(size);
} 
 
 
/**
 * ft_malloc0 - allocate and clear memory
 * @size: size in bytes
 *
 * Allocate memory of size @size bytes. The buffer 
 * is filled with zeroes.
 *
 * The memory may be freed with standard C library
 * free().
 *
 * Returns a void pointer to the memory allocated.
 */ 
void *ft_malloc0(size_t size)
{
	void * p;

	p = ft_malloc(size);
	if (p)
		memset(p, 0, size); 
	return p;
}

 
/**
 * ft_realloc - resize allocated memory
 * @buf: current memory
 * @size: size in bytes of new request
 *
 * Re-allocates a buffer with a different
 * size.
 *
 * @buf may be %NULL.
 * 
 * Returns a void pointer to the new memory
 * allocated. 
 */ 
void * ft_realloc(void * buf, size_t size)
{
	if (!buf)
		return ft_malloc(size);
 
	return realloc(buf, size);
}
 
 
/**
 * ft_free - free previously allocated memory
 * @p: pointer to memory
 *
 * Free previously allocated memory. @p may be
 * %NULL, in which case nothing happens.
 */ 
void ft_free(void *p)
{
	if (p)
		free(p);
}
 
/**
 * ft_get_line - read an ASCII line from a file
 * @fp: file pointer 
 *
 * Get a line of ASCII text from a file. The file is read
 * up to the first \0 or \n.
 * 
 * Returns the dynamically-allocated string containing
 * that line. At the end of a file a string "" will
 * be returned.
 *
 * In *both* cases, the string must be free()d at some
 * point.
 *
 * %NULL may be returned on allocation failure.
 */ 
char * ft_get_line(FILE * fp)
{
	char * buf;
	char * cp;
	int c;
	size_t max = 128;

	buf = ft_malloc(max);
	if (!buf)
		return NULL;
 
	cp = buf; 

	do {
		switch (c = fgetc(fp)) {
			case EOF:
			case '\0':
				*cp = '\0';
				return buf;
				break;

			case '\n':
				*cp = (char)c;
				cp++;
				if (((size_t)(cp - buf)) == max) {
					buf = ft_realloc(buf, max + 64);
					if (!buf)
						return NULL;
					cp = buf+max;
					max += 64;
				}
				*cp = '\0';
				return buf;
				break;

			default:
				*cp = (char)c;
				cp++;
				if (((size_t)(cp - buf)) == max) {
					buf = ft_realloc(buf, max + 64);
					if (!buf)
						return NULL;
					cp = buf+max;
					max += 64;
				}
				break;
		}
	} while (1);
}
