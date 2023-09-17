#include "x_shell.h"

/**
 * strcat_cd - The function that appends a message for change directory error.
 *
 * @datash: The data relevant (directory).
 * @msg: The message to print.
 * @x_error: The output of the cd message.
 * @ver_x_str: The ounter lines.
 * Return: Always return error message.
 */

char *strcat_cd(data_shell *datash, char *msg, char *x_error, char *ver_x_str)
{
	char *is_illegal_flag;

	x_strcpy(x_error, datash->argv[0]);
	x_strcat(x_error, ": ");
	x_strcat(x_error, ver_x_str);
	x_strcat(x_error, ": ");
	x_strcat(x_error, datash->args[0]);
	x_strcat(x_error, msg);
	if (datash->args[1][0] == '-')
	{
		is_illegal_flag = malloc(3);
		is_illegal_flag[0] = '-';
		is_illegal_flag[1] = datash->args[1][1];
		is_illegal_flag[2] = '\0';
		x_strcat(x_error, is_illegal_flag);
		free(is_illegal_flag);
	}
	else
	{
		x_strcat(x_error, datash->args[1]);
	}

	x_strcat(x_error, "\n");
	x_strcat(x_error, "\0");
	return (x_error);
}

/**
 * error_get_cd - The error message for the change directory command.
 *
 * @datash: The data relevant (directory).
 * Return: Always return error message.
 */

char *error_get_cd(data_shell *datash)
{
	int len, length_id;
	char *x_error, *ver_x_str, *msg;

	ver_x_str = x_itoa(datash->counter_x);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		length_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		length_id = x_strlen(datash->args[1]);
	}

	len = x_strlen(datash->argv[0]) + x_strlen(datash->args[0]);
	len += x_strlen(ver_x_str) + x_strlen(msg) + length_id + 5;
	x_error = malloc(sizeof(char) * (len + 1));

	if (x_error == 0)
	{
		free(ver_x_str);
		return (NULL);
	}

	x_error = strcat_cd(datash, msg, x_error, ver_x_str);

	free(ver_x_str);

	return (x_error);
}

/**
 * error_not_found - The generic failure message for command not found.
 * @datash: The data relevant (Counter, Arguments).
 * Return: Always error message.
 */

char *error_not_found(data_shell *datash)
{
	int len;
	char *x_error;
	char *ver_x_str;

	ver_x_str = x_itoa(datash->counter_x);
	len = x_strlen(datash->argv[0]) + x_strlen(ver_x_str);
	len += x_strlen(datash->args[0]) + 16;
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
	x_strcat(x_error, ": not found\n");
	x_strcat(x_error, "\0");
	free(ver_x_str);
	return (x_error);
}

/**
 * error_exit_x_shell - The generic failure message for exit in get_x_exit.
 * @datash: The data relevant (Counter, Arguments).
 *
 * Return: Always return error message.
 */

char *error_exit_x_shell(data_shell *datash)
{
	int len;
	char *x_error;
	char *ver_x_str;

	ver_x_str = x_itoa(datash->counter_x);
	len = x_strlen(datash->argv[0]) + x_strlen(ver_x_str);
	len += x_strlen(datash->args[0]) + x_strlen(datash->args[1]) + 23;
	x_error = malloc(sizeof(char) * (len + 1));
	if (x_error == 0)
	{
		free(ver_x_str);
		return (NULL);
	}
	x_strcpy(x_error, datash->argv[0]);
	x_strcat(x_error, ": ");
	x_strcat(x_error, ver_x_str);
	x_strcat(x_error, ": ");
	x_strcat(x_error, datash->args[0]);
	x_strcat(x_error, ": Illegal number: ");
	x_strcat(x_error, datash->args[1]);
	x_strcat(x_error, "\n\0");
	free(ver_x_str);

	return (x_error);
}
