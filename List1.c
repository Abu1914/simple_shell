#include "shell.h"

/**
 * Add_sep_node_end - adds a separator at the end
 * of a sep_list.
 * @h: h of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the h.
 */
sep_list *Add_sep_node_end(sep_list **h, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*h);
}

/**
 * free_sep_list - frees a sep_list
 * @h: h of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **h)
{
	sep_list *temp;
	sep_list *curr;

	if (h != NULL)
	{
		curr = *h;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*h = NULL;
	}
}

/**
 * Add_line_node_end - adds a command line at end
 * of a line_list.
 * @h: h of the linked list.
 * @line: command line.
 * Return: Address of the h.
 */
line_list *Add_line_node_end(line_list **h, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*h);
}

/**
 * Free_line_list - frees a line_list
 * @h: h of the linked list.
 * Return: No return.
 */
void Free_line_list(line_list **h)
{
	line_list *temp;
	line_list *curr;

	if (h != NULL)
	{
		curr = *h;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*h = NULL;
	}
}
