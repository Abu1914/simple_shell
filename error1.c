#include "shell.h"

/**
 * strcat_cd - function that concatenates the message for cd err
 *
 * @data: data relevant
 * @msg: message to print
 * @err: output message
 * @verstr_: counter lines
 * Return: err message
 */
char *strcat_cd(data_shell *data, char *msg, char *err, char verstr_)
{
	char *illegal_flag;

	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, verstr_);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, msg);
	if (data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(err, data->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * err_get_cd - err message for cd command in get_cd
 * @data: data relevant
 * Return: Error message
 */
char *err_get_cd(data_shell *data)
{
	int length, len_id;
	char *err, *verstr_, *msg;

	verstr_ = aux_itoa(data->counter);
	if (data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(data->args[1]);
	}

	length = _strlen(data->av[0]) + _strlen(data->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (length + 1));

	if (err == 0)
	{
		free(verstr_);
		return (NULL);
	}

	err = strcat_cd(data, msg, error, verstr_);

	free(verstr_);

	return (err);
}

/**
 * err_not_found - err message for command not found
 * @data: data relevant (arguments, counter)
 * Return: err message
 */
char *err_not_found(data_shell *data)
{
	int length;
	char *err;
	char *verstr_;

	verstr_ = aux_itoa(data->counter);
	length = _strlen(data->av[0]) + _strlen(verstr_);
	length += _strlen(data->args[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(verstr_);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, verstr_);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(verstr_);
	return (err);
}

/**
 * err_exit_shell - err message for exit in get_exit
 * @data: data relevant (arguments, counter)
 *
 * Return: err message
 */
char *err_exit_shell(data_shell *data)
{
	int length;
	char *err;
	char *verstr_;

	verstr_ = aux_itoa(data->counter);
	length = _strlen(data->av[0]) + _strlen(verstr_);
	length += _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(verstr_);
		return (NULL);
	}
	_strcpy(err, data->av[0]);
	_strcat(err, ": ");
	_strcat(err, verstr_);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, data->args[1]);
	_strcat(err, "\n\0");
	free(verstr_);

	return (err);
}
