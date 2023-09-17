#include "x_shell.h"

/**
 * x_strdup - This duplicates a string in the heap memory.
 * @str_x: The type char pointer string.
 * Return: The duplicated string.
 */
char *x_strdup(const char *str_x)
{
	char *n;
	size_t length;

	length = x_strlen(str_x);
	n = malloc(sizeof(char) * (length + 1));
	if (n == NULL)
		return (NULL);
	x_memcpy(n, str_x, length + 1);
	return (n);
}

/**
 * x_strlen - This returns the lenght of a string.
 * @str_x: The type character pointer.
 * Return: Always return 0.
 */
int x_strlen(const char *str_x)
{
	int length;

	for (length = 0; str_x[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * x_cmp_chars - This compare characters of strings.
 * @str: The input string.
 * @delim_x: The delimiter.
 *
 * Return: Always return 1 if are equals, 0 if not.
 */
int x_cmp_chars(char str[], const char *delim_x)
{
	unsigned int m, n, k;

	for (m = 0, k = 0; str[m]; m++)
	{
		for (n = 0; delim_x[n]; n++)
		{
			if (str[m] == delim_x[n])
			{
				k++;
				break;
			}
		}
	}
	if (m == k)
		return (1);
	return (0);
}

/**
 * x_strtok - This helps to split a string by some delimiter.
 * @str: The input string.
 * @delim_x: The delimiter.
 *
 * Return: string splited.
 */
char *x_strtok(char str[], const char *delim_x)
{
	static char *splitted, *s_end;
	char *s_start;
	unsigned int m, bool_x;

	if (str != NULL)
	{
		if (x_cmp_chars(str, delim_x))
			return (NULL);
		splitted = str;
		m = x_strlen(str);
		s_end = &str[m];
	}
	s_start = splitted;
	if (s_start == s_end)
		return (NULL);
	for (bool_x = 0; *splitted; splitted++)
	{

		if (splitted != s_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		for (m = 0; delim_x[m]; m++)
		{
			if (*splitted == delim_x[m])
			{
				*splitted = '\0';
				if (splitted == s_start)
					s_start++;
				break;
			}
		}
		if (bool_x == 0 && *splitted)
			bool_x = 1;
	}
	if (bool_x == 0)
		return (NULL);
	return (s_start);
}

/**
 * x_isdigit - This defines if the string passed is a number.
 *
 * @str_x: The input string.
 * Return: Always return 1 if string is a number. 0 in other case.
 */
int x_isdigit(const char *str_x)
{
	unsigned int m;

	for (m = 0; str_x[m]; m++)
	{
		if (str_x[m] < 48 || str_x[m] > 57)
			return (0);
	}
	return (1);
}
