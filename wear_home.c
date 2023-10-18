#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print in the code below
 * @flags:  Calculates active flags.
 * @width: get width of the formula
 * @precision: specify the precision
 * @size: Size specifier of the formula
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int g = 0;
	char cadd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		cadd = '0';

	buffer[g++] = c;
	buffer[g] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (g = 0; g < width - 1; g++)
			buffer[BUFF_SIZE - g - 2] = cadd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - g - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - g - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types and others
 * @buffer: Buffer array to handle display
 * @flags:  Calculates the flags that are active
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char cadd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		cadd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, cadd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer and others
 * @flags: Flags
 * @width: width and th rest
 * @prec: Precision specifiers
 * @length: Number length in the function
 * @padd: Pading char
 * @extra_c: Extra char and the rest
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char cadd, char extra_c)
{
	int g, cadd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = cadd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		cadd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (g = 1; g < width - length + 1; g++)
			buffer[g] = cadd;
		buffer[g] = '\0';
		if (flags & F_MINUS && cadd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], g - 1));
		}
		else if (!(flags & F_MINUS) && cadd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], g - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && cadd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--cadd_start] = extra_c;
			return (write(1, &buffer[cadd_start], g - cadd_start) +
				write(1, &buffer[ind], length - (1 - cadd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the figure is stated
 * @buffer: Array of chars and other data types
 * @flags: Flags specifiers
 * @width: Width specify here
 * @precision: Precision specifier
 * @size: Size specifier and others
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position g */
	int length = BUFF_SIZE - ind - 1, g = 0;
	char cadd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		cadd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		cadd = '0';

	if (width > length)
	{
		for (g = 0; g < width - length; g++)
			buffer[g] = cadd;

		buffer[g] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], g));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], g) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char cadd, char extra_c, int cadd_start)
{
	int g;

	if (width > length)
	{
		for(g = 3; g < width - length + 3; g++)
			buffer[g] = cadd;
		buffer[g] = '\0';
		if (flags & F_MINUS && cadd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], g - 3));
		}
		else if (!(flags & F_MINUS) && cadd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], g - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && cadd == '0')/* extra char to left of cadd */
		{
			if (extra_c)
				buffer[--cadd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[cadd_start], g - cadd_start) +
				write(1, &buffer[ind], length - (1 - cadd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

