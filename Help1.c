#include "shell.h"

/**
 * help - help information for builtin help.
 * Return: No return
 */
void help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, str_len(help));
}
/**
 * help_alias - help information for bulitin alias.
 * Return: No return
 */
void help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}
/**
 * help_cd - help information for builtin alias.
 * Return: No return
 */
void help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}
