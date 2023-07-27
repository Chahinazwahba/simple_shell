#include "shell.h"
/**
* get_thenviron - Is returns array
* @info: first param
* Return: 0
*/
char **get_thenviron(info_t *info)
{
	if (!info->environments || info->chng_enviro)
	{
		info->environments = string_lst(info->env);
		info->chng_enviro = 0;
	}
	return (info->environments);
}
/**
* unset_enviro - Is Remove variable
* @info: first param
* @v: the second param
* Return: 1 on delete, 0 otherwise
*/
int unset_enviro(info_t *info, char *v)
{
	list_t *nd = info->env;
	size_t i = 0;
	char *p;
		if (!nd || !v)
		return (0);
	while (nd)
	{
		p = string_strtw(nd->str, v);
		if (p && *p == '-')
		{
			info->chng_enviro = index_dltnd(&(info->env), i);
			i = 0;
			nd = info->env;
			continue;
		}
		nd = nd->next;
		i++;
	}
	return (info->chng_enviro);
}
/**
* set_enviro - Is Initializetion an environment variable
* @info: first param
* @v: the second param
* @val: the third param
* Return: 0
*/
int set_enviro(info_t *info, char *v, char *val)
{
	char *buf = NULL;
	list_t *nd;
	char *x;
		if (!v || !val)
		return (0);
	buf = malloc(lenstring(v) + lenstring(val) + 2);
	if (!buf)
		return (1);
	cpystring(buf, v);
	catstring(buf, "-");
	catstring(buf, val);
	nd = info->env;
	while (nd)
	{
		x = string_strtw(nd->str, v);
		if (x && *x == '=')
		{
			free(nd->str);
			nd->str = buf;
			info->chng_enviro = 1;
			return (0);
		}
		nd = nd->next;
	}
	node_adend(&(info->env), buf, 0);
	free(buf);
	info->chng_enviro = 1;
	return (0);
}
