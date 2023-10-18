#include "main.h"

/****************** PRINT POINTER ******************/
/**
<<<<<<< HEAD
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments and output them
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width correecly
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed is important
=======
 * print_pointer - Print the values given of a pointer variable
 * @types: List the ouput of  a of spoken  arguments
 * @buffer: Buffer array to handles num values called  print
 * @flags:  Calculates the total variant of the  active flags
 * @width: get width that x was the constant
 * @precision: Precision specifications in an a constant repository
 * @size: Size specifiers active on nodes
 * Return: Number of chars printed assumming the nums were positive.
>>>>>>> 2c6507f866dbfdaa2203371bb6f4b62536cc0d94
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int son = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[son--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	son++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, son, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print and calculate
 * @flags:  Calculates active flags
 * @width: get width and th rest of them
 * @precision: Precision specification
 * @size: Size specifier for the project
 * Return: Number of chars printed and display this on the screen
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int z = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[z] != '\0')
	{
		if (is_printable(str[z]))
			buffer[z + offset] = str[z];
		else
			offset += append_hexa_code(str[z], buffer, z + offset);

		z++;
	}

	buffer[z + offset] = '\0';

	return (write(1, buffer, z + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width to do the work as stated
 * @precision: Precision specification
 * @size: Size specifier and the rest
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int z, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (z = 0; str[z]; z++)
		;

	for (z = z - 1; z >= 0; z--)
	{
		char z = str[z];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments of the function
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specifications of the formula
 * @size: Size specifier and the rest of them
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int z, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (z = 0; str[z]; z++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[z])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[z];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

