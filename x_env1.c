#include "x_shell.h"

/**
 * cmp_env_name - This helps to compare env variables names
 * with the name passed.
 * @env_name: The name of the environment variable.
 * @name: The name passed.
 *
 * Return: Always return 0 when not equal. Or another value if they are.
 */
int cmp_env_name(const char *env_name, const char *name)
{
	int m;

	for (m = 0; env_name[m] != '='; m++)
	{
		if (env_name[m] != name[m])
		{
			return (0);
		}
	}

	return (m + 1);
}

/**
 * _getenv - This helps to get an environment variable.
 * @name: The name of the environment variable.
 * @_enviro: The environment variable.
 *
 * Return: The value of the enviro variable if is found.
 * In other case, simply return NULL.
 */
char *_getenv(const char *name, char **_enviro)
{
	char *pter_env;
	int m, move;

	pter_env = NULL;
	move = 0;

	for (m = 0; _enviro[m]; m++)
	{
		move = cmp_env_name(_enviro[m], name);
		if (move)
		{
			pter_env = _enviro[m];
			break;
		}
	}

	return (pter_env + move);
}

/**
 * _env - This helps to print the evironment variables.
 *
 * @datash: The data relevant.
 * Return:  On success return 1.
 */
int _env(data_shell *datash)
{
	int m, n;

	for (m = 0; datash->_enviro[m]; m++)
	{

		for (n = 0; datash->_enviro[m][n]; n++)
			;

		write(STDOUT_FILENO, datash->_enviro[m], n);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
