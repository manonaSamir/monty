#include "monty.h"

/**
 * opcode_func - gets function from opcode
 * @s: the opcode
 * Return: a function pointer
 */

void (*opcode_func(char *s))(stack_t **stack, unsigned int line)
{
	instruction_t codes[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"div", M_div},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
	};
	int i;

	for (i = 0; codes[i].opcode != NULL; i++)
	{
		if (strcmp(codes[i].opcode, s) == 0)
			return (codes[i].f);
	}

	return (NULL);
}
