#include "shell.h"

/**
 * mem_cpy - Copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: No return.
 */
void mem_cpy(void *newptr, unsigned int size, const void *ptr)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * realloc - reallocates a memory block.
 * @ptr: pointer to previous memory allocated.
 * @old_size: size, in bytes, of the new memory block.
 * @new_size: new size, in bytes, of new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *realloc(void *ptr, unsigned int new_size, unsigned int old_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		mem_cpy(newptr, ptr, new_size);
	else
		mem_cpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 *realloc_dp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to previous memory allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **realloc_dp(char **ptr, unsigned int new_size, unsigned int old_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
