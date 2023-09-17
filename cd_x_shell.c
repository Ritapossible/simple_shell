#include "x_shell.h"

/**
 * cd_x_shell - This helps to change current directory.
 *
 * @datash: The data relevant.
 * Return: Always return 1 on success.
 */
int cd_x_shell(data_shell *datash)
{
	char *x_dir;
	int isx_home, isx_home2, isx_dash;

	x_dir = datash->args[1];

	if (x_dir != NULL)
	{
		isx_home = x_strcmp("$HOME", x_dir);
		isx_home2 = x_strcmp("~", x_dir);
		isx_dash = x_strcmp("--", x_dir);
	}

	if (x_dir == NULL || !isx_home || !isx_home2 || !isx_dash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (x_strcmp("-", x_dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (x_strcmp(".", x_dir) == 0 || x_strcmp("..", x_dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
