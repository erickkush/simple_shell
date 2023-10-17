#include "shell.h"

/**
 * _strtoi - Converts a string to an integer
 * with error handling.
 * @s: The string to be converted.
 * Return: The converted number on success, -1 on error.
 */
int _strtoi(const char *s)
{
	int result = 0;
	int sign = 1;

	if (*s == '+')
		s++;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	for (; *s != '\0'; s++)
	{
		if (*s >= '0' && *s <= '9')
		{
			if (result > INT_MAX / 10 ||
					(result == INT_MAX / 10 && *s - '0' > INT_MAX % 10))
				return (-1);
			result = result * 10 + (*s - '0');
		}
		else
		{
			return (-1);
		}
	}

	return (result * sign);
}

/**
 * print_error - Prints an error message.
 * @info: The parameter and return info struct.
 * @estr: String containing the specified error type.
 */
void print_error(info_t *info, const char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*putchar_func)(char) =
		(fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int abs_val = (input < 0) ? -input : input;

	if (input < 0)
	{
		putchar_func('-');
		count++;
	}

	if (abs_val >= 10)
		count += print_d(abs_val / 10, fd);

	putchar_func('0' + abs_val % 10);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to a string representation.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * Return: The string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *array = (flags & CONVERT_LOWERCASE) ?
		"0123456789abcdef" : "0123456789ABCDEF";
	char *ptr = &buffer[49];

	*ptr = '\0';

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		num = -num;
		sign = '-';
	}

	do {
		*--ptr = array[num % base];
		num /= base;
	} while (num != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - Replaces the first instance
 * of '#' with '\0'.
 * @buf: Address of the string to modify.
 */
void remove_comments(char *buf)
{
	for (int i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}

