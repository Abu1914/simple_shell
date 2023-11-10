#include "shell.h"

/**
 * main - creates a simple shell
 * @ac: argument count
 * @av: argument vectors
 * @env: environmental variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	prompt(env);

	return (0);
}
