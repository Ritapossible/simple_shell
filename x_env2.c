#include "x_shell.h"

/**
 * copy_info - This helps to copy info to create
 * a new environment or alias.
 * @name: The name environment or alias.
 * @x_value: The value environment or alias.
 *
 * Return: The new environment or alias.
 */
char *copy_info(char *name, char *x_value)
{
	char *xnew;
	int len_name, len_value, length;

	len_name = x_strlen(name);
	len_value = x_strlen(x_value);
	length = len_name + len_value + 2;
	xnew = malloc(sizeof(char) * (length));
	x_strcpy(xnew, name);
	x_strcat(xnew, "=");
	x_strcat(xnew, x_value);
	x_strcat(xnew, "\0");

	return (xnew);
}

/**
 * set_env - This sets an environment variable.
 *
 * @name: The name of the environment variable.
 * @x_value: The value of the environment variable.
 * @datash: The data structure (enviro).
 * Return: Return Nothing.
 */
void set_env(char *name, char *x_value, data_shell *datash)
{
	int m;
	char *x_var_env, *name_env;

	for (m = 0; datash->_enviro[m]; m++)
	{
		x_var_env = x_strdup(datash->_enviro[m]);
		name_env = x_strtok(x_var_env, "=");
		if (x_strcmp(name_env, name) == 0)
		{
			free(datash->_enviro[m]);
			datash->_enviro[m] = copy_info(name_env, x_value);
			free(x_var_env);
			return;
		}
		free(x_var_env);
	}

	datash->_enviro = x_reallocdp(datash->_enviro, m, sizeof(char *) * (m + 2));
	datash->_enviro[m] = copy_info(name, x_value);
	datash->_enviro[m + 1] = NULL;
}

/**
 * _setenv -This helps to compare env variables names
 * with the name passed.
 * @datash: The data relevant (env name and env value)
 *
 * Return: Always return 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_x_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - This helps to delete a environment variable
 *
 * @datash: The data relevant (environment name)
 *
 * Return: Always return 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_enviro;
	char *x_var_env, *name_env;
	int m, n, o;

	if (datash->args[1] == NULL)
	{
		get_x_error(datash, -1);
		return (1);
	}
	o = -1;
	for (m = 0; datash->_enviro[m]; m++)
	{
		x_var_env = x_strdup(datash->_enviro[m]);
		name_env = x_strtok(x_var_env, "=");
		if (x_strcmp(name_env, datash->args[1]) == 0)
		{
			o = m;
		}
		free(x_var_env);
	}
	if (o == -1)
	{
		get_x_error(datash, -1);
		return (1);
	}
	realloc_enviro = malloc(sizeof(char *) * (m));
	for (m = n = 0; datash->_enviro[m]; m++)
	{
		if (m != o)
		{
			realloc_enviro[n] = datash->_enviro[m];
			n++;
		}
	}
	realloc_enviro[n] = NULL;
	free(datash->_enviro[o]);
	free(datash->_enviro);
	datash->_enviro = realloc_enviro;
	return (1);
}
