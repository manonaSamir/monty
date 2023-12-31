#ifndef MONTY_H
#define MONTY_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void push(stack_t **tops, unsigned int n);
void pall(stack_t **stack, unsigned int line __attribute__((unused)));

void free_arr(char **arr);
int _atoi(char *s, int *valid);
void run(char **ops, stack_t **stack, unsigned int line_number);
char **splitter(char *str, const char *tube);
void (*opcode_func(char *s))(stack_t **stack, unsigned int line);
char *_strdup(const char *s);
void free_stack(stack_t *top);
void pint(stack_t **stack, unsigned int line);
void pop(stack_t **stack, unsigned int line);
void swap(stack_t **stack, unsigned int line);
void checks_stack(stack_t **stack, char *opcode, int line);
void add(stack_t **stack, unsigned int line);
void nop(stack_t **stack __attribute__((unused)),
		 unsigned int line __attribute__((unused)));
void sub(stack_t **stack, unsigned int line);
void M_div(stack_t **stack, unsigned int line);
void mul(stack_t **stack, unsigned int line);
void mod(stack_t **stack, unsigned int line);
void pchar(stack_t **stack, unsigned int line);
void pstr(stack_t **stack, unsigned int line __attribute__((unused)));
void rotl(stack_t **stack, unsigned int line __attribute__((unused)));
void rotr(stack_t **stack, unsigned int line __attribute__((unused)));

#endif
