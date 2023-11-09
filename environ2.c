#include "shell.h"

/**
 * _copyinfo - Copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias
 */
char *_copyinfo(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = strlen(name);
	len_value = strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	strcpy(new, name);
	strcat(new, "=");
	strcat(new, value);
	strcat(new, "\0");

	return (new);
}

/**
 * _setenv - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @data: data structure (environ)
 * Return: No return
 */
void _setenv(char *name, char *value, data_shell *data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data->environ[i]; i++)
	{
		var_env = strdup(data->environ[i]);
		name_env = strtok(var_env, "=");
		if (strcmp(name_env, name) == 0)
		{
			free(data->environ[i]);
			data->environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	data->environ = reallocdp(data->environ, i, sizeof(char *) * (i + 2));
	data->environ[i] = copy_info(name, value);
	data->environ[i + 1] = NULL;
}

/**
 * set_env - Compares env variable names
 * with the name passed
 * @data: data relevant (env name and env value)
 *
 * Return: 1 on success
 */
int set_env(data_shell *data)
{
	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		get_error(data, -1);
		return (1);
	}

	_setenv(data->args[1], data->args[2], data);

	return (1);
}

/**
 * unset_env - deletes an environment variable
 *
 * @data: data relevant (env name)
 *
 * Return: 1 No success
 */
int unset_env(data_shell *data)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (data->args[1] == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->environ[i]; i++)
	{
		var_env = strdup(data->environ[i]);
		name_env = strtok(var_env, "=");
		if (strcmp(name_env, data->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(data, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = data->environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(data->environ[k]);
	free(data->environ);
	data->environ = realloc_environ;
	return (1);
}
