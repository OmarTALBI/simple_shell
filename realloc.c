#include "shell.h"

/**
 * _memset - remplit la mémoire avec un octet constant
 * @s: le pointeur vers la zone mémoire
 * @b: l'octet avec lequel remplir *s
 * @n: le nombre d'octets à remplir
 * Return: (s) un pointeur vers la zone mémoire s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - libère une chaîne de chaînes de caractères
 * @pp: chaîne de chaînes de caractères
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - réallocation d'un bloc de mémoire
 * @ptr: pointeur vers le bloc malloc précédent
 * @old_size: taille en octets du bloc précédent
 * @new_size: taille en octets du nouveau bloc
 *
 * Return: pointeur vers l'ancien bloc
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

