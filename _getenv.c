#include "shell.h"

/**
 * _str_dup - custom string duplication; excludes beginning bytes
 * @string: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @cs: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *_str_dup(char *string, int cs)
{
	char *duplicate_str;
	int a, len = 0;

	if (string == NULL) /* validate str input */
		return (NULL);

	/* calculate len + null terminator to malloc */
	while (*(string + len))
		len++;
	len++;

	/* allocate memory but exclude environmental variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - cs));
	if (duplicate_str == NULL)
		return (NULL);

	a = 0;
	while (a < (len - cs))
	{
		*(duplicate_str + a) = *(string + cs + a);
		a++;
	}
	return (duplicate_str);
}

/**
 * _getenv - finds and returns a copy of the requested environmental variable
 * @str: string to store it in
 * @env: entire set of environmental variables
 * Return: copy of requested environmental variable
 */
char *_getenv(char *str, list_t *env)
{
	int b = 0, cs = 0;

	while (env != NULL)
	{
		b = 0;
		while ((env->var)[b] == str[b])
			b++;
		if (str[b] == '\0' && (env->var)[b] == '=')
			break;
		env = env->next;
	}

	while (str[cs] != '\0')
		cs++;
	cs++;
	return (_str_dup(env->var, cs));
}
