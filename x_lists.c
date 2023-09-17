#include "x_shell.h"

/**
 * add_sep_node_end - This helps to add a separator found at the end
 * of a sep_list.
 * @head: The head of the linked list.
 * @sep_x: The separator found (; | &).
 * Return: Always return the address of the head.
 */

sep_list *add_sep_node_end(sep_list **head, char sep_x)
{
	sep_list *ptrn, *temp;

	ptrn = malloc(sizeof(sep_list));
	if (ptrn == NULL)
		return (NULL);

	ptrn->separator = sep_x;
	ptrn->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = ptrn;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = ptrn;
	}

	return (*head);
}

/**
 * free_sep_list - This frees a sep_list
 * @head: The head of the linked list.
 * Return: Return Nothing.
 */
void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - This helps to add a command line at the end
 * of a line_list.
 * @head: The head of the linked list.
 * @line_x: The x command line.
 * Return: Always return address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line_x)
{
	line_list *ptrn, *temp;

	ptrn = malloc(sizeof(line_list));
	if (ptrn == NULL)
		return (NULL);

	ptrn->line_x = line_x;
	ptrn->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = ptrn;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = ptrn;
	}

	return (*head);
}

/**
 * free_line_list - This frees a line_list.
 * @head: The head of the linked list.
 * Return: Return nothing.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
