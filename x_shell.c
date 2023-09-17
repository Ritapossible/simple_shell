#include "x_shell.h"

/**
 * free_data - Frees the data struct.
 *
 * @datash: The data structure.
 * Return: Always return nothing.
 */

void free_data(data_shell *datash)
{
	unsigned int j;

	for (j = 0; datash->_enviro[j]; j++)
	{
		free(datash->_enviro[j]);
	}

	free(datash->_enviro);
	free(datash->pid);
}

/**
 * set_data - Initialize data the structure.
 *
 * @datash: The data structure.
 * @argv: Argument vector.
 * Return: Return nothing.
 */

void set_data(data_shell *datash, char **argv)
{
	unsigned int j;

	datash->argv = argv;
	datash->input_x = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter_x = 1;

	for (j = 0; enviro[j]; j++)
		;

	datash->_enviro = malloc(sizeof(char *) * (j + 1));

	for (j = 0; enviro[j]; j++)
	{
		datash->_enviro[j] = x_strdup(enviro[j]);
	}

	datash->_enviro[j] = NULL;
	datash->pid = x_itoa(getpid());
}

/**
 * main - The entry point of the code.
 *
 * @argc: The argument count.
 * @argv: Argument vector
 *
 * Return: Return 0 on success.
 */
int main(int argc, char **argv)
{
	data_shell datash;
	(void) argc;

	signal(SIGINT, get_x_sigint);
	set_data(&datash, argv);
	x_shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}

