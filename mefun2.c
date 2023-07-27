#include "shell.h"
/**
* block_afree - Is frees a pointer
* @ptr: the first param
* Return: 1 if freed, otherwise 0.
*/
int block_afree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
