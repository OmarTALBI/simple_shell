#include "shell.h"

/**
 * is_chain - teste si le caractère actuel dans le tampon est un délimiteur de chaîne
 * @info: la structure de paramètres
 * @buf: le tampon de caractères
 * @p: adresse de la position actuelle dans buf
 *
 * Retourne : 1 si c'est un délimiteur de chaîne, 0 sinon
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* trouvé la fin de cette commande */
	{
		buf[j] = 0; /* remplace le point-virgule par un null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - vérifie si nous devons continuer la chaîne en fonction du dernier statut
 * @info: la structure de paramètres
 * @buf: le tampon de caractères
 * @p: adresse de la position actuelle dans buf
 * @i: position de départ dans buf
 * @len: longueur de buf
 *
 * Retourne : Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - remplace les alias dans la chaîne de caractères tokenisée
 * @info: la structure de paramètres
 *
 * Retourne : 1 si remplacé, 0 sinon
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - remplace les variables dans la chaîne de caractères tokenisée
 * @info: la structure de paramètres
 *
 * Retourne : 1 si remplacé, 0 sinon
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - remplace la chaîne de caractères
 * @old: adresse de l'ancienne chaîne
 * @new: nouvelle chaîne
 *
 * Retourne : 1 si remplacé, 0 sinon
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

