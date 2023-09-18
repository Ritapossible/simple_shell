#include "x_shell.h"

/**
 * get_x_len - This get the lenghth of a number.
 * @i: The type int number.
 * Return: The lenghth of a number.
 */
int get_x_len(int i)
{
	unsigned int i1;
	int len = 1;

	if (i < 0)
	{
		len++;
		i1 = i * -1;
	}
	else
	{
		i1 = i;
	}
	while (i1 > 9)
	{
		len++;
		i1 = i1 / 10;
	}

	return (len);
}
/**
 * x_itoa - The function that converts int to string.
 * @i: The type integer number.
 * Return: The String.
 */
char *x_itoa(int i)
{
	unsigned int i1;
	int len = get_x_len(i);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (i < 0)
	{
		i1 = i * -1;
		buffer[0] = '-';
	}
	else
	{
		i1 = i;
	}

	len--;
	do {
		*(buffer + len) = (i1 % 10) + '0';
		i1 = i1 / 10;
		len--;
	}
	while (i1 > 0)
		;
	return (buffer);
}

/**
 * x_atoi - This converts a string to an integer.
 * @x: The input string.
 * Return: The integer.
 */
int x_atoi(char *x)
{
	unsigned int count = 0, xsize = 0, oi = 0, pn = 1, m = 1, i;

	while (*(x + count) != '\0')
	{
		if (xsize > 0 && (*(x + count) < '0' || *(x + count) > '9'))
			break;

		if (*(x + count) == '-')
			pn *= -1;

		if ((*(x + count) >= '0') && (*(x + count) <= '9'))
		{
			if (xsize > 0)
				m *= 10;
			xsize++;
		}
		count++;
	}

	for (i = count - xsize; i < count; i++)
	{
		oi = oi + ((*(x + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
