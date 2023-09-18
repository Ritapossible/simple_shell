#include "x_shell.h"

/**
 * bring_line - This assigns the line var for get_line.
 * @lineptr_x: The buffer that store the input string.
 * @buffer: The string that is been called to line
 * @i: The size of line.
 * @j: The size of buffer.
 */
void bring_line(char **lineptr_x, size_t *i, char *buffer, size_t j)
{

	if (*lineptr_x == NULL)
	{
		if  (j > BUFSIZ)
			*i = j;

		else
			*i = BUFSIZ;
		*lineptr_x = buffer;
	}
	else if (*i < j)
	{
		if (j > BUFSIZ)
			*i = j;
		else
			*i = BUFSIZ;
		*lineptr_x = buffer;
	}
	else
	{
		x_strcpy(*lineptr_x, buffer);
		free(buffer);
	}
}
/**
 * get_line - This read input from stream.
 * @lineptr_x: The buffer that stores the input.
 * @i: The size of lineptr_x.
 * @stream: The stream to read from.
 * Return: The number of bytes.
 */
ssize_t get_line(char **lineptr_x, size_t *i, FILE *stream)
{
	int j;
	static ssize_t input_x;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input_x == 0)
		fflush(stream);
	else
		return (-1);
	input_x = 0;

	buffer = malloc(sizeof(char) * BUFSIZ);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		j = read(STDIN_FILENO, &t, 1);
		if (j == -1 || (j == 0 && input_x == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && input_x != 0)
		{
			input_x++;
			break;
		}
		if (input_x >= BUFSIZ)
			buffer = x_realloc(buffer, input_x, input_x + 1);
		buffer[input_x] = t;
		input_x++;
	}
	buffer[input_x] = '\0';
	bring_line(lineptr_x, i, buffer, input_x);
	retval = input_x;
	if (j != 0)
		input_x = 0;
	return (retval);
}
