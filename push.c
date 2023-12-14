#include "monty.h"

/**
 * push - pushe element at top
 * @tops: a pointer
 * @n: argument given to push
 */
void push(stack_t **tops, unsigned int n)
{
	stack_t *temp;

	temp = malloc(sizeof(stack_t));
	if (tops == NULL || temp == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	temp->n = n;
	temp->prev = NULL;
	temp->next = *tops;
	if (*tops)
		(*tops)->prev = temp;
	*tops = temp;
}

/**
 * pall - prints the stack
 * @tops: a pointer to the stack
 * @line: the line number of the operation
 */
void pall(stack_t **stack, unsigned int line __attribute__((unused)))
{
	stack_t *p;

	if (stack == NULL)
		return;
	p = *stack;
	while (p)
	{
		printf("%i\n", p->n);
		p = p->next;
	}
}