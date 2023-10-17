#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	if (!info->argv[1])
	{
		info->err_num = -1;
		return (-2);
	}

	int exitcode = _erratoi(info->argv[1]);

	if (exitcode == -1)
	{
		info->status = 2;
		print_error(info, "Illegal number: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		info->err_num = exitcode;
		return (-2);
	}

	return (1);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir = NULL;
	char buffer[1024];
	int chdir_ret;
	char *current_dir = getcwd(buffer, 1024);

	if (!current_dir)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return (1);
	}
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
	}
	else
	{
		dir = info->argv[1];
	}
	chdir_ret = chdir(dir);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays help message
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	(void)info;

	_puts("Help message: Function not yet implemented\n");
	return (0);
}
