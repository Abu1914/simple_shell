#include "shell.h"

/**
 * _swapchar - swaps | and & for non printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *_swapchar(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * _addnodes - add Seperators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void _addnodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = _swapchar(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			Add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			Add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	line = strtok(input, ";|&");
	do {
		line = _swapchar(line, 1);
		Add_line_node_end(head_l, line);
		line = strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _gonext - go to the next Command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @data: data structure
 * Return: no return
 */
void _gonext(sep_list **list_s, line_list **list_l, data_shell *data)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (data->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * _splitcommands - splits command lines according to
 * The seperators ;, | and &, and executes them
 *
 * @data: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int _splitcommands(data_shell *data, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	_addnodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;
	while (list_l != NULL)
	{
		data->input = list_l->line;
		data->args = _splitline(data->input);
		loop = _execline(data);
		free(data->args);

		if (loop == 0)
			break;

		_gonext(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	Free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * _splitline - Tokenizes the inputed string
 *
 * @input: input string
 * Return: string splitted
 */
char **_splitline(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
