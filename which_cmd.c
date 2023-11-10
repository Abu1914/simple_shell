#include "shell.h"

/**
 * which_cmd - fleshes out command by appending it to a matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * @env: environmental variable
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *which_cmd(char *string, list_t *env)
{
	char *pth, *cat = NULL, **toks;
	int i = 0;

	pth = _getenv("PATH", env);
	toks = _tok(pth, ":");
	free(pth);

	i = 0;
	while (toks[i] != NULL)
	{
		if (toks[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = _strdup(toks[i]);
		cat = _strcat(cat, "/");
		cat = _strcat(cat, string);
		if (access(cat, F_OK) == 0)
		{
			free_double_p(toks);
			return (cat);
		}
		free(cat);
		i++;
	}
	free_double_p(toks);
	return (string);
}
