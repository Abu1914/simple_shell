#include "shell.h"

/**
 * n_found - write error ("sh: 1: lss: not found")
 * @string: user's typed command
 * @c_n: nth user's typed command
 * @env: bring in environmental variables linked list to write shell name
 */
void n_found(char *string, int c_n, list_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = _getenv("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = to_string(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	count = 0;
	while (string[count] != '\0')
		count++;
	write(STDOUT_FILENO, string, count);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "not found\n", 10);
}

/**
 * not_cd_to - write error ("sh: 2: cd: can't cd to xyz")
 * @string: user's typed argument after the cmd cd
 * @c_n: nth user's typed command
 * @env: bring in environmental variables linked list to write shell name
 */
void not_cd_to(char *string, int c_n, list_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = _getenv("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = to_string(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "cd: can't cd to ", 16);
	count = 0;
	while (string[count] != '\0')
		count++;
	write(STDOUT_FILENO, string, count);
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * wrong_number - write error ("sh: 3: exit: Illegal number abc (or -1)")
 * @string: user's typed argument after the cmd exit
 * @c_n: nth user's typed command
 * @env: bring in environmental variables linked list to write shell name
 */
void wrong_number(char *string, int c_n, list_t *env)
{
	int count = 0;
	char *shell = NULL, *num = NULL;

	shell = _getenv("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = to_string(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "exit: Illegal number: ", 22);
	count = 0;
	while (string[count] != '\0')
		count++;
	write(STDOUT_FILENO, string, count);
	write(STDOUT_FILENO, "\n", 1);
}
