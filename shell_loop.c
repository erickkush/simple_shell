#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @info: Pointer to the info struct
 * @av: Argument vector from main()
 *
 * Return: (0 on success, 1 on error, or error code)
 */
int shell_loop(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_ret = 0;

	while (read_result != -1 && builtin_ret != -2)
	{
		clear_info(info);

		if (interactive(info))
			_puts("$ ");

		_eputchar(BUF_FLUSH);
		read_result = get_input(info);

		if (read_result != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin_command(info);

			if (builtin_ret == -1)
				find_external_command(info);
		}
		else if (interactive(info))
			_putchar('\n');

		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin_command - Finds and executes a builtin command
 * @info: Pointer to the info struct
 *
 * Return: (-1 if builtin not found, 0 if builtin executed successfully,
 *          1 if builtin found but not successful, 2 if builtin signals exit())
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].command; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].command) == 0)
		{
			info->line_count++;
			builtin_ret = builtintbl[i].function(info);
			break;
		}
	}

	return (builtin_ret);
}

/**
 * find_external_command - Finds and executes an external command
 * @info: Pointer to the info struct
 *
 * Return: void
 */
void find_external_command(info_t *info)
{
	char *path = NULL;
	int i, num_args = 0;

	info->path = info->argv[0];

	for (i = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
			num_args++;
	}

	if (!num_args)
		return;

	path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_and_execute_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
					info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_and_execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_and_execute_command - Forks a child process to execute the command
 * @info: Pointer to the info struct
 *
 * Return: void
 */
void fork_and_execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);

			if (errno == EACCES)
				exit(126);

			exit(1);
		}
	}
	else
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

