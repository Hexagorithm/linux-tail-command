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
	char* pointer = allocate_size(1);
	printf("pointer: %p, stackptr: %p\n",pointer, stackptr);
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
	if (stackptr + size > stack + MAX_STACK_SIZE) /* Allocation failed, stack full*/ 
	{
		return NULL;
	}
	char* pointer = stackptr;
	stackptr += size;
	return pointer;
}
