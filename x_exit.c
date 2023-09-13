#include "x-shell.h"

/**
 * exit_x_shell - Exits the x shell.
 *
 * @datash: The data relevant (status and args).
 * Return: Return 0 on success.
 */

int exit_x_shell(data_shell *datash)
{
	unsigned int x_status;
	int x_digit;
	int x_str_len;
	int large_number;

	if (datash->args[1] != NULL)
	{
		x_status = _atoi(datash->args[1]);
		x_digit = _xdigit(datash->args[1]);
		x_str_len = _xstrlen(datash->args[1]);
		large_number = x_status > (unsigned int)INT_MAX;
		if (!x_digit || x_str_len > 10 || large_number)
		{
			get_x_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (x_status % 256);
	}
	return (0);
}
