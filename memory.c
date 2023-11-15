#include "shell.h"

/**
 * bfree - libère un pointeur et met l'adresse à NULL
 * @ptr: adresse du pointeur à libérer
 *
 * Return: 1 si libéré, sinon 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

