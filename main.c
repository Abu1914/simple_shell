#include "shell.h"

/**
 * _freedata - frees data Structure
 *
 * @data: data structure
 * Return: No return
 */
void _freedata(data_shell *data)
{
	unsigned int i;

	for (i = 0; data->environ[i]; i++)
	{
		free(data->environ[i]);
	}

	free(data->environ);
	free(data->pid);
}

/**
 * set_data - initialize data Structure
 *
 * @data: data structure
 * @av: argument vector
 * Return: No return
 */
void set_data(data_shell *data, char **av)
{
	unsigned int i;

	data->av = av;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data->environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->environ[i] = str_dup(environ[i]);
	}

	data->environ[i] = NULL;
	data->pid = _itoa(getpid());
}

/**
 * main - entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	data_shell data;
	(void) ac;

	signal(SIGINT, _getsigint);
	set_data(&data, av);
	_shell_loop(&data);
	_freedata(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
}

/**
 * _readline - reads input string.
 *
 * @i_eof: Return value of getline function
 * Return: input string
 */
char *_readline(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = _getline(&input, &bufsize, stdin);

	return (input);
}
