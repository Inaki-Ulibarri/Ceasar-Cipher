/*
 * https://en.wikipedia.org/wiki/Caesar_cipher
 * TODO: make wrappers for ecrypt and decrypt to pipe to files
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>

#include "cc.h"

void print_help()
{
	printf( "ceci: A Ceasar Cipher encryptor and decryptor\n"
			"ceci <options> <files>\n"
			"options:\n"
			"	-k the key used to encrypt and decrypt the file\n"
			"	-e encrypt the file given\n"
			"	-d decrypt the file file given\n"
			"	-h show this help text\n"
			"Note that you always have to provide the key for a file and the -d or -e options.\n");
}

//shift characters is "the wheel", check the wikipedia article
int encrypt(int ch, size_t key)
{
	if(isspace(ch) || !isascii(ch))
		return (ch);
	key %= ASCII_SZ;
	ch += key;
	if((ASCII_SZ - 1) < ch)
		ch = '!' + (ch - (ASCII_SZ - 1));
	if((ASCII_SZ - 1) < ch)
		ch = '!' + (ch - (ASCII_SZ - 1));
	//sometimes it wraps around the wheel twice
 	return (ch);
}

//inverted encryt()
int decrypt(int ch, size_t key)
{
	
	if(isspace(ch) || !isascii(ch))
		return (ch);
	key %= ASCII_SZ;
	ch -= key;
	if(ch < '!')
		ch = (ASCII_SZ - 1) - ('!' - ch);
	if(ch < '!')
		ch = (ASCII_SZ - 1) - ('!' - ch);
 	return (ch);
}

/* wrappers sround encrypt() and decrypt that pipe the output to files*/

void fencrypt(FILE *inp, FILE *out, size_t key)
{
	int c;
	while((c = getc(inp)) != EOF){
		c = encrypt(c, key);
		fprintf(out, "%c", c);
	}
}


void fdecrypt(FILE *inp, FILE *out, size_t key)
{
	int c;
	while((c = getc(inp)) != EOF){
		c = decrypt(c, key);
		fprintf(out, "%c", c);
	}
}

int main(int argc, char *argv[])
{
	if(argc == 1){
		print_help();
		exit (0);
	}
	
	int opt = 0;
	while((opt = getopt(argc, argv, "hk:ed")) != -1){
		
		switch(opt){
			case 'h':
				print_help();
				exit(0);
				break;
				
			case 'k':
				if(optarg==NULL){
					printf("I need you to geve me a key.\n");
					print_help();
				}
				p_flags.key = atoll(optarg);
				break;

			case 'e':
				p_flags.action = 'e';
				break;

			case 'd':
				p_flags.action = 'd';
				break;
				
			default:
				print_help();
				break;
			
		}
	}

	FILE *f;
	f = fopen(argv[optind], "r");
	if(!f){
		fprintf(stderr,"Error opening the file.\n");
		exit(1);
	}
	
	switch(p_flags.action){
	//I am so good at the "c" stuff
	//sometimes I can't believe myself
		case 'e':{
			FILE *g;
			char *outf = strcat(argv[optind], ".cc");
			g = fopen(outf, "w");
			if(!g){
				fprintf(stderr, "Error creating the output file.\n");
				exit (1);
			}
			fencrypt(f, g, p_flags.key);
			break;

		}
		case 'd':{
			fdecrypt(f, stdout, p_flags.key);
			break;
		}
		default:{
			fprintf(stderr, "I don't recognize that option.\n");
			break;
		}
	}

	return (0);
}
