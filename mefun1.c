#include "shell.h"
/**
* *set_memory - Is a memory files
* @s: the first param
* @b: the second param
* @n: the third param
* Return: pointer
*/
char *set_memory(char *s, char b, unsigned int n)
{
	unsigned int x;
		for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}
/**
* arr_free - A free string
* @bb: first param
*/
void arr_free(char **bb)
{
	char **a = bb;
		if (!bb)
		return;
	while (*bb)
		free(*bb++);
	free(a);
}
/**
* mmry_reallc - Is reallocates a block of memory
* @ptr: first param
* @o_s: second param
* @newS: third param
*
* Return: pointer to da ol'block nameen.
*/

void *mmry_reallc(void *ptr, unsigned int o_s, unsigned int newS)
{
	char *x;
		if (!ptr)
		return (malloc(newS));
	if (!newS)
		return (free(ptr), NULL);
	if (newS == o_s)
		return (ptr);
	x = malloc(newS);
	if (!x)
		return (NULL);
	o_s = o_s < newS ? o_s : newS;
	while (o_s--)
		x[o_s] = ((char *)ptr)[o_s];
	free(ptr);
	return (x);
}
