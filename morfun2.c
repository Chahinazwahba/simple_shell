#include "shell.h"
/**
* intr_error - Is converting a string
* @s: the frist param
* Return: 0 ,-1 on error
*/
int intr_error(char *s)
{
	int x = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (x = 0; s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			r *= 10;
			r += (s[x] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
* errorprtt - Is printing an error
* @info: the frist param
* @estr: the second param
* Return: 0 ,-1 on error
*/
void errorprtt(info_t *info, char *estr)
{
	puterror(info->name_file);
	puterror(": ");
	intr_prt(info->countli, STDERR_FILENO);
	puterror(": ");
	puterror(info->argvarb[0]);
	puterror(": ");
	puterror(estr);
}

/**
* intr_prt - Is prints a decimal
* @input: the frist param
* @fd: the second
* Return: num of characters printed
*/

int intr_prt(int input, int fd)
{
	int (*__putchar)(char) = prtcharc;
	int x, c = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = put_erchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar ('0' + current / x);
			c++;
		}
		current %= x;
	}
	__putchar('0' + current);
	c++;

	return (c);
}
/**
* numcnv - converter function
* @num: the frist param
* @base: the second param
* @flags : the third param
* Return: string
*/
char *numcnv(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;

	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abxef" : "0123456789ABxEF";
	ptr = &buffer[49];
*ptr = '\0';

	do {
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

if (sign)
{
*--ptr = sign;
}
	return (ptr);
}

/**
* cmmrmv - replaces first instance
* @buf: the frist param
* Return: 0;
*/
void cmmrmv(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '%' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
