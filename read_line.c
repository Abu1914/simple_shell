#include "shell.h"

/**
 * ctrl_c - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * built_in - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @cmd: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, list_t *env, int num, char **cmd)
{
	int a = 0;

	if (_strcmp(token[0], "exit") == 0)
	{
		a = __exit(token, env, num, cmd);
	}
	else if (_strcmp(token[0], "env") == 0)
	{
		_env(token, env);
		a = 1;
	}
	else if (_strcmp(token[0], "cd") == 0)
	{
		a = _cd(token, env, num);
	}
	else if (_strcmp(token[0], "setenv") == 0)
	{
		_setenv(&env, token);
		a = 1;
	}
	else if (_strcmp(token[0], "unsetenv") == 0)
	{
		_unsetenv(&env, token);
		a = 1;
	}
	return (a);
}

/**
 * ign_space - return string without spaces in front
 * @string: string
 * Return: new string
 */
char *ign_space(char *string)
{
	while (*string == ' ')
		string++;
	return (string);
}

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via get_line
 * @cmd: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *cmd, list_t *env)
{
	if (i == 0)
	{
		free(cmd);
		free_linked_list(env);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * prompt - repeatedly prompts user and executes user's cmds if applicable
 * @environ: envrionmental variables
 * Return: 0 on success
 */
int prompt(char **environ)
{
	list_t *env;
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command, *n_command, **token;

	env = envlinked_list(environ);
	do {
		command_line_no++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		else
			_interactive(env);
		signal(SIGINT, ctrl_c);
		command = NULL;
		i = 0;
		i = _getline(&command);
		ctrl_D(i, command, env);
		n_command = command;
		command = ign_space(command);
		n = 0;
		while (command[n] != '\n')
			n++;
		command[n] = '\0';
		if (command[0] == '\0')
		{
			free(n_command);
			continue;
		}
		token = NULL;
		token = _tok(command, " ");
		if (n_command != NULL)
			free(n_command);
		exit_stat = built_in(token, env, command_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = _execve(token, env, command_line_no);
	} while (1);
	return (exit_stat);
}
