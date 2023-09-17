#include "x_shell.h"

/**
 * exit_x_shell - Exits the x shell.
 *
 * @datash: The data relevant (status and args).
 * Return: Return 0 on success.
 */

int exit_x_shell(data_shell *datash)
{
	unsigned int status;
	int x_digit;
	int x_str_len;
	int large_number;

	if (datash->args[1] != NULL)
	{
		status = _atoi(datash->args[1]);
		x_digit = _xdigit(datash->args[1]);
		x_str_len = _xstrlen(datash->args[1]);
		large_number = status > (unsigned int)INT_MAX;
		if (!x_digit || x_str_len > 10 || large_number)
		{
			get_x_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (status % 256);
	}
	return (0);
}
