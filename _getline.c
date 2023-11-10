#include "shell.h"

/**
 * _getline - stores into malloced buffer the user's command into shell
 * @string: buffer
 * Return: number of characters read
 */
size_t _getline(char **string)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1)
			return (-1);

		buff[i] = '\0';

		n = 0;
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		if (t == 0)
		{
			i++;
			*string = malloc(sizeof(char) * i);
			*string = _strcpy(*string, buff);
			size = i;
			t = 1;
		}
		else
		{
			size += i;
			*string = _strcat(*string, buff);
		}
	}
	return (size);
}
