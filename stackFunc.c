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
 * @stack: a pointer to the stack
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

/**
 * pint - prints the top element in the stack
 * @stack: a pointer to the stack
 * @line: the line number of the operation
 */
void pint(stack_t **stack, unsigned int line)
{
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%i: can't pint, stack empty\n", line);
		exit(EXIT_FAILURE);
	}

	printf("%i\n", (*stack)->n);
}

/**
 * pop - deletes the top of the stack
 * @stack: a pointer to the stack
 * @line: the line number of operation
 */
void pop(stack_t **stack, unsigned int line)
{
	stack_t *p;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%i: can't pop an empty stack\n", line);
		exit(EXIT_FAILURE);
	}

	p = *stack;

	*stack = p->next;
	free(p);
	if (*stack)
		(*stack)->prev = NULL;
}

/**
 * swap - swaps the top 2 element of the stack
 * @stack: a pointer to the top of the stack
 * @line: the line number of the operation
 */
void swap(stack_t **stack, unsigned int line)
{
	int tmp;
	stack_t *p = *stack;

	checks_stack(stack, "swap", line);
	tmp = p->n;
	p->n = (p->next)->n;
	(p->next)->n = tmp;
}

/**
 * add - adds the top 2 elements in the stack in one element
 * @stack: a pointer to the stack
 * @line: line number of the operation
 */
void add(stack_t **stack, unsigned int line)
{
	int sum = 0;
	stack_t *p = *stack;

	checks_stack(stack, "add", line);
	sum += p->n + (p->next)->n;
	(p->next)->n = sum;
	pop(stack, 0);
}

/**
 * nop - doesn't do anything
 * @stack: a pointer to the stack
 * @line: line number of operation
 */
void nop(stack_t **stack __attribute__((unused)),
		 unsigned int line __attribute__((unused)))
{
}

/**
 * sub - substracte the top element from the second to element
 * @stack: a pointer to the stack
 * @line: the line number of the operation
 */
void sub(stack_t **stack, unsigned int line)
{
	int top;
	stack_t *p = *stack;

	checks_stack(stack, "sub", line);
	top = p->n;
	p = p->next;
	p->n = (p->n) - top;
	pop(stack, 0);
}

/**
 * M_div - divides the second top element by the top element in the stack
 * @stack: a pointer to the stack
 * @line: the line number of the operation
 */
void M_div(stack_t **stack, unsigned int line)
{
	stack_t *p = *stack;
	int top;

	checks_stack(stack, "div", line);

	top = p->n;
	if (top == 0)
	{
		fprintf(stderr, "L%i: division by zero\n", line);
		exit(EXIT_FAILURE);
	}

	p = p->next;
	p->n = (p->n) / top;
	pop(stack, 0);
}

/**
 * mul - multiply the top two elements
 * @stack: a pointer to the stack
 * @line: the line number of the operation
 */
void mul(stack_t **stack, unsigned int line)
{
	stack_t *p = *stack;

	checks_stack(stack, "mul", line);
	p = p->next;
	p->n = (p->n) * (p->prev)->n;
	pop(stack, 0);
}

/**
 * mod - computes the rest of the division of the second top element
 * by the top element of the stack
 * @stack: a pointer to the stack
 * @line: the line number to the operation
 */
void mod(stack_t **stack, unsigned int line)
{
	stack_t *p = *stack;
	int top;

	checks_stack(stack, "mod", line);
	top = p->n;
	if (top == 0)
	{
		fprintf(stderr, "L%i: division by zero\n", line);
		exit(EXIT_FAILURE);
	}
	p = p->next;
	p->n = (p->n) % top;
	pop(stack, 0);
}

/**
 * pchar - prints the integer at the top of the stack as ascii value
 * @stack: a pointer to the stack
 * @line: the line number of operation
 */
void pchar(stack_t **stack, unsigned int line)
{
	int c;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%i: can't pchar, stack empty\n", line);
		exit(EXIT_FAILURE);
	}
	c = (*stack)->n;
	if (c < 0 || c > 127)
	{
		fprintf(stderr, "L%i: can't pchar, value out of range\n", line);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", c);
}

/**
 * pstr - prints each element in the stack in a string (if it's in ascii table)
 * @stack: a pointer to the stack
 * @line: the line number of the operation
 */
void pstr(stack_t **stack, unsigned int line __attribute__((unused)))
{
	stack_t *p = *stack;
	int c;

	while (p)
	{
		c = p->n;
		if (c > 0 && c <= 127)
		{
			printf("%c", c);
		}
		else
			break;
		p = p->next;
	}

	printf("\n");
}
