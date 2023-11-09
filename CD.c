#include "shell.h"

/**
 * _cddot - changes the parent directory.
 *
 * @data: data Relevant ( environ)
 *
 * Return: No return
 */
void _cddot(data_shell *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = str_dup(pwd);
	_setenv("OLDPWD", cp_pwd, data);
	dir = data->args[1];
	if (str_cmp(".", dir) == 0)
	{
		_setenv("PWD", cp_pwd, data);
		free(cp_pwd);
		return;
	}
	if (str_cmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	_revstring(cp_strtok_pwd);
	cp_strtok_pwd = str_tok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = str_tok(NULL, "\0");
		if (cp_strtok_pwd != NULL)
			_revstring(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		_setenv("PWD", cp_strtok_pwd, data);
	}
	else
	{
		chdir("/");
		_setenv("PWD", "/", data);
	}
	data->status = 0;
	free(cp_pwd);
}

/**
 * _cdto - Changes a given directory
 * by the User
 *
 * @data: data Relevant (directories)
 * Return: No return
 */
void _cdto(data_shell *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		get_error(data, 2);
		return;
	}

	cp_pwd = str_dup(pwd);
	_setenv("OLDPWD", cp_pwd, data);

	cp_dir = str_dup(dir);
	_setenv("PWD", cp_dir, data);

	free(cp_pwd);
	free(cp_dir);

	data->status = 0;

	chdir(dir);
}

/**
 * _cdprevious - Changes the previous directory
 *
 * @data: data Relevant ( environ)
 * Return: No return
 */
void _cdprevious(data_shell *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = str_dup(pwd);

	p_oldpwd = _getenv("OLDPWD", data->environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
	cp_oldpwd = str_dup(p_oldpwd);

	_setenv("OLDPWD", cp_pwd, data);

	if (chdir(cp_oldpwd) == -1)
		_setenv("PWD", cp_pwd, data);
	else
		_setenv("PWD", cp_oldpwd, data);

	p_pwd = _getenv("PWD", data->environ);

	write(STDOUT_FILENO, p_pwd, str_len(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data->status = 0;

	chdir(p_pwd);
}

/**
 * cd_tohome -Changes directory to home
 *
 * @data: data Relevant (environ)
 * Return: No return
 */
void cd_tohome(data_shell *data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = str_dup(pwd);

	home = _getenv("HOME", data->environ);

	if (home == NULL)
	{
		_setenv("OLDPWD", p_pwd, data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data, 2);
		free(p_pwd);
		return;
	}

	_setenv("OLDPWD", p_pwd, data);
	_setenv("PWD", home, data);
	free(p_pwd);
	data->status = 0;
}
