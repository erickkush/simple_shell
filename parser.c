#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: (1) if true, (0) otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st) != 0)
		return (0);

	if (S_ISREG(st.st_mode))
		return (1);

	return (0);
}

/**
 * extract_substring - extracts a substring from a given string
 * @str: the input string
 * @start: the starting index of the substring
 * @end: the ending index of the substring (exclusive)
 *
 * Return: a dynamically allocated substring or (NULL) on failure
 */
char *extract_substring(const char *str, int start, int end)
{
	if (!str || start < 0 || end < start)
		return (NULL);

	int len = end - start;
	char *substring = (char *)malloc((len + 1) * sizeof(char));

	if (!substring)
		return (NULL);

	for (int i = start, j = 0; i < end; i++, j++)
		substring[j] = str[i];
	substring[len] = '\0';
	return (substring);
}

/**
 * find_path - finds the full path of a
 * command in the PATH environment variable
 * @info: the info struct
 * @pathstr: the PATH environment variable
 * @cmd: the command to find
 *
 * Return: the full path of the command if found, or (NULL) if not found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	if (!pathstr || !cmd)
		return (NULL);

	if (strncmp(cmd, "./", 2) == 0 && is_cmd(info, cmd))
		return (cmd);

	char *path_copy = strdup(pathstr);

	if (!path_copy)
		return (NULL);

	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char *full_path = (char *)malloc((strlen(token) +
					strlen(cmd) + 2) * sizeof(char));

		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (is_cmd(info, full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

