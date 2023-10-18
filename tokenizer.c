#include "shell.h"
/**
 * strtow - splits a string into words using specified delimiters
 * @str: the input string
 * @delim: the delimiter characters
 * Return: (a pointer to an array of strings, or NULL on failure)
 */
char **strtow(char *str, char *delim)
{
	int i, j, k, num_words = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], delim))
		{
			num_words++;
			while (!is_delim(str[i], delim) && str[i + 1] != '\0')
				i++;
		}
	}
	if (num_words == 0)
		return (NULL);
	words = malloc((num_words + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k] != '\0')
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (int m = 0; m < k; m++, i++)
			words[j][m] = str[i];
		words[j][k] = '\0';
	}
	words[num_words] = NULL;
	return (words);
}

