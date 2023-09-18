#include "x_shell.h"

/**
 * rev_string - This helps to reverse a string.
 * @str_x: The input string.
 * Return: Return Nothing.
 */
void rev_string(char *str_x)
{
	int count = 0, m, n;
	char *st, temp;

	while (count >= 0)
	{
		if (str_x[count] == '\0')
			break;
		count++;
	}
	st = str_x;

	for (m = 0; m < (count - 1); m++)
	{
		for (n = m + 1; n > 0; n--)
		{
			temp = *(st + n);
			*(st + n) = *(st + (n - 1));
			*(st + (n - 1)) = temp;
		}
	}
}
