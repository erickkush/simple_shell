#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified number of characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to be copied.
 * Return: A pointer to the concatenated string.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_start = dest;

	while (*src != '\0' && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}

	return (dest_start);
}

/**
 * _strncat - Concatenates two strings up to a specified number of characters.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to be appended.
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	char *dest_start = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0' && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	*dest = '\0';

	return (dest_start);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the located character or NULL if not found.
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}

	if (c == '\0')
		return ((char *)s);

	return (NULL);
}

