#include "shell.h"

/**
 * _size - returns number of delim
 * @str: user's command typed into shell
 * @delm: delimeter (e.g. " ");
 * Return: number of tokens
 */
int _size(char *str, char delm)
{
	int a = 0, num_delm = 0;

	while (str[a] != '\0')
	{
		if (str[a] == delm)
		{
			num_delm++;
		}
		a++;
	}
	return (num_delm);
}


/**
 * _tok - tokenizes a string even the continuous delim with empty string
 * (e.g. path --> ":/bin::/bin/usr" )
 * @str: user's command typed into shell
 * @delm: delimeter (e.g. " ");
 * Return: an array of tokens (e.g. {"\0", "/bin", "\0", "/bin/usr"}
 * (purpose is to have which command look through current directory if ":")
 */
char **_tok(char *string, char *delim)
{
	int buffsize = 0, p = 0, si = 0, i = 0, len = 0, se = 0;
	char **toks = NULL, d_ch;

	d_ch = delim[0];
	buffsize = _size(string, d_ch);
	toks = malloc(sizeof(char *) * (buffsize + 2));
	if (toks == NULL)
		return (NULL);

	while (string[se] != '\0')
		se++;
	while (si < se)
	{
		len = t_strlen(string, si, d_ch);
		toks[p] = malloc(sizeof(char) * (len + 1));
		if (toks[p] == NULL)
			return (NULL);
		i = 0;
		while ((string[si] != d_ch) &&
		       (string[si] != '\0'))
		{
			toks[p][i] = string[si];
			i++;
			si++;
		}
		toks[p][i] = '\0';
		p++;
		si++;
	}
	toks[p] = NULL;
	return (toks);
}
