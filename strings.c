#include "shell.h"

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * Return: copy of original source
 */

char *_strcpy(char *dest, char *src)
{
	int a, len;

	for (len = 0; src[len] != '\0'; len++)
		;

	for (a = 0; a <= len; a++)
		dest[a] = src[a];

	return (dest);
}

/**
 * _strcmp - compare two strings
 * @s1: string 1
 * @s2: string 2
 * Return: int that tells num spaces in between, 0 if exactly the same string
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (*(s1 + i) == *(s2 + i) && *(s1 + i))
		i++;

	if (*(s2 + i))
		return (*(s1 + i) - *(s2 + i));
	else
		return (0);
}

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
