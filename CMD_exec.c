#include "shell.h"

/**
 * _iscdir - checks ":" if in the current directory
 * @path: type char pointer char
 * @i: type int pointer of index
 * Return: 1 if the path is searchable in the cd, 0 otherwise
 */
int _iscdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * which - locates a command
 *
 * @cmd: command name
 * @environ: environment variable
 * Return: location of the command
 */
char *which(char *cmd, char **environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", environ);
	if (path)
	{
		ptr_path = str_dup(path);
		len_cmd = str_len(cmd);
		token_path = str_tok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (_iscdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = str_len(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			str_cpy(dir, token_path);
			str_cat(dir, "/");
			str_cat(dir, cmd);
			str_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = str_tok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * _isexecutable - Determines if is executable
 *
 * @data: data structure
 * Return: 0 if not executable, other number if it does
 */
int _isexecutable(data_shell *data)
{
	struct stat st;
	int i;
	char *input;

	input = data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(data, 127);
	return (-1);
}

/**
 * _check_error_cmd - verifies if user has permission to access
 * @dir: Destination directory
 * @data:data structure
 * Return: 1 if there is an error, 0 if not
 */
int _check_error_cmd(char *dir, data_shell *data)
{
	if (dir == NULL)
	{
		get_error(data, 127);
		return (1);
	}

	if (str_cmp(data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			get_error(data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * _cmdexec - executes command lines
 *
 * @data: data relevant (args and input)
 * Return: 1 on success
 */
int _cmdexec(data_shell *data)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = _isexecutable(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = which(data->args[0], data->environ);
		if (_check_error_cmd(dir, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = which(data->args[0], data->environ);
		else
			dir = data->args[0];
		execve(dir + exec, data->args, data->environ);
	}
	else if (pd < 0)
	{
		perror(data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	return (1);
}
