#include "x_shell.h"

/**
 * get_x_error - Gets/calls error according the builtin, syntax or permission.
 * @datash: The data structure that contains the arguments.
 * @err_val: The x shell error value.
 * Return: Always return error.
 */

int get_x_error(data_shell *datash, int err_val)
{
	char *x_error = NULL;

	if (err_val == -1)
	{
		x_error = error_env(datash);
	} else if (err_val == 126)
	{
		x_error = error_path_126(datash);
	} else if (err_val == 127)
	{
		x_error = error_not_found(datash);
	} else if (err_val == 2)
	{
		if (x_strcmp("exit", datash->args[0]) == 0)
		{
			x_error = error_exit_x_shell(datash);
		} else if (x_strcmp("cd", datash->args[0]) == 0)
		{
			x_error = error_get_cd(datash);
		}
	}
	if (x_error)
	{
		write(STDERR_FILENO, x_error, x_strlen(x_error));
		free(x_error);
	}

	datash->status = err_val;
	return (err_val);
}
