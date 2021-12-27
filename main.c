/*
 * https://en.wikipedia.org/wiki/Caesar_cipher
 */

#include "cc.h"
//There are 127 characters in ascii


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
	if(isspace(ch)) return (ch);
	//enconding spaces is a clusterfuck
	key %= ASCII_SZ;
	ch += key;
	if(ASCII_SZ <= ch)ch -= ASCII_SZ;
	if(ch < '!') ch += '!';
	//dirty little trick perhaps, but it works
	return (ch);
}

//inverted encryt()
int decrypt(int ch, size_t key)
{
	if(isspace(ch)) return (ch);
	key %= ASCII_SZ;
	ch -= key;
	if(ASCII_SZ <= ch) ch += ASCII_SZ;
	if(ch < '!') ch -= '!';
	return (ch);
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
	int c = 0;

	switch(p_flags.action){
		case 'e':{
			while((c = getc(f)) != EOF){
				c = encrypt(c, p_flags.key);
				printf("%c", c);
			}
			break;
			
		}
		case 'd':{
			while((c = fgetc(f)) != EOF){
				c = decrypt(c, p_flags.key);
				printf("%c", c);
			}
			break;
		}
		default:{
			fprintf(stderr, "I don't recognize that option.\n");
			break;
		}
	}

	return (0);
}
