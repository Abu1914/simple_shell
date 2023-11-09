#include "shell.h"

/**
 * _execline - finds builtins and commands
 *
 * @data: data relevant (args)
 * Return: 1 on success
 */
int _execline(data_shell  *data)
{
	int (*builtin)(data_shell  *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = get_builtin(data->args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (_cmdexec(data));
}

/**
 * _exit_shell - exits the shell
 *
 * @data: data relevant (status and args)
 * Return: 0 on success
 */
int _exit_shell(data_shell *data)
{
	unsigned int ustatus;
	int isdigit;
	int slen;
	int big_number;

	if (data->args[1] != NULL)
	{
		ustatus = atoi(data->args[1]);
		isdigit = is_digit(data->args[1]);
		slen = str_len(data->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!isdigit || slen > 10 || big_number)
		{
			get_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (ustatus % 256);
	}
	return (0);
}

/**
 * get_builtin - Builtin that parse command in arg
 * @cmd: Command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", env },
		{ "exit", _exit_shell },
		{ "setenv", set_env },
		{ "unsetenv", unset_env },
		{ "cd", _cdshell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (str_cmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
