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

	verstr_ = _itoa(data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = strlen(data->av[0]) + strlen(verstr_);
	length += strlen(data->args[0]) + strlen(msg) + 4;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(verstr_);
		return (NULL);
	}

	strcpy(err, data->av[0]);
	strcat(err, ": ");
	strcat(err, verstr_);
	strcat(err, ": ");
	strcat(err, data->args[0]);
	strcat(err, msg);
	strcat(err, "\0");
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

	verstr_ = _itoa(data->counter);
	length = strlen(data->av[0]) + strlen(verstr_);
	length += strlen(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(verstr_);
		return (NULL);
	}
	strcpy(err, data->av[0]);
	strcat(err, ": ");
	strcat(err, verstr_);
	strcat(err, ": ");
	strcat(err, data->args[0]);
	strcat(err, ": Permission denied\n");
	strcat(er, "\0");
	free(verstr_);
	return (err);
}
