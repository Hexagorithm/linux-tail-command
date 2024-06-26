#include <stdio.h>
#include <string.h> /* strlen*/
#include <stdbool.h> /* bools */
#include <stdlib.h> /* atoi*/

#define MAX_NUMBER_LINES 100
#define MAX_LINE_LENGTH 200
#define MAX_STACK_SIZE MAX_LINE_LENGTH * MAX_NUMBER_LINES
#define DEFAULT_NLINES 10
#define VERBOSE if (isverbose)

char stack[MAX_NUMBER_LINES * MAX_LINE_LENGTH];
char* stackptr = stack; /* shows the next free space */
char* lines[MAX_NUMBER_LINES];
int linesptr = 0; /* shows the next free space to allocate string */
bool isnlines = false;
bool isverbose = false;
int nlines = 0;

char* allocate_size(size_t size);
void print_help(void);
void load_sequence(char* dst, char* src, size_t size );
int free_alloc_pointer(char* pointer);
void free_alloc_pointers(void);
int readline(char buffer[]);
void alloc_lines(void);
void print_all_lines(void);
void print_lines(int count);

int main(int argc, char* argv[])
{
	char* argument;
	int parameter;
	for (int current_arg_i = 1; current_arg_i < argc; ++current_arg_i)
	{
		argument = *(++argv);
		if (argument[0] != '-') continue; /* Argument is NOT an option*/
		if (strlen(argument) == 1)
		{
			printf("Invalid argument: \"-\"\n");
			return 1;
		}
		switch (argument[1])
		{
			case 'n':
				if (strlen(argument) != 2)
				{
					printf("Invalid argument detected: \"%s\".\n",argument);
					return 1;
				}
				else if (current_arg_i == argc - 1) /* Current argument is last, no parameter given*/
				{
					printf("-n: no parameter given.\n");
					return 1;
				}
				nlines = atoi(*(argv+1));
				isnlines = true;
				break;
			case 'v':
				if (strlen(argument) != 2)
				{
					printf("Invalid argument detected: \"%s\".\n",argument);
					return 1;
				}
				isverbose = true;
				break;
			case 'h':
				if (strlen(argument) != 2)
				{
					printf("Invalid argument detected: \"%s\".\n",argument);
					return 1;
				}
				print_help();
				return 0;
			default:
				printf("Invalid argument detected: \"%s\".\n",argument);
				return 1;

		}
	}
	if (isnlines == false) nlines = 10;
	alloc_lines();
	nlines = (nlines <= linesptr) ? nlines : linesptr;
	VERBOSE printf("%d lines selected for output.\n\n\n", nlines);
	
	VERBOSE printf("\tLines read from file:\n");
	VERBOSE print_all_lines();
	VERBOSE printf("\n\n\n");
	VERBOSE printf("\tLines selected from file:\n");
	print_lines(nlines);
	VERBOSE printf("Freeing pointers.\n");
	free_alloc_pointers();

	return 0;
}

void print_help(void)
{
	printf(
			"tail: get n(10) last lines of input.\n"
			"Options:\n"
			"\t-h -> show help\n"
			"\t-n -> specify number of lines to output (default = 10)\n"
			"\t-v -> verbose mode (should not use if output used in another program)\n");
	return;

}

char* allocate_size(size_t size)
{
	/* NOTE: when allocating string, manually increment size value to accomodate null byte */
	if (stackptr + size > stack + MAX_STACK_SIZE) /* Allocation failed, stack full*/ 
	{
		return NULL;
	}
	char* pointer = stackptr;
	stackptr += size;
	return pointer;
}

void load_sequence(char* dst, char* src, size_t size )
{
	/* Assume dst can hold src */
	/* Assume size to not include null byte*/
	/* allocate null byte by force */
	/* Allocate size+1 bytes ( +1 = null byte)*/
	/* This way strlen() can be used without trouble */
	int i;
	for (i = 0; i < size && src[i] != '\0'; ++i)
	{
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return;
}

void free_alloc_pointers(void)
{
	for (int i = linesptr-1; i >= 0; --i)
	{
		free_alloc_pointer(lines[i]);
	}
}

int free_alloc_pointer(char* pointer)
{
	if (!( stack <= pointer && pointer <= stack + MAX_STACK_SIZE)) return -1; /* pointer not on stack*/
	else if (stackptr < pointer) return -2; /* pointer already freed! */
	stackptr = pointer;
	return 0;
}

void alloc_lines(void)
{
	char buffer[MAX_LINE_LENGTH];
	int length; 
	while (1)
	{
		length = readline(buffer);
		if (buffer[0] == EOF) /* Phantom line, EOF */
		{
			break;
		}
		int i;
		for (i = 0; buffer[i] != '\n'; ++i);
		buffer[i] = '\0';
		char* pointer = allocate_size(length+1);
		load_sequence(pointer, buffer, length);
		lines[linesptr++] = pointer;
	}
	return;
}


int readline(char buffer[])
{
	int c;
	int i = 0;
	while (i < MAX_LINE_LENGTH -1)
	{
		buffer[i++] = (c=getchar());
		if (c == EOF || c == '\n') break;
	}
	if (i == MAX_LINE_LENGTH - 1 && c != '\n' && c != EOF) /* line too long*/
	{
		while ((c = getchar()) != '\n' &&  c != EOF ); /* pass through the line, so the next one is in the chamber when readline invoked again*/
	}
	return i; /* i is length (without null byte)*/
}

void print_all_lines(void)
{
	for (int i = 0; i < linesptr; ++i)
	{
		printf("%d.\"%s\"\n",i,lines[i]);
	}
	return;

}

void print_lines(int count)
{
	for (int i = count; i > 0; --i)
	{
		printf("%s\n",lines[linesptr-i]);
	}
	return;
}
