#include "monty.h"
#define BUFFERSIZE 1024

/**
 * main - entry point of the program
 * an interpeter for monty files
 * @argc: the arguments count
 * @argv: the arguments
 * Return: 0 Success
 */
int main(int argc, char *argv[])
{
	stack_t *top = NULL;
	FILE *fp;
	char buffer[BUFFERSIZE];
	char *file_name;
	char **ops;
	unsigned int line_number;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_name = argv[1];
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file_name);
		exit(EXIT_FAILURE);
	}
	while (fgets(buffer, BUFFERSIZE, fp) != NULL)
	{
		line_number++;
		if (buffer[0] == '#')
			continue;
		ops = splitter(buffer, " ");
		run(ops, &top, line_number);
	}

	fclose(fp);
	free_stack(top);

	return (0);
}

/**
 * splitter - splits string
 * @str: the string splitted
 * @tube: the delimeter
 * Return: an array of splitted words
 */

char **splitter(char *str, const char *tube)
{
	char **words = NULL;
	int i = 0;
	char *copy = NULL, *token = NULL;

	if (str == NULL)
		return (NULL);

	words = (char **)malloc(sizeof(char *) * 3);
	if (words == NULL)
		return (NULL);

	copy = _strdup(str);
	token = strtok(copy, "\n");	 /* removes new lines */
	token = strtok(token, "\t"); /* removes taps */
	token = strtok(token, tube);
	while (token != NULL)
	{
		words[i] = _strdup(token);
		i++;
		if (i == 2)
			break;
		token = strtok(NULL, tube);
	}
	words[i] = NULL;
	if (words[0])
	{
		if (words[0][0] == '#')
		{
			free(copy);
			free_arr(words);
			return (NULL);
		}
	}
	free(copy);
	return (words);
}

/**
 * run - a function that takes an array of opcodes and arguments
 * which should end with NULL and check the argumnet for push opcode
 * @ops: array of strings containing the line of monty
 * byte code space separated
 * @stack: a pointer to a stack to perform operations on it
 * @line_number: the line number in monty file
 */

void run(char **ops, stack_t **stack, unsigned int line_number)
{
	char *opcode, *arg;
	void (*op)(stack_t **stack, unsigned int line);
	int n, valid;

	if (ops == NULL)
		return;
	opcode = ops[0];
	if (opcode == NULL)
	{
		free_arr(ops);
		return;
	}
	arg = ops[1];
	if (strcmp(opcode, "push") == 0)
	{
		n = _atoi(arg, &valid);
		if (arg == NULL || !valid)
		{
			fprintf(stderr, "L%i: usage: push integer\n", line_number);
			free_arr(ops);
			exit(EXIT_FAILURE);
		}

		push(stack, n);
	}
	else
	{
		op = opcode_func(opcode);
		if (op == NULL)
		{
			fprintf(stderr, "L%i: unknown instruction %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}

		op(stack, line_number);
	}
	free_arr(ops);
}
