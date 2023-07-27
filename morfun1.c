#include "shell.h"
/**
* isinteractv - Is true if shell is isinteractv
* @info: the frist param
* Return: 1 , 0 otherwise
*/
int isinteractv(info_t *info)
{
	return (isatty(STDIN_ FILENO) && info - ›inptfd <= 2);
}
/**
* delim - Is check character is a delimeter
* @c: the frist param
* @n: the second param
* Return: 1
*/
int delim(char c, char *n)
{
	while (*n)
		if (*n++ == c)
			return (1);
		return (0);
}
/**
* aalpha - Is checks for alphabetic
* @c: The frist param
* Return: 1
*/
int aalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
* integerstr - Is converting a string
* @s: the frist param
* Return: 0
*/
int integerstr(char *s)
{
	int x, sign = 1, flag = 0, o;
	unsigned int r = 0;
		for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;
		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			r *= 10;
			r += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		o = -r;
	else
		o = r;
	return (o);
}
