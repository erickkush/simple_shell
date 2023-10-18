#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * create_node - creates a new list node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: A pointer to the newly created node or NULL on failure
 */
list_t *create_node(const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->str = strdup(str);
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}

	new_node->num = num;
	new_node->next = NULL;
	return (new_node);
}

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = create_node(str, num);

	if (!new_node)
		return (NULL);

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = create_node(str, num);

	if (!new_node)
		return (NULL);

	if (*head)
	{
		list_t *node = *head;

		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes a node at the given index
 * @head: address of pointer to the first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	list_t *prev_node = NULL;
	list_t *node = *head;
	unsigned int i = 0;

	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	if (!head_ptr || !*head_ptr)
		return;

	list_t *head = *head_ptr;

	while (head)
	{
		list_t *next_node = head->next;

		free(head->str);
		free(head);
		head = next_node;
	}
	*head_ptr = NULL;
}

