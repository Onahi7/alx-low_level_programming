#include "lists.h"

/**
 * print_listint - prints all the elements of a linked list
 * @h: a pointer to the heads of he list
 *
 * Return: number of nodes in the list 
 */
size_t print_listint(const listint_t *h)
{
	size_t num = 0;

	while (h)
	{
		printf("%d\n", h->n);
		num++;
		h = h->next;
	}

	return (num);
}

