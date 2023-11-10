#include "shell.h"

/**
 * envlinked_list - creates a linked list from environmental variables
 * @env: environmental variables
 * Return: linked list
 */
list_t *envlinked_list(char **env)
{
	list_t *h;
	int a = 0;

	h = NULL;
	while (env[a] != NULL)
	{
		add_end_node(&h, env[a]);
		a++;
	}
	return (h);
}

/**
 * _env - prints environmental variables
 * @string: user's command into shell (i.e. "env")
 * @env: environmental variables
 * Return: 0 on success
 */
int _env(char **string, list_t *env)
{
	free_double_p(string);
	print_list(env);
	return (0);
}
