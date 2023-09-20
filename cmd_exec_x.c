#include "x_shell.h"

/**
 * is_cdir - This helps to check ":" while it is in the current directory.
 * @x_path: The type char pointer character.
 * @i: The type integer pointer of index.
 * Return: Always return 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *x_path, int *i)
{
	if (x_path[*i] == ':')
		return (1);

	while (x_path[*i] != ':' && x_path[*i])
	{
		*i += 1;
	}

	if (x_path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - This locates a command.
 *
 * @cmd_x: The command name.
 * @_enviro: The environment variable.
 * Return: The location of the command.
 */
char *_which(char *cmd_x, char **_enviro)
{
	char *x_path, *ptr_path, *token_path, *dir;
	int len_dir, len_x_cmd, j;
	struct stat st;

	x_path = _getenv("PATH", _enviro);
	if (x_path)
	{
		ptr_path = x_strdup(x_path);
		len_x_cmd = x_strlen(cmd_x);
		token_path = x_strtok(ptr_path, ":");
		j = 0;
		while (token_path != NULL)
		{
			if (is_cdir(x_path, &j))
				if (stat(cmd_x, &st) == 0)
					return (cmd_x);
			len_dir = x_strlen(token_path);
			dir = malloc(len_dir + len_x_cmd + 2);
			x_strcpy(dir, token_path);
			x_strcat(dir, "/");
			x_strcat(dir, cmd_x);
			x_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = x_strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd_x, &st) == 0)
			return (cmd_x);
		return (NULL);
	}
	if (cmd_x[0] == '/')
		if (stat(cmd_x, &st) == 0)
			return (cmd_x);
	return (NULL);
}

/**
 * is_executable - This determines if is an executable file.
 *
 * @datash: This data structure.
 * Return: Always return 0 if it is  not an executable, other no if it does.
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int j;
	char *input_x;

	input_x = datash->args[0];
	for (j = 0; input_x[j]; j++)
	{
		if (input_x[j] == '.')
		{
			if (input_x[j + 1] == '.')
				return (0);
			if (input_x[j + 1] == '/')
				continue;
			else
				break;
		}
		else if (input_x[j] == '/' && j != 0)
		{
			if (input_x[j + 1] == '.')
				continue;
			j++;
			break;
		}
		else
			break;
	}
	if (j == 0)
		return (0);

	if (stat(input_x + j, &st) == 0)
	{
		return (j);
	}
	get_x_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - This verifies if a user has permissions to access file.
 *
 * @x_dir: The destination directory.
 * @datash: The data structure.
 * Return: Always return 1 if there is an error, 0 if not.
 */
int check_error_cmd(char *x_dir, data_shell *datash)
{
	if (x_dir == NULL)
	{
		get_x_error(datash, 127);
		return (1);
	}

	if (x_strcmp(datash->args[0], x_dir) != 0)
	{
		if (access(x_dir, X_OK) == -1)
		{
			get_x_error(datash, 126);
			free(x_dir);
			return (1);
		}
		free(x_dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_x_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - This executes command lines.
 *
 * @datash: The data relevant (args and input_x).
 * Return: Always return 1 on success.
 */
int cmd_exec(data_shell *datash)
{
	pid_t xpd;
	pid_t wpd;
	int state_x;
	int exec_x;
	char *dir;
	(void) wpd;

	exec_x = is_executable(datash);
	if (exec_x == -1)
		return (1);
	if (exec_x == 0)
	{
		dir = _which(datash->args[0], datash->_enviro);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	xpd = fork();
	if (xpd == 0)
	{
		if (exec_x == 0)
			dir = _which(datash->args[0], datash->_enviro);
		else
			dir = datash->args[0];

		execve(dir + exec_x, datash->args, datash->_enviro);
	}
	else if (xpd < 0)
	{
		perror(datash->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(xpd, &state_x, WUNTRACED);
		} while (!WIFEXITED(state_x) && !WIFSIGNALED(state_x));
	}

	datash->status = state_x / 256;
	return (1); }
