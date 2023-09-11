#include "x-shell.h"

/**
 * get_x_builtin - The builtin that pass the command in the argument.
 * @cmd-x: The x command.
 * Return: The function pointer of the builtin command.
 */
int (*get_x_builtin(char *cmd-x))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_x_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_x_shell },
		{ "help", get_x_help },
		{ NULL, NULL }
	};
	int j;

	for (j= 0; builtin[j].name_x; j++)
	{
		if (_strcmp(builtin[j].name_x, cmd-x) == 0)
			break;
	}

	return (builtin[j].func_x);
}
