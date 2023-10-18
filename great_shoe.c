#include "main.h"

/**
 * get_size - Calculates the size to print
 * @format: Formatted string in which to print the arguments
 * @got: outline all the variables
 *
 * Return: Precision.
 */
int get_size(const char *format, int *got)
{
	int curr_got = *got + 1;
	int size = 0;

	if (format[curr_got] == 'l')
		size = S_LONG;
	else if (format[curr_got] == 'h')
		size = S_SHORT;

	if (size == 0)
		*got = curr_got - 1;
	else
		*got = curr_got;

	return (size);
}

