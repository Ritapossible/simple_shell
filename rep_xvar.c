#include "x_shell.h"

/**
 * check_env - This checks if the typed variable is an env variable.
 *
 * @head: The head of linked list.
 * @in: The input string.
 * @data: The data structure.
 * Return: Return Nothing.
 */
void check_env(r_var **head, char *in, data_shell *data)
{
	int xrow, chra, n, lval;
	char **_envr;

	_envr = data->_enviro;
	for (xrow = 0; _envr[xrow]; xrow++)
	{
		for (n = 1, chra = 0; _envr[xrow][chra]; chra++)
		{
			if (_envr[xrow][chra] == '=')
			{
				lval = x_strlen(_envr[xrow] + chra + 1);
				add_rvar_node(head, n, _envr[xrow] + chra + 1, lval);
				return;
			}

			if (in[n] == _envr[xrow][chra])
				n++;
			else
				break;
		}
	}

	for (n = 0; in[n]; n++)
	{
		if (in[n] == ' ' || in[n] == '\t' || in[n] == ';' || in[n] == '\n')
			break;
	}

	add_rvar_node(head, n, NULL, 0);
}

/**
 * check_vars - This checks if the typed variable is $$ or $?.
 *
 * @head: The head of the linked list.
 * @in: The input string.
 * @str: The last status of the Shell.
 * @data: The data structure.
 * Return: Return Nothing.
 */
int check_vars(r_var **head, char *in, char *str, data_shell *data)
{
	int m, lst, xpd;

	lst = x_strlen(str);
	xpd = x_strlen(data->pid);

	for (m = 0; in[m]; m++)
	{
		if (in[m] == '$')
		{
			if (in[m + 1] == '?')
				add_rvar_node(head, 2, str, lst), m++;
			else if (in[m + 1] == '$')
				add_rvar_node(head, 2, data->pid, xpd), m++;
			else if (in[m + 1] == '\n')
				add_rvar_node(head, 0, NULL, 0);
			else if (in[m + 1] == '\0')
				add_rvar_node(head, 0, NULL, 0);
			else if (in[m + 1] == ' ')
				add_rvar_node(head, 0, NULL, 0);
			else if (in[m + 1] == '\t')
				add_rvar_node(head, 0, NULL, 0);
			else if (in[m + 1] == ';')
				add_rvar_node(head, 0, NULL, 0);
			else
				check_env(head, in + m, data);
		}
	}

	return (m);
}

/**
 * replaced_input - This replaces string into the variables.
 *
 * @head: The head of the linked list.
 * @input_x: The input string.
 * @xnew_input: The new input string (replaced).
 * @xlen: The new length.
 * Return: The replaced string.
 */
char *replaced_input(r_var **head, char *input_x, char *xnew_input, int xlen)
{
	r_var *index;
	int m, n, o;

	index = *head;
	for (n = m = 0; m < xlen; m++)
	{
		if (input_x[n] == '$')
		{
			if (!(index->len_xvar) && !(index->len_xval))
			{
				xnew_input[m] = input_x[n];
				n++;
			}
			else if (index->len_xvar && !(index->len_xval))
			{
				for (o = 0; o < index->len_xvar; o++)
					n++;
				m--;
			}
			else
			{
				for (o = 0; o < index->len_xval; o++)
				{
					xnew_input[m] = index->xval[o];
					m++;
				}
				n += (index->len_xvar);
				m--;
			}
			index = index->next;
		}
		else
		{
			xnew_input[m] = input_x[n];
			n++;
		}
	}

	return (xnew_input);
}

/**
 * rep_var - This call functions to replace string into varables.
 *
 * @input_x: The input string.
 * @datash: The data structure.
 * Return: Always return replaced string.
 */
char *rep_var(char *input_x, data_shell *datash)
{
	r_var *head, *index;
	char *status, *new_x_input;
	int oldlen, newlen;

	status = x_itoa(datash->status);
	head = NULL;

	oldlen = check_vars(&head, input_x, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input_x);
	}

	index = head;
	newlen = 0;

	while (index != NULL)
	{
		newlen += (index->len_xval - index->len_xvar);
		index = index->next;
	}

	newlen += oldlen;

	new_x_input = malloc(sizeof(char) * (newlen + 1));
	new_x_input[newlen] = '\0';

	new_x_input = replaced_input(&head, input_x, new_x_input, newlen);

	free(input_x);
	free(status);
	free_rvar_list(&head);

	return (new_x_input);
}
