#include "monty.h"
#define BUFFERSIZE 1024

int is_stack = 1;
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
		if (is_stack)
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
