#include "shell.h"

/**
 * _myexit - quitte le shell
 * @info: Structure contenant des arguments potentiels. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * Return: quitte avec un statut de sortie donné
 *         (0) si info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* S'il y a un argument exit */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Nombre illégal : ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change le répertoire courant du processus
 * @info: Structure contenant des arguments potentiels. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * Return: Toujours 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >> Erreur getcwd ici <<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: que doit-il être ? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: que doit-il être ? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Impossible de changer vers ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - affiche l'aide
 * @info: Structure contenant des arguments potentiels. Utilisée pour maintenir
 *         le prototype de fonction constant.
 * Return: Toujours 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("L'appel de l'aide fonctionne. Fonction pas encore implémentée \n");
	if (0)
		_puts(*arg_array); /* Contournement temporaire att_unused */
	return (0);
}

