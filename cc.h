#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

//127 character in ascii
#define ASCII_SZ 127

struct flags{
	size_t key;
	int action;
} p_flags;
