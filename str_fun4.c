#include "shell.h"

/**
* lenstring - Is the length of a string
* @s: the first param
* Return: length of string
*/

int lenstring(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
* cmpstring - Is performs lexicogarphic comparison of two strange.
* @s1: the first param
* @s2: the second param
*Return: 1
*/

int cmpstring(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
* *string_strtw - Is checking If needle is haystack
* @haystack: the first param
* @needle: the second param
* Return: char of haystack
*/

char *string_strtw(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
		return ((char *)haystack);
}

/**
* catstring - Is two strings
* @dest: the first param
* @src: the second param
* Return: destination butter
*/

char *catstring(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
