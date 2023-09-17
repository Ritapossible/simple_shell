#include "x_shell.h"

/**
 * add_rvar_node - This helps to add a variable at the end
 * of a r_var list.
 * @head: The head of the linked list.
 * @len_var: The length of the variable.
 * @xval: The value of the variable.
 * @l_xval: The length of the value.
 * Return: Always return address of the head.
 */
r_var *add_rvar_node(r_var **head, int len_var, char *xval, int l_xval)
{
	r_var *ptrn, *temp;

	ptrn = malloc(sizeof(r_var));
	if (ptrn == NULL)
		return (NULL);

	ptrn->length_var = len_var;
	ptrn->value = value;
	ptrn->length_val = l_xval;

	new_x->next = NULL;
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
