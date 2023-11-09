#include "shell.h"

/**
 * _withoutcomment - deletes comments from input
 *
 * @in: input string
 * Return: input without comments
 */
char *_withoutcomment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * _shell_loop - loop of shell
 * @data: data relevant (av, input, args)
 *
 * Returns: No return
 */
void _shell_loop(data_shell *data)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = _withoutcomment(input);
			if (input == NULL)
				continue;

			if (_checksyntax_error(data, input) == 1)
			{
				data->status = 2;
				free(input);
				continue;
			}
			input = _repvar(input, data);
			loop = _splitcommands(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
