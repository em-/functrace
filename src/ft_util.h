/**
 * \file ft_util.h
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#ifndef FT_UTIL_H
#define FT_UTIL_H

#define FALSE 0
#define TRUE 1

#define fd_t int
#define streq(a,b) (!strcmp((a), (b)))

/* utility functions */
#define ft_calloc(memb, size) ft_malloc(memb*size)
#define ft_calloc0(memb, size) ft_malloc0(memb*size)
#define ft_crealloc(memb, buf, size) ft_realloc((buf), memb*size)
void *ft_malloc(size_t size) __attribute__((malloc));
void *ft_malloc0(size_t size) __attribute__((malloc));
void *ft_realloc(void *buf, size_t size);
void ft_free(void *p);
 
char *ft_get_line(FILE *fp);

#endif /* FT_UTIL_H */
