#include <stdio.h>
#include <string.h> /* strlen*/
#include <stdbool.h> /* bools */

#define MAX_NUMBER_LINES 100
#define MAX_LINE_LENGTH 200
#define MAX_STACK_SIZE MAX_LINE_LENGTH * MAX_NUMBER_LINES

char stack[MAX_NUMBER_LINES * MAX_LINE_LENGTH];
char* stackptr = stack; /* shows the next free space */
bool isnlines = false;

char* allocate_size(size_t size);
void print_help(void);
void load_sequence(char* dst, char* src, size_t size );

int main(int argc, char* argv[])
{
	char* argument;
	for (int _ = 1; _ < argc; ++_)
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
				isnlines = true;
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
	printf("Isnlines: %d\n",isnlines);
	char string1[] = "Hello";
	char* pointer1 = allocate_size(strlen(string1) +1);
	char string2[] = "There";
	char* pointer2 = allocate_size(strlen(string2) +1);
	load_sequence(pointer1, string1, strlen(string1));
	load_sequence(pointer2, string2, strlen(string2));

	printf("Allocated string1: \"%s\"\n", pointer1);
	printf("Allocated string2: \"%s\"\n", pointer2);
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
