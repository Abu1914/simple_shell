#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @string: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */
char *_strdup(char *string)
{
	char *dup_str;
	int i, len = 0;

	if (string == NULL)
		return (NULL);

	while (*(string + len))
		len++;
	len++;

	dup_str = malloc(sizeof(char) * len);
	if (dup_str == NULL)
		return (NULL);

	i = 0;
	while (i < len)
	{
		*(dup_str + i) = *(string + i);
		i++;
	}

	return (dup_str);
}
