#include "shell.h"

/**
 * _cdshell - changes to current directory
 *
 * @data: data Relevant
 * Return: 1 on success
 */
int _cdshell(data_shell *data)
{
	char *dir;
	int ishome, ishome2, isddash

	dir = data->args[1];

	if (dir != NULL)
	{
		ishome = strcmp("$HOME", dir);
		ishome2 = strcmp("~", dir);
		isddash = strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_tohome(data);
		return (1);
	}

	if (strcmp("-", dir) == 0)
	{
		_cdprevious(data);
		return (1);
	}

	if (strcmp(".", dir) == 0 || strcmp("..", dir) == 0)
	{
		_cddot(data);
		return (1);
	}

	_cdto(data);

	return (1);
}
