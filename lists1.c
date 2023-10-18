#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * list_to_strings - returns an array of strings from the list
 * @head: pointer to the first node
 *
 * Return: an array of strings or NULL on failure
 */
char **list_to_strings(list_t *head)
{
	size_t list_size = list_len(head);
	char **strs = malloc(sizeof(char *) * (list_size + 1));

	if (!strs)
		return (NULL);

	size_t i = 0;
	list_t *node = head;

	while (node)
	{
		strs[i] = _strdup(node->str);
		if (!strs[i])
		{
			for (size_t j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		node = node->next;
		i++;
	}

	strs[list_size] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");

		head = head->next;
		count++;
	}

	return (count);
}

/**
 * find_node_starts_with - finds a node whose string starts with a prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
	while (head)
	{
		char *str = head->str;

		if (str && starts_with(str, prefix) &&
				(c == -1 || str[_strlen(prefix)] == c))
			return (head);
		head = head->next;
	}

	return (NULL);
}

/**
 * get_node_index - gets the index of a node in the linked list
 * @head: pointer to the list head
 * @node: pointer to the node to find
 *
 * Return: index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	ssize_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}

