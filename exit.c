#include "shell.h"

/**
 * _atoi - custom atoi converts string to int
 * @s: string
 * Return: number if success, -1 if string contains non-numbers
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + (s[i] - '0');
		if (s[i] > '9' || s[i] < '0')
			return (-1);
		i++;
	}
	return (num);
}

/**
 * __exit - frees user input and then exits main program with a value
 * @string: user's command into shell (e.g. "exit 99")
 * @env: bring in environmental variable to free at error
 * @num: bring in nth user command line input to print in error message
 * @command: bring in command to free
 * Return: 0 if success 2 if fail
 */
int __exit(char **string, list_t *env, int num, char **command)
{
	int e_value = 0;

	if (string[1] != NULL)
		e_value = _atoi(string[1]);

	if (e_value == -1)
	{
		wrong_number(string[1], num, env);
		free_double_p(string);
		return (2);
	}
	free_double_p(string);
	free_linked_list(env);
	if (command != NULL)
		free_double_p(command);
	exit(e_value);
}
