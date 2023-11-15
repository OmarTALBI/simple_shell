#include "shell.h"

/**
 * _strcpy - copie une chaîne de caractères
 * @dest: la destination
 * @src: la source
 *
 * Retourne : pointeur vers la destination
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

/**
 * _strdup - duplique une chaîne de caractères
 * @str: la chaîne à dupliquer
 *
 * Retourne : pointeur vers la chaîne dupliquée
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**
 *_puts - imprime une chaîne de caractères en entrée
 *@str: la chaîne à imprimer
 *
 * Retourne : Rien
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _putchar - écrit le caractère c sur stdout
 * @c: Le caractère à imprimer
 *
 * Retourne : En cas de succès, retourne 1.
 * En cas d'erreur, -1 est retourné, et errno est défini correctement.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

