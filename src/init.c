/**
 * \file init.c
 * Copyright 2001 John Levon
 * Read the file COPYING
 *
 * \author John Levon
 */

#include "functrace.h"
 

void CONSTRUCTOR functrace_init(void)
{
	static int init = 0;
	if (init)
		return;
	init = 1; 
	printf("FUCK"); 
	// open the binary image
	ft_open_image();
}


void DESTRUCTOR functrace_exit(void)
{
}
