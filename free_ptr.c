#include "shell.h"

/**
 * free_double_ptr - free malloced arrays
 * @str: array of strings
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
