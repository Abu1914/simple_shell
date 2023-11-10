#include "shell.h"

/**
 * main - creates a simple shell
 * @argc: argument count
 * @argv: argument vectors
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
