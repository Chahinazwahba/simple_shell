#include "shell.h"
/**
* puterror - Is print a string
* @str: the frist param
* Return: Nothing
*/
void puterror(char *str)
{
	int x = 0;
		if (!str)
		return;
	while (str[x] != '\0')
	{
		put_erchar(str[x]);
		x++;
	}
}
/**
* put_erchar - Is writes character
* @c: the frist param
* Return: On success 1.-1 on error
*/
int put_erchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
		if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
/**
* char_P - Is writes the character
* @c: first param
* @fd: The second param
* Return: On success 1.
*/
int char_P(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
		if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
/**
* put_stringf - Is prints an input string
* @str: first param
* @fd: second param
* Return: num of char
*/
int put_stringf(char *str, int fd)
{
	int x = 0;
		if (!str)
		return (0);
	while (*str)
	{
		x += char_P(*str++, fd);
	}
	return (x);
}
