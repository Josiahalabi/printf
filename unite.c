#include "main.h"

/**
 * is_printable - Evaluate if the data type is printable
 * @r: Char to be calculated.
 *
 * Return: 1 if r is printable or return 0
 */
int is_printable(char r)
{
	if (r >= 32 && r < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars and others
 * @i: Index at which to start appending or else do otherwise
 * @ascii_code: ASSCI CODE.
 * Return: Always 3 and not 0
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @r: Char to be evaluated
 *
 * Return: 1 if r is a digit, 0 otherwise
 */
int is_digit(char r)
{
	if (r >= '0' && r  <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size and others
 * @num: Number to be printed
 * @size: Number indicating the type to be casted or printed
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

