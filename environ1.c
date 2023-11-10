#include "shell.h"

/**
 * _cmpenv_name - Compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if not equal. Another value if they are.
 */
int _cmpenv_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @environ:environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **environ)
{
	char *ptrenv;
	int i, mov;

	/* Initialize ptrenv value */
	ptrenv = NULL;
	mov = 0;
	/* Compares all environment variables */
	/* environ is declared in the header file */
	for (i = 0; environ[i]; i++)
	{
		/* If name and env are equal */
		mov = _cmpenv_name(environ[i], name);
		if (mov)
		{
			ptrenv = environ[i];
			break;
		}
	}
	return (ptrenv + mov);
}

/**
 * env - print environment variables
 *
 * @data: data relevant.
 * Return: 1 on success.
 */
int env(data_shell *data)
{
	int i, j;

	for (i = 0; data->environ[i]; i++)
	{

		for (j = 0; data->environ[i][j]; j++)
			;

		write(STDOUT_FILENO, data->environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;

	return (1);
}
