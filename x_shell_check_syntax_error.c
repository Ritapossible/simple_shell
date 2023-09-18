#include "x_shell.h"

/**
 * repeated_char - This counts the repetitions of a character.
 *
 * @input_x: The input string.
 * @i: The index.
 * Return: Return the repetitions.
 */
int repeated_char(char *input_x, int i)
{
	if (*(input_x - 1) == *input_x)
		return (repeated_char(input_x - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - This finds syntax errors.
 *
 * @input_x: The input string.
 * @i: The index.
 * @last_x: The last char read.
 * Return: Return the index of error. Or 0 when there are no errors.
 */
int error_sep_op(char *input_x, int i, char last_x)
{
	int count;

	count = 0;
	if (*input_x == '\0')
		return (0);

	if (*input_x == ' ' || *input_x == '\t')
		return (error_sep_op(input_x + 1, i + 1, last_x));

	if (*input_x == ';')
		if (last_x == '|' || last_x == '&' || last_x == ';')
			return (i);

	if (*input_x == '|')
	{
		if (last_x == ';' || last_x == '&')
			return (i);

		if (last_x == '|')
		{
			count = repeated_char(input_x, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input_x == '&')
	{
		if (last_x == ';' || last_x == '|')
			return (i);

		if (last_x == '&')
		{
			count = repeated_char(input_x, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input_x + 1, i + 1, *input_x));
}

/**
 * first_char - This finds index of the first character.
 *
 * @input_x: The input string.
 * @i: The index.
 * Return: Always return 1 if there is an error. Or 0 in other case.
 */
int first_char(char *input_x, int *i)
{

	for (*i = 0; input_x[*i]; *i += 1)
	{
		if (input_x[*i] == ' ' || input_x[*i] == '\t')
			continue;

		if (input_x[*i] == ';' || input_x[*i] == '|' || input_x[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - This helps to print when a syntax error is found.
 *
 * @datash: The data structure/relevance.
 * @input_x: The input string.
 * @i: The index of the error.
 * @bool_x: This controls msg error.
 * Return: Return Nothing.
 */
void print_syntax_error(data_shell *datash, char *input_x, int i, int bool_x)
{
	char *msg, *msg2, *msg3, *error, *counter_x;
	int len;

	if (input_x[i] == ';')
	{
		if (bool_x == 0)
			msg = (input_x[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input_x[i - 1] == ';' ? ";;" : ";");
	}

	if (input_x[i] == '|')
		msg = (input_x[i + 1] == '|' ? "||" : "|");

	if (input_x[i] == '&')
		msg = (input_x[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter_x = x_itoa(datash->counter_x);
	len = x_strlen(datash->argv[0]) + x_strlen(counter_x);
	len += x_strlen(msg) + x_strlen(msg2) + x_strlen(msg3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter_x);
		return;
	}
	x_strcpy(error, datash->argv[0]);
	x_strcat(error, ": ");
	x_strcat(error, counter_x);
	x_strcat(error, msg2);
	x_strcat(error, msg);
	x_strcat(error, msg3);
	x_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter_x);
}

/**
 * check_syntax_error - The intermediate function to
 * find and print a syntax error.
 *
 * @datash: The data structure.
 * @input_x: The input string.
 * Return: Always return 1 if there is an error. 0 if there is none.
 */
int check_syntax_error(data_shell *datash, char *input_x)
{
	int x_begin = 0;
	int n_char = 0;
	int m = 0;

	n_char = first_char(input_x, &x_begin);
	if (n_char == -1)
	{
		print_syntax_error(datash, input_x, x_begin, 0);
		return (1);
	}

	m = error_sep_op(input_x + x_begin, 0, *(input_x + x_begin));
	if (m != 0)
	{
		print_syntax_error(datash, input_x, x_begin + m, 1);
		return (1);
	}

	return (0);
}
