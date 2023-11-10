#include "shell.h"

/**
 * _bringline - Assigns the line var for get_Line
 * @lineptr: Buffer that store the inputed string
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void _bringline(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		str_cpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - read input from stream
 * @lineptr: buffer that stores input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: the number of bytes
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = re_alloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	_bringline(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}

/**
 * _getsigint - handle the ctrl + c Call in Prompt
 * @sig: signal handler
 */
void _getsigint(int sig)
{
	(void)sig;
	_puts("\n$ ");
}
