#include <stdio.h>
/* Options: */
/*
 * -n <uint> 
 * -h
 *  nothing at all, default 10 lines
*/
int main(int argc, char* argv[])
{
	char* argument;
	for (int _ = 1; _ < argc; ++_)
	{
		argument = *(++argv);
		printf("Argument found!\n");
		printf("Argument found: %s\n",argument);
	}
	return 0;
}
