#include "shell.h"
#include <stdlib.h>
/**
 * _myenv - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_environment(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = find_environment(info->env, name);

	return ((node != NULL) ? node->str : NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	int result = set_environment(info->env, info->argv[1], info->argv[2]);

	return ((result == 0) ? 0 : (1));
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */
int _myunsetenv(info_t *info)
{
	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (int i = 1; i <= info->argc; i++)
	{
		int result = unset_environment(info->env, info->argv[i]);

		if (result != 0)
		{
			_eputs("Error unsetting environment variable.\n");
			return (1);
		}
	}

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */
int populate_env_list(info_t *info)
{
	char **environ_copy = environ;
	list_t *env_list = NULL;

	for (size_t i = 0; environ_copy[i]; i++)
	{
		int result = add_environment(&env_list, environ_copy[i]);

		if (result != 0)
		{
			_eputs("Error populating environment list.\n");
			return (1);
		}
	}

	info->env = env_list;
	return (0);
}
