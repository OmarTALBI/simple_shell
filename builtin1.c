#include "shell.h"

/**
 * _myhistory - affiche la liste de l'historique, une commande par ligne,
 *               précédée par des numéros de ligne, à partir de 0.
 * @info: Structure contenant des arguments potentiels. Utilisée pour maintenir
 *        le prototype de fonction constant.
 * Return: Toujours 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - supprime un alias
 * @info: structure de paramètres
 * @str: la chaîne alias
 * Return: Toujours 0 en cas de succès, 1 en cas d'erreur
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - définit un alias
 * @info: structure de paramètres
 * @str: la chaîne alias
 * Return: Toujours 0 en cas de succès, 1 en cas d'erreur
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - affiche une chaîne d'alias
 * @node: le nœud alias
 * Return: Toujours 0 en cas de succès, 1 en cas d'erreur
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - imite la commande alias (man alias)
 * @info: Structure contenant des arguments potentiels. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * Return: Toujours 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

