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
	length = str_len(data->av[0]) + str_len(verstr_);
	length += str_len(data->args[0]) + str_len(msg) + 4;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(verstr_);
		return (NULL);
	}

	str_cpy(err, data->av[0]);
	str_cat(err, ": ");
	str_cat(err, verstr_);
	str_cat(err, ": ");
	str_cat(err, data->args[0]);
	str_cat(err, msg);
	str_cat(err, "\0");
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
	length = str_len(data->av[0]) + str_len(verstr_);
	length += str_len(data->args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(verstr_);
		return (NULL);
	}
	str_cpy(err, data->av[0]);
	str_cat(err, ": ");
	str_cat(err, verstr_);
	str_cat(err, ": ");
	str_cat(err, data->args[0]);
	str_cat(err, ": Permission denied\n");
	str_cat(err, "\0");
	free(verstr_);
	return (err);
}
