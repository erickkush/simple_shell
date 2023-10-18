#include "shell.h"

/**
 * custom_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: (integer length of string)
 */
size_t custom_strlen(const char *str)
{
	size_t length = 0;

	if (!str)
		return (0);

	while (str[length] != '\0')
	{
		length++;
	}

	return (length);
}

/**
 * custom_strcmp - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: (negative if str1 < str2,
 * positive if str1 > str2, zero if str1 == str2)
 */
int custom_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * custom_starts_with - checks if a string starts with a prefix
 * @str: the string to search
 * @prefix: the prefix to find
 *
 * Return: (pointer to the next character of
 * str if it starts with prefix, otherwise NULL)
 */
const char *custom_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*str != *prefix)
			return (NULL);
		str++;
		prefix++;
	}

	return (str);
}

/**
 * custom_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: (pointer to the destination buffer)
 */
char *custom_strcat(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return (original_dest);
}

