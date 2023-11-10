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
char *strcat_cd(data_shell *data, char *msg, char *err, char *verstr_)
{
	char *illegal_flag;

	str_cpy(err, data->av[0]);
	str_cat(err, ": ");
	str_cat(err, verstr_);
	str_cat(err, ": ");
	str_cat(err, data->args[0]);
	str_cat(err, msg);
	if (data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = data->args[1][1];
		illegal_flag[2] = '\0';
		str_cat(err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		str_cat(err, data->args[1]);
	}

	str_cat(err, "\n");
	str_cat(err, "\0");
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

	verstr_ = _itoa(data->counter);
	if (data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = str_len(data->args[1]);
	}

	length = str_len(data->av[0]) + str_len(data->args[0]);
	length += str_len(verstr_) + str_len(msg) + len_id + 5;
	err = malloc(sizeof(char) * (length + 1));

	if (err == 0)
	{
		free(verstr_);
		return (NULL);
	}

	err = strcat_cd(data, msg, err, verstr_);

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

	verstr_ = _itoa(data->counter);
	length = str_len(data->av[0]) + str_len(verstr_);
	length += str_len(data->args[0]) + 16;
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
	str_cat(err, ": not found\n");
	str_cat(err, "\0");
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

	verstr_ = _itoa(data->counter);
	length = str_len(data->av[0]) + str_len(verstr_);
	length += str_len(data->args[0]) + str_len(data->args[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(verstr_);
		return (NULL);
	}
	str_cpy(err, data->av[0]);
	str_cat(err, ": ");
	str_cat(err, verstr_);
	str_cat(err, ": ");
	str_cat(err, data->args[0]);
	str_cat(err, ": Illegal number: ");
	str_cat(err, data->args[1]);
	str_cat(err, "\n\0");
	free(verstr_);

	return (err);
}
