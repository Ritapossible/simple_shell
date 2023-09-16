#include "x-shell.h"

/**
 * get_x_sigint - Handles the crtl + c call in prompt.
 * @x_sig: The signal handler.
 */
void get_x_sigint(int x_sig)
{
	(void)x_sig;
	write(STDOUT_FILENO, "\n:) ", 4);
}
