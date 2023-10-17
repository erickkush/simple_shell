#include "shell.h"

/**
 * _myhistory - Display the command history list with line numbers.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
	print_history(info->history);
	return (0);
}

/**
 * unset_alias - Unset an alias by name.
 * @info: Parameter struct.
 * @alias_name: The name of the alias to unset.
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias_name)
{
	int ret = delete_alias(&(info->alias), alias_name);

	return ((ret == 0) ? 0 : 1);
}

/**
 * set_alias - Set an alias to a string.
 * @info: Parameter struct.
 * @alias_str: The string representing the alias.
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias_str)
{
	int ret = add_alias(&(info->alias), alias_str);

	return ((ret == 0) ? 0 : 1);
}

/**
 * print_alias - Print an alias node.
 * @node: The alias node to print.
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	if (node)
	{
		_puts(node->str);
		_putchar('\n');
		return (0);
	}
	return (1);
}

/**
 * _myalias - Manage aliases.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
	if (info->argc == 1)
	{
		print_aliases(info->alias);
	}
	else
	{
		for (int i = 1; info->argv[i]; i++)
		{
			char *alias_name = info->argv[i];
			char *equal_sign = _strchr(alias_name, '=');

			if (equal_sign)
			{
				*equal_sign = '\0';
				set_alias(info, info->argv[i]);
			}
			else
			{
				print_alias(find_alias(info->alias, alias_name));
			}
		}
	}

	return (0);
}

