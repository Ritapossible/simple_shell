#include "x_shell.h"

/**
 * x_strcat - This concatenate two strings.
 * @dest_x: The char pointer the dest of the copied string.
 * @src_x: The constant char pointer to the source of string.
 * Return: The destination.
 */
char *x_strcat(char *dest_x, const char *src_x)
{
	int m;
	int n;

	for (m = 0; dest_x[m] != '\0'; m++)
		;

	for (n = 0; src_x[n] != '\0'; n++)
	{
		dest_x[m] = src_x[n];
		m++;
	}

	dest_x[m] = '\0';
	return (dest_x);
}
/**
 * *x_strcpy - This copies the string pointed to by source.
 * @dest_x: The type char pointer the dest of the copied string.
 * @src_x: The type char pointer the source of string.
 * Return: the destination.
 */
char *x_strcpy(char *dest_x, char *src_x)
{

	size_t j;

	for (j = 0; src_x[j] != '\0'; j++)
	{
		dest_x[j] = src_x[j];
	}
	dest_x[j] = '\0';

	return (dest_x);
}
/**
 * x_strcmp - The function that compares two strings.
 * @s1_x: The type string compared.
 * @s2_x: The type string compared.
 * Return: Always return 0.
 */
int x_strcmp(char *s1_x, char *s2_x)
{
	int m;

	for (m = 0; s1_x[m] == s2_x[m] && s1_x[m]; m++)
		;

	if (s1_x[m] > s2_x[m])
		return (m);
	if (s1_x[m] < s2_x[m])
		return (-1);
	return (0);
}
/**
 * x_strchr - This locates a character in a string.
 * @s_x: The string.
 * @c_x: The character.
 * Return: Always return the pointer to the first occurrence of the character.
 */
char *x_strchr(char *s_x, char c_x)
{
	unsigned int m = 0;

	for (; *(s_x + m) != '\0'; m++)
		if (*(s_x + m) == c_x)
			return (s_x + m);
	if (*(s_x + m) == c_x)
		return (s_x + m);
	return ('\0');
}
/**
 * x_strspn - This gets the length of a prefix sub-string.
 * @s_x: The initial segment.
 * @accept_x: The accepted x shell bytes.
 * Return: The number of accepted x shell bytes.
 */
int x_strspn(char *s_x, char *accept_x)
{
	int m, n, bool_x;

	for (m = 0; *(s_x + m) != '\0'; m++)
	{
		bool_x = 1;
		for (n = 0; *(accept_x + n) != '\0'; n++)
		{
			if (*(s_x + m) == *(accept_x + n))
			{
				bool_x = 0;
				break;
			}
		}
		if (bool_x == 1)
			break;
	}
	return (m);
}
