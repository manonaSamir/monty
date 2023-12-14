#include "monty.h"
/**
 * checks_stack - checks that the stack has minimum two elements
 * @stack: a pointer to the stack
 * @opcode: the operation code
 * @line: the line number of the operation
 * Return: 1 if has two or more elements 0 otherwise
 */
void checks_stack(stack_t **stack, char *opcode, int line)
{
	if (stack && *stack)
	{
		if ((*stack)->next)
			return;
	}
	fprintf(stderr, "L%i: can't %s, stack too short\n", line, opcode);
	exit(EXIT_FAILURE);
}

/**
 * _atoi - a function that converts a string to a number and checks
 * if it's valid (this is just of the "0" string which is valid
 * but the original atio will return 0 which is the same return for the invalid
 * @s: the string to be converted
 * @valid: a pointer to integer to work as a bool checking the validation
 * Return: the converted integer
 */
int _atoi(char *s, int *valid)
{
	int i;
	int n;

	if (s == NULL)
	{
		*valid = 0;
		return (0);
	}
	n = atoi(s);
	i = s[0] == '-' ? 1 : 0;
	for (; s[i] != '\0'; i++)
	{
		if (!isdigit(s[i]))
		{
			*valid = 0;
			return (0);
		}
	}

	*valid = 1;
	return (n);
}

/**
 * free_arr - frees array
 * @arr: the array to be freed
 */
void free_arr(char **arr)
{
	int i = 0;

	if (arr == NULL)
		return;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}

	free(arr);
}

/**
 * strdup -  rellocate space in memoery
 * @s : pointer to the new str
 * Return: NULL or a pointer to the duplicated string
 */
char *_strdup(const char *s)
{
	int len;
	char *new;
	int i;

	if (s == NULL)
		return (NULL);

	len = strlen((char *)s);
	new = malloc(sizeof(char) * len + 1);

	if (new == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		new[i] = s[i];

	new[i] = '\0';

	return (new);
}

/**
 * free_stack - frees a stack
 * @top: the top of the stack
 */
void free_stack(stack_t *top)
{
	if (!top)
		return;
	while (top->next)
	{
		top = top->next;
		free(top->prev);
	}
	free(top);
}
