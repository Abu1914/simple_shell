#include "shell.h"

/**
 * _repeatedchar - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int _repeatedchar(char *input, int i)
{
	if (*(input - 1) == *input)
		return (_repeatedchar(input - 1, i + 1));

	return (i);
}

/**
 * _errorsep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last:last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int _errorsep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (_errorsep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = _repeatedchar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = _repeatedchar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (_errorsep_op(input + 1, i + 1, *input));
}

/**
 * _firstchar - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int _firstchar(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * _printsyntax_error - prints when a syntax error is found
 *
 * @data: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: No return
 */
void _printsyntax_error(data_shell *data, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(data->counter);
	length = strlen(data->av[0]) + strlen(counter);
	length += strlen(msg) + strlen(msg2) + strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	strcpy(error, data->av[0]);
	strcat(error, ": ");
	strcat(error, counter);
	strcat(error, msg2);
	strcat(error, msg);
	strcat(error, msg3);
	strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * _checksyntax_error - intermediate function to
 * find and print a syntax error
 *
 * @data: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int _checksyntax_error(data_shell *data, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	_fchar = _firstchar(input, &begin);
	if (_fchar == -1)
	{
		_printsyntax_error(data, input, begin, 0);
		return (1);
	}

	i = _errorsep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		_printsyntax_error(data, input, begin + i, 1);
		return (1);
	}

	return (0);
}
