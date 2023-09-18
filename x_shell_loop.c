#include "x_shell.h"

/**
 * without_comment - This helps to delete comments from the input.
 *
 * @in_x: The input string.
 * Return: Always return input without comments.
 */
char *without_comment(char *in_x)
{
	int m, up_to_x;

	up_to_x = 0;
	for (m = 0; in_x[m]; m++)
	{
		if (in_x[m] == '#')
		{
			if (m == 0)
			{
				free(in_x);
				return (NULL);
			}

			if (in_x[m - 1] == ' ' || in_x[m - 1] == '\t' || in_x[m - 1] == ';')
				up_to_x = m;
		}
	}

	if (up_to_x != 0)
	{
		in_x = x_realloc(in_x, m, up_to_x + 1);
		in_x[up_to_x] = '\0';
	}

	return (in_x);
}

/**
 * x_shell_loop - The loop of x shell.
 * @datash: The data relevant (argv, input_x, args).
 *
 * Return: Return Nothing.
 */
void x_shell_loop(data_shell *datash)
{
	int x_loop, x_eof;
	char *input_x;

	x_loop = 1;
	while (x_loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input_x = read_line(&x_eof);
		if (x_eof != -1)
		{
			input_x = without_comment(input_x);
			if (input_x == NULL)
				continue;

			if (check_syntax_error(datash, input_x) == 1)
			{
				datash->status = 2;
				free(input_x);
				continue;
			}
			input_x = rep_var(input_x, datash);
			x_loop = split_commands(datash, input_x);
			datash->counter_x += 1;
			free(input_x);
		}
		else
		{
			x_loop = 0;
			free(input_x);
		}
	}
}
