#include "shell.h"

/**
 * get_error - calls the error according to the builtin, syntax or permission
 * @data: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *data, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = err_env(data);
		break;
	case 126:
		error = err_path_126(data);
		break;
	case 127:
		error = err_not_found(data);
		break;
	case 2:
		if (str_cmp("exit", data->args[0]) == 0)
			error = err_exit_shell(data);
		else if (str_cmp("cd", data->args[0]) == 0)
			error = err_get_cd(data);
		break;
	}

	if (error)
	{
	write(STDERR_FILENO, error, str_len(error));
	free(error);
	}

	data->status = eval;
	return (eval);
}

/**
 * get_help - function that Retrieves help messages according builtin
 * @data: data structure ( args and input)
 * Return: return 0
 */
int get_help(data_shell *data)
{
	if (data->args[1] == 0)
		help_general();
	else if (str_cmp(data->args[1], "setenv") == 0)
		help_setenv();
	else if (str_cmp(data->args[1], "env") == 0)
		help_env();
	else if (str_cmp(data->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (str_cmp(data->args[1], "help") == 0)
		help();
	else if (str_cmp(data->args[1], "exit") == 0)
		help_exit();
	else if (str_cmp(data->args[1], "cd") == 0)
		help_cd();
	else if (str_cmp(data->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, data->args[0],
			str_len(data->args[0]));

	data->status = 0;
	return (1);
}
