#include "shell.h"

/**
 * _findenv - find given environmental variable in linked list
 * @env: environmental variable linked list
 * @string: variable name
 * Return: idx of node in linked list
 */
int _findenv(list_t *env, char *string)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == string[j]) /* find desired env variable */
			j++;
		if (string[j] == '\0') /* if matches entirely, break, return idx */
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}

/**
 * _unsetenv - remove node in environmental linked list
 * @env: linked list
 * @string: user's typed in command (e.g. "unsetenv MAIL")
 * Return: 0 on success
 */
int _unsetenv(list_t **env, char **string)
{
	int index = 0, j = 0;

	if (string[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_p(string);
		return (-1);
	}
	index = _findenv(*env, string[1]); /* get idx of node to delete */
	free_double_p(string);
	if (index == -1) /* check if index errored */
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	j = delete_nodeint_at_index(env, index); /* delete node */
	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}

/**
 * _setenv - create or modify existing environmental variable in linked list
 * @env: linked list
 * @string: user's typed in command (e.g. "setenv USER Superman")
 * Return: 0 on success, 1 on fail
 */
int _setenv(list_t **env, char **string)
{
	int index = 0, j = 0;
	char *cat;
	list_t *holder;

	if (string[1] == NULL || string[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_p(string);
		return (-1);
	}
	cat = _strdup(string[1]); /* concatenate strings to be new node data */
	cat = _strcat(cat, "=");
	cat = _strcat(cat, string[2]);
	index = _findenv(*env, string[1]); /* find idx to traverse to node */
	if (index == -1)
	{
		add_end_node(env, cat); /* doesn't exist? create env var */
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var); /* else free malloced data */
		holder->var = _strdup(cat); /* assign to new malloced data */
	}
	free(cat);
	free_double_p(string);
	return (0);
}
