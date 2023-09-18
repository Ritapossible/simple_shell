#include "x_shell.h"

/**
 * read_line - This helps to read the input string.
 *
 * @x_eof: This returns value of getline function.
 * Return: Always input string.
 */
char *read_line(int *x_eof)
{
	char *input_x = NULL;
	size_t buffer_size = 0;

	*x_eof = getline(&input_x, &buffer_size, stdin);

	return (input_x);
}
