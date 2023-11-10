#include "shell.h"

/**
 * cd_strcat - concatenate two strings ignoring the first character ("~" in cd)
 * @dest: string to be appended to
 * @src: string to append
 * Return: concatenated string
 */
char *cd_strcat(char *dest, char *src)
{
	int len = 0;
	int len2 = 0;
	int total_len = 0;
	int b = 0;

	while (dest[len] != '\0')
	{
		len++;
		total_len++;
	}
	while (src[len2] != '\0')
	{
		len2++;
		total_len++;
	}

	dest = _realloc(dest, len, sizeof(char) * total_len + 1);

	b = 1;
	while (src[b] != '\0')
	{
		dest[len] = src[b];
		len++;
		b++;
	}
	dest[len] = '\0';

	return (dest);
}

/**
 * com_setenv - custom _setenv by concatenating string first before setting
 * @env: environmental variable linked list
 * @name: environmental variable name (e.g. "OLDPWD")
 * @dir: directory path (e.g. "/home/vagrant/directory1")
 * Return: 0 on success (e.g. "OLDPWD=/home/vagrant/directory1")
 */
int com_setenv(list_t **env, char *name, char *dir)
{
	int index = 0, b = 0;
	char *cat;
	list_t *holder;

	cat = _strdup(name);
	cat = cd_strcat(cat, "=");
	cat = cd_strcat(cat, dir);
	index = _findenv(*env, name);

	holder = *env;
	while (b < index)
	{
		holder = holder->next;
		b++;
	}
	free(holder->var);
	holder->var = _strdup(cat);
	free(cat);
	return (0);
}

/**
 * _cdonly - change directory to home
 * @env: bring in environmental linked list to update PATH and OLDPWD
 * @cur: bring in current working directotry
 */
void _cdonly(list_t *env, char *cur)
{
	char *home = NULL;

	home = _getenv("HOME", env);
	com_setenv(&env, "OLDPWD", cur);
	free(cur);
	if (access(home, F_OK) == 0)
		chdir(home);
	cur = NULL;
	cur = getcwd(cur, 0);
	com_setenv(&env, "PWD", cur);
	free(cur);
	free(home);
}
/**
 * cd_execute - executes the cd
 * @env: bring in environmental linked list to update PATH and OLDPWD
 * @cur: bring in current working directotry
 * @dir: bring in directory path to change to
 * @str: bring in the 1st argument to write out error
 * @num: bring in the line number to write out error
 * Return: 0 if success 2 if fail
 */
int cd_execute(list_t *env, char *cur, char *dir, char *str, int num)
{
	int i = 0;

	if (access(dir, F_OK) == 0)
	{
		com_setenv(&env, "OLDPWD", cur);
		free(cur);
		chdir(dir);
		cur = NULL;
		cur = getcwd(cur, 0);
		com_setenv(&env, "PWD", cur);
		free(cur);
	}
	else
	{
		not_cd_to(str, num, env);
		free(cur);
		i = 2;
	}
	return (i);
}

/**
 * _cd - change directory
 * @str: user's typed in command
 * @env: enviromental linked list to retrieve HOME and OLDPWD paths
 * @num: nth user command, to be used at error message
 * Return: 0 if success 2 if failed
 */
int _cd(char **str, list_t *env, int num)
{
	char *cur = NULL, *dir = NULL;
	int exit_stat = 0;

	cur = getcwd(cur, 0);
	if (str[1] != NULL)
	{
		if (str[1][0] == '~')
		{
			dir = _getenv("HOME", env);
			dir = _strcat(dir, str[1]);
		}
		else if (str[1][0] == '-')
		{
			if (str[1][1] == '\0')
				dir = _getenv("OLDPWD", env);
		}
		else
		{
			if (str[1][0] != '/')
			{
				dir = getcwd(dir, 0);
				dir = cd_strcat(dir, "/");
				dir = cd_strcat(dir, str[1]);
			}
			else
				dir = _strdup(str[1]);
		}
		exit_stat = cd_execute(env, cur, dir, str[1], num);
		free(dir);
	}
	else
		_cdonly(env, cur);
	free_double_p(str);
	return (exit_stat);
}
