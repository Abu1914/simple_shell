#include "shell.h"

/**
 * c_exit - frees user's typed command and linked list before exiting
 * @string: user's typed command
 * @env: input the linked list of envirnment
 */
void c_exit(char **string, list_t *env)
{
	free_double_p(string);
	free_linked_list(env);
	_exit(0);
}

/**
 * _execve - execute command user typed into shell
 * @s: command user typed
 * @env: environmental variable
 * @num: nth user command; to be used in error message
 * Return: 0 on success
 */
int _execve(char **st, list_t *env, int num)
{
	char *holder;
	int status = 0, t = 0;
	pid_t pid;

	if (access(s[0], F_OK) == 0)
	{
		holder = st[0];
		t = 1;
	}
	else
		holder = _which(st[0], env);
	if (access(holder, X_OK) != 0)
	{
		not_found(s[0], num, env);
		free_double_p(st);
		return (127);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(holder, st, NULL) == -1)
			{
				not_found(s[0], num, env);
				c_exit(st, env);
			}
		}
		else
		{
			wait(&status);
			free_double_p(st);
			if (t == 0)
				free(holder);
		}
	}
	return (0);
}
