#include "shell.h"

/**
 * input_buf - met en mémoire tampon les commandes chaînées
 * @info: structure des paramètres
 * @buf: adresse du tampon
 * @len: adresse de la variable de longueur
 *
 * Retour : octets lus
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* si rien n'est resté dans le tampon, le remplir */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* supprimer le saut de ligne final */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* si (_strchr(*buf, ';')) est-ce une chaîne de commandes ? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}

/**
 * get_input - obtient une ligne sans le saut de ligne
 * @info: structure des paramètres
 *
 * Retour : octets lus
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* le tampon de chaîne de commandes ';' */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len) /* il reste des commandes dans le tampon de la chaîne */
    {
        j = i; /* initialise le nouvel itérateur à la position actuelle du tampon */
        p = buf + i; /* obtient

