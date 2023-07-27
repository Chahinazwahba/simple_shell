#include "shell.h"
/**
* thenviro - Is printing
* @info: first param
* Return: 0
*/
int thenviro(info_t *info)
{
	string_liprt(info->env);
	return (0);
}
/**
* enviro_get - IS gets the value
* @info: first param
* @N: second param
* Return: value
*/
char *enviro_get(info_t *info, const char *N)
{
	list_t *nd = info->enva;
	char *PS;
		while (nd)
	{
		PS = string_strtw(nd->str, N);
		if (PS && *PS)
			return (PS);
		nd = nd->next;
	}
	return (NULL);
}
/**
* thesetevn - Is Initialize variable,
* @info: first param
* Return: 0
*/
int thesetevn(info_t *info)
{
if (info->argcount != 3)
{
puterror("Incorrect number of arguments\n");
return (1);
}
if (set_enviro(info, info->argvarb[1], info->argvarb[2]))
return (0);
return (1);
}
/**
* theunset_env - Is Removeing variable
* @info: first param
* Return: 0
*/
int theunset_env(info_t *info)
{
int x;
if (info->argcount == 1)
{
puterror("Too few arguments.\n");
return (1);
}
for (x = 1; x <= info->argcount; x++)
unset_enviro(info, info->argvarb[x]);
return (0);
}
/**
* env_populate - dube linked list
* @info: first param
* Return: 0
*/
int env_populate(info_t *info)
{
	list_t *nd = NULL;
	size_t x;
		for (x = 0; environments[x]; x++)
		node_adend(&nd, environments[x], 0);
	info->env = nd;
	return (0);
}
