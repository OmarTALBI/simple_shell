#include "shell.h"

/**
 * get_environ - renvoie la copie du tableau de chaînes de notre environnement
 * @info: Structure contenant d'éventuels arguments. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * Return: Toujours 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Supprime une variable d'environnement
 * @info: Structure contenant d'éventuels arguments. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * Return: 1 en cas de suppression, 0 sinon
 * @var: la propriété de la variable d'environnement en chaîne
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialise une nouvelle variable d'environnement
 *            ou modifie une variable existante
 * @info: Structure contenant d'éventuels arguments. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * @var: la propriété de la variable d'environnement en chaîne
 * @value: la valeur de la variable d'environnement en chaîne
 * Return: Toujours 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

