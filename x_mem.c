#include "x_shell.h"

/**
 * x_memcpy - This copies information between void pointers.
 * @x_newptr: The new destination pointer.
 * @ptr_x: The source pointer.
 * @x_size: The size of the new pointer.
 *
 * Return: no return.
 */
void x_memcpy(void *x_newptr, const void *ptr_x, unsigned int x_size)
{
	char *charc_ptr = (char *)ptr_x;
	char *charc_newptr = (char *)x_newptr;
	unsigned int m;

	for (m = 0; m < x_size; m++)
		charc_newptr[m] = charc_ptr[m];
}

/**
 * x_realloc - This helps to reallocate a memory block.
 * @ptr_x: The pointer to the memory previously allocated.
 * @x_old_sz: The size, in bytes, of the allocated space of ptr.
 * @x_new_sz: The new size, in bytes, of the new memory block.
 *
 * Return: Always return ptr.
 * if new_sz == old_sz, returns ptr without changes.
 * if malloc fails, simply return NULL.
 */
void *x_realloc(void *ptr_x, unsigned int x_old_sz, unsigned int x_new_sz)
{
	void *nptr;

	if (ptr_x == NULL)
		return (malloc(x_new_sz));

	if (x_new_sz == 0)
	{
		free(ptr_x);
		return (NULL);
	}

	if (x_new_sz == x_old_sz)
		return (ptr_x);

	nptr = malloc(x_new_sz);
	if (nptr == NULL)
		return (NULL);

	if (x_new_sz < x_old_sz)
		x_memcpy(nptr, ptr_x, x_new_sz);
	else
		x_memcpy(nptr, ptr_x, x_old_sz);

	free(ptr_x);
	return (nptr);
}

/**
 * x_reallocdp - This helps to reallocate a memory block of a double pointer.
 * @ptr_x: The double ptr to the memory previously allocated.
 * @x_old_sz: The size, in bytes, of the allocated space of ptr.
 * @x_new_sz: The new size, in bytes, of the new memory block.
 *
 * Return: Always return a ptr.
 * if new_sz == old_sz, returns ptr_x without changes.
 * if malloc fails, simply returns NULL.
 */
char **x_reallocdp(char **ptr_x, unsigned int x_old_sz, unsigned int x_new_sz)
{
	char **nptr;
	unsigned int m;

	if (ptr_x == NULL)
		return (malloc(sizeof(char *) * x_new_sz));

	if (x_new_sz == x_old_sz)
		return (ptr_x);

	nptr = malloc(sizeof(char *) * x_new_sz);
	if (nptr == NULL)
		return (NULL);

	for (m = 0; m < x_old_sz; m++)
		nptr[m] = ptr_x[m];

	free(ptr_x);

	return (nptr);
}
