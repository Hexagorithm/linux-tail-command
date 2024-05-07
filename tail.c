#include <stdio.h>
#include <string.h> /* strlen*/
/* Options: */
/*
 * -n <uint> 
 * -h
 *  nothing at all, default 10 lines
*/
void print_help(void);
int main(int argc, char* argv[])
{
	char* argument;
	for (int _ = 1; _ < argc; ++_)
	{
		argument = *(++argv);
		if (argument[0] = '-') /* Argument is an option*/
		{
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
					printf("-n option detected.\n");
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

	}
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
