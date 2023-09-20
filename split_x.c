#include "x_shell.h"
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * swap_char - This helps to swap | and & for non-printed characters.
 *
 * @input_x: The input string.
 * @bool_x: The type of swap.
 * Return:Always return swapped string.
 */
char *swap_char(char *input_x, int bool_x)
{
	int j;

	if (bool_x == 0)
	{
		for (j = 0; input_x[j]; j++)
		{
			if (input_x[j] == '|')
			{
				if (input_x[j + 1] != '|')
					input_x[j] = 16;
				else
					j++;
			}

			if (input_x[j] == '&')
			{
				if (input_x[j + 1] != '&')
					input_x[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; input_x[j]; j++)
		{
			input_x[j] = (input_x[j] == 16 ? '|' : input_x[j]);
			input_x[j] = (input_x[j] == 12 ? '&' : input_x[j]);
		}
	}
	return (input_x);
}

/**
 * add_nodes - This helps to add separators and command lines in the lists.
 *
 * @head_x: The head of separator list.
 * @head_l: The head of command lines list.
 * @input_x: The input string.
 * Return: Return nothing.
 */
void add_nodes(sep_list **head_x, line_list **head_l, char *input_x)
{
	int j;
	char *lin;

	input_x = swap_char(input_x, 0);

	for (j = 0; input_x[j]; j++)
	{
		if (input_x[j] == ';')
			add_sep_node_end(head_x, input_x[j]);

		if (input_x[j] == '|' || input_x[j] == '&')
		{
			add_sep_node_end(head_x, input_x[j]);
			j++;
		}
	}

	lin = x_strtok(input_x, ";|&");
	do {
		lin = swap_char(lin, 1);
		add_line_node_end(head_l, lin);
		lin = x_strtok(NULL, ";|&");
	} while (lin != NULL);

}

/**
 * go_next - This helps to go the next command line stored.
 *
 * @list_x: The separator list.
 * @list_l: The command line list.
 * @datash: The data structure.
 * Return: Return Nothing.
 */
void go_next(sep_list **list_x, line_list **list_l, data_shell *datash)
{
	int loop_sept;
	sep_list *ls_x;
	line_list *ls_l;

	loop_sept = 1;
	ls_x = *list_x;
	ls_l = *list_l;

	while (ls_x != NULL && loop_sept)
	{
		if (datash->status == 0)
		{
			if (ls_x->separator_x == '&' || ls_x->separator_x == ';')
				loop_sept = 0;
			if (ls_x->separator_x == '|')
				ls_l = ls_l->next, ls_x = ls_x->next;
		}
		else
		{
			if (ls_x->separator_x == '|' || ls_x->separator_x == ';')
				loop_sept = 0;
			if (ls_x->separator_x == '&')
				ls_l = ls_l->next, ls_x = ls_x->next;
		}
		if (ls_x != NULL && !loop_sept)
			ls_x = ls_x->next;
	}

	*list_x = ls_x;
	*list_l = ls_l;
}

/**
 * split_commands - This splits command lines according to
 * the separators ;, | and &, and executes them.
 *
 * @datash: This data structure.
 * @input_x: The input string.
 * Return: Return 0 to exit, 1 to continue.
 */
int split_commands(data_shell *datash, char *input_x)
{

	sep_list *head_x, *list_x;
	line_list *head_l, *list_l;
	int xloop;

	head_x = NULL;
	head_l = NULL;

	add_nodes(&head_x, &head_l, input_x);

	list_x = head_x;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input_x = list_l->line_x;
		datash->args = split_line(datash->input_x);
		xloop = exec_line(datash);
		free(datash->args);

		if (xloop == 0)
			break;

		go_next(&list_x, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_x);
	free_line_list(&head_l);

	if (xloop == 0)
		return (0);
	return (1);
}

/**
 * split_line - This tokenizes the input string.
 *
 * @input_x: The input string.
 * Return: The string splitted.
 */
char **split_line(char *input_x)
{
	size_t bufsize;
	size_t j;
	char **tokens;
	char *token;

	bufsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bufsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = x_strtok(input_x, TOK_DELIM);
	tokens[0] = token;

	for (j = 1; token != NULL; j++)
	{
		if (j == bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = x_reallocdp(tokens, j, sizeof(char *) * bufsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = x_strtok(NULL, TOK_DELIM);
		tokens[j] = token;
	}

	return (tokens);
}
