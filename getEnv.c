#include "shell.h"

/**
 * update_environment - updates the environment variable list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: void
 */
void update_environment(info_t *info)
{
	if (!info->env || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
}

/**
 * remove_environment - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int remove_environment(info_t *info, const char *var)
{
	list_t *current = info->env;
	list_t *prev = NULL;

	if (!current || !var)
		return (0);

	while (current)
	{
		if (_startswith(current->str, var) && current->str[_strlen(var)] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				info->env = current->next;

			free(current->str);
			free(current);
			info->env_changed = 1;
			return (1);
		}

		prev = current;
		current = current->next;
	}

	return (0);
}

/**
 * set_environment - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int set_environment(info_t *info, const char *var, const char *value)
{
	char *env_str = NULL;
	list_t *current = info->env;

	if (!var || !value)
		return (0);

	env_str = malloc(_strlen(var) + _strlen(value) + 2);
	if (!env_str)
		return (1);

	_strcpy(env_str, var);
	_strcat(env_str, "=");
	_strcat(env_str, value);

	while (current)
	{
		if (_startswith(current->str, var) && current->str[_strlen(var)] == '=')
		{
			free(current->str);
			current->str = env_str;
			info->env_changed = 1;
			return (0);
		}
		current = current->next;
	}

	add_node_end(&(info->env), env_str, 0);
	free(env_str);
	info->env_changed = 1;
	return (0);
}

