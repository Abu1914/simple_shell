#include "shell.h"

/**
 * free_double_p - free malloced arrays
 * @string: array of strings
 */
void free_double_p(char **string)
{
	int i = 0;

	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}
