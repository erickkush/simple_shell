#include "shell.h"
#include <unistd.h>

/**
 * _eputs - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(const char *str)
{
	if (!str)
		return;

	while (*str)
	{
		_eputchar(*str);
		str++;
	}
}

/**
 * _eputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(const char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += _putfd(*str, fd);
		str++;
	}
	return (count);
}

