#include "shell.h"

/**
* cpystring - Is copieing a string
* @dest: the first param
* @src: the second param
* Return: pointer
*/

char *cpystring(char *dest, char *src)
{
	int x = 0;
		if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
* dplstring - Is duplicates a string
* @str: the first param
* Return: string
*/

char *dplstring(const char *str)
{
	int length = 0;
	char *ret;
		if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
* prtstring - Is printing string
*@str: the first param
* Return: Nothing
*/

void prtstring(char *str)
{
	int x = 0;
		if (!str)
		return;
	while (str[x] != '\0')
	{
		prtcharc(str[x]);
		x++;
	}
}

/**
* prtcharc - Is writeing a character
* @c: the first param
* Return: 1 On success
*/

int prtcharc(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
		if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
