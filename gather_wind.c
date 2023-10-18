#include "main.h"

/**
 * get_width - Calculates the width for and the the other specified functions
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed below
 * @list: list of arguments in the functions
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int surr_j;
	int pitch = 0;

	for (surr_j = *i + 1; format[surr_j] != '\0'; surr_j++)
	{
		if (is_digit(format[surr_j]))
		{
			pitch *= 10;
			pitch += format[surr_j] - '0';
		}
		else if (format[surr_j] == '*')
		{
			surr_j++;
			pitch = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = surr_j - 1;

	return (pitch);
}

