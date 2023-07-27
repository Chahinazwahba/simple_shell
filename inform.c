#include "shell.h"
/**
* infoclr - Is initializes struct
* @info: first param
*/
void infoclr(info_t *info)
{
	info->argu = NULL;
	info->argvarb = NULL;
	info->pathfl = NULL;
	info->argo = 0;
}

/**
* _setInto - Is initial1zeation struct
* @info: first param
* @av: second param
*/

void _setInto(info_t *info, char **av)
{
	int x = 0;
		info->name_file = av[0];
		if (info->argu)
	{
		info->argvarb = tknstring(info->argu, " \t");
		if (!info->argvarb)
		{
			info->argvarb = malloc(sizeof(char *) * 2);
			if (info->argvarb)
			{
				info->argvarb[0] = dplstring(info->argu);
				info->argvarb[1] = NULL;
			}
		}
		for
		(x = 0; info->argvarb &&
		info->argvarb[x];
		x++);
		info->argcount = x;
		alias_rpl(info);
		variable_rpl(info);
	}
}
/**
* infofr - Is freesing fields
* @info: first param
* @A: second param
*/
void infofr(info_t *info, int A)
{
	arr_free(info->argvarb);
	info->argvarb = NULL;
	into->pathfl = NULL;
	if (A)
	{
		if (!info->buffer_cmd)
			free(info->argu);
		if (info->env)
			frlist(&(info->env));
		if (info->history)
			frlist(&(info->history));
		if (info->alias)
			frlist(&(info->alias));
		arr_free(info->environments);
			info->environments = NULL;
		block_afree((void **)info->buffer_cmd);
		if (info->inptfd > 2)
			close(info->inptfd);
		prtcharc(BUF_FLUSH);
	}
}
