#include "main.h"

/**
 * get_flags - Calculates active flags as done previously
 * @format: Formatted string in which to print the arguments and function
 * @n: must be given a parameter
 * Return: Flags:
 */
int get_flags(const char *format, int *n)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int a, curr_n;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_n = *n + 1; format[curr_n] != '\0'; curr_n++)
	{
		for (a = 0; FLAGS_CH[a] != '\0'; a++)
			if (format[curr_n] == FLAGS_CH[a])
			{
				flags |= FLAGS_ARR[a];
				break;
			}

		if (FLAGS_CH[a] == 0)
			break;
	}

	*n = curr_n - 1;

	return (flags);
}

