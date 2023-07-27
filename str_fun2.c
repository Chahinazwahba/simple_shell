#include "shell.h"
/**
* cpy_nstring - Is copieing a string
* @dest: the first param
* @src: the second param
* @n: the third param
* Return: concatenated string
*/
char *cpy_nstring(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
* cat_nstring - Is concatenates two strings
* @dest: the first param
* @src: the second param
* @n: the third param
* Return: concatenated string
*/

char *cat_nstring(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (s);
}
/**
* *charc_stringf - Is character in a string
* @s: the first param
* @c: the second param
* Return: pointer to the memory area s
*/
char *charc_stringf(char *s, char c)
{
	do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');
	return (NULL);
}
