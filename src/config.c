/**
 * \file config.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include "functrace.h"

char * line;
FILE * fp;
 
char * ft_next_token()
{
	static char * cp;
	char * token; 
	char * cp2;
 
	if (!line) {
		line = ft_get_line(fp);
		cp = line;
	}

	printf("Line : $%s$\n", line); 
	if (*cp == '\0') {
		free(line);
		line = ft_get_line(fp);
		if (line[0] == '\0') {
			free(line);
			return NULL;
		}
		cp = line;
	}

	cp2 = cp;
	while (*cp != '\0' && *cp != ' ' && *cp != '\n' && *cp != '\t')
		cp++;

	token = ft_malloc(cp - cp2 + 1);
	if (!token)
		return token;

	strncpy(token, cp2, cp - cp2);
	token[cp - cp2] = '\0';
 
	cp += cp - cp2;
 
	printf("cp : $%s$\n", cp); 
	while (*cp == '\t' || *cp == ' ')
		cp++;
 
	return token;
}


void ft_read_config(char const * argv0)
{
	char * token;
	// FIXME
 
	fp = fopen("/home/moz/.functracerc", "r");
	if (!fp)
		return;

	while ((token = ft_next_token())) {
		printf("Token: $%s$\n", token);
		free(token);
	}
 
	fclose(fp);
}
