#include "shell.h"

/**
 * _strlen - retourne la longueur d'une chaîne de caractères
 * @s: la chaîne dont on veut mesurer la longueur
 *
 * Retourne : la longueur entière de la chaîne
 */
int _strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    while (*s++)
        i++;
    return (i);
}

/**
 * _strcmp - réalise une comparaison lexicographique de deux chaînes de caractères.
 * @s1: la première chaîne
 * @s2: la deuxième chaîne
 *
 * Retourne : négatif si s1 < s2, positif si s1 > s2, zéro si s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - vérifie si l'aiguille commence par la botte de foin
 * @haystack: la chaîne à rechercher
 * @needle: la sous-chaîne à trouver
 *
 * Retourne : l'adresse du caractère suivant de haystack ou NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * _strcat - concatène deux chaînes de caractères
 * @dest: le tampon de destination
 * @src: le tampon source
 *
 * Retourne : pointeur vers le tampon de destination
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (ret);
}

