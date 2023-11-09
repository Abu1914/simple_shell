#include "shell.h"

/**
 * err_env - err message for env in getenv
 * @data: data relevant (arguments, counter)
 * Return: err message.
 */
char *err_env(data_shell *data)
{
	int length;
	char *err;
	char *verstr_;
	char *msg;

	verstr_ = aux_itoa(data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(data->av[0]) + _strlen(verstr_);
	length += _strlen(data->args[0]) + _strlen(msg) + 4;
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
	_strcat(err, msg);
	_strcat(err, "\0");
	free(verstr_);

	return (err);
}
/**
 * err_path_126 - err message for path and failure denied Permission.
 * @data: data relevant (arguments, counter)
 *
 * Return: err string.
 */
char *err_path_126(data_shell *data)
{
	int length;
	char *verstr_;
	char *err;

	verstr_ = aux_itoa(data->counter);
	length = _strlen(data->av[0]) + _strlen(verstr_);
	length += _strlen(datash->args[0]) + 24;
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
	_strcat(err, ": Permission denied\n");
	_strcat(er, "\0");
	free(verstr_);
	return (err);
}
