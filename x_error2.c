#include "x_shell.h"

/**
 * error_env - The error message for environment in get_env.
 * @datash: The data relevant (Counter, Arguments).
 * Return: Always return error message.
 */

char *error_env(data_shell *datash)
{
	int len;
	char *x_error;
	char *ver_x_str;
	char *msg;

	ver_x_str = x_itoa(datash->counter_x);
	msg = ": Unable to add/remove from environment\n";
	len = x_strlen(datash->argv[0]) + x_strlen(ver_x_str);
	len += x_strlen(datash->args[0]) + x_strlen(msg) + 4;
	x_error = malloc(sizeof(char) * (len + 1));
	if (x_error == 0)
	{
		free(x_error);
		free(ver_x_str);
		return (NULL);
	}

	x_strcpy(x_error, datash->argv[0]);
	x_strcat(x_error, ": ");
	x_strcat(x_error, ver_x_str);
	x_strcat(x_error, ": ");
	x_strcat(x_error, datash->args[0]);
	x_strcat(x_error, msg);
	x_strcat(x_error, "\0");
	free(ver_x_str);

	return (x_error);
}


/**
 * error_path_126 - The error msg for the path and failure denied permission.
 * @datash: The data relevant (Counter, Arguments).
 *
 * Return: Return the error string.
 */
char *error_path_126(data_shell *datash)
{
	int len;
	char *ver_x_str;
	char *x_error;

	ver_x_str = x_itoa(datash->counter_x);
	len = x_strlen(datash->argv[0]) + x_strlen(ver_x_str);
	len += x_strlen(datash->args[0]) + 24;
	x_error = malloc(sizeof(char) * (len + 1));
	if (x_error == 0)
	{
		free(x_error);
		free(ver_x_str);
		return (NULL);
	}
	x_strcpy(x_error, datash->argv[0]);
	x_strcat(x_error, ": ");
	x_strcat(x_error, ver_x_str);
	x_strcat(x_error, ": ");
	x_strcat(x_error, datash->args[0]);
	x_strcat(x_error, ": Permission denied\n");
	x_strcat(x_error, "\0");
	free(ver_x_str);
	return (x_error);
}
