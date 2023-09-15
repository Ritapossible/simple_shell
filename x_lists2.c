#include "x-shell.h"

/**
 * add_rvar_node - This helps to add a variable at the end
 * of a r_var list.
 * @head: The head of the linked list.
 * @lxvar: The length of the variable.
 * @xval: The value of the variable.
 * @lxval: The length of the value.
 * Return: Always return address of the head.
 */
r_var *add_rvar_node(r_var **head, int lxvar, char *xval, int lxval)
{
	r_var *new_x, *temp;

	new_x = malloc(sizeof(r_var));
	if (new_x == NULL)
		return (NULL);

	new_x->length_var = lxvar;
	new_x->value = value;
	new_x->length_val = lxval;

	new_x->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_x;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_x;
	}

	return (*head);
}

/**
 * free_rvar_list - This frees a r_var list.
 * @head: The head of the linked list.
 * Return: Return Nothing.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *current;

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
