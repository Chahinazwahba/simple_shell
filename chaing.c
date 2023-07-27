#include "shell.h"
/**
 * thehistory - Is displays history
 *@info: first param
 * Return: 0
*/
int thehistory(info_t *info)
{
listprt(info->history);
return (0);
}
/**
 *unset_alias - Is remove alias
 *@info: first param
 *@i: the second param
 * Return: 0 on success, 1 on error
*/
int unset_alias(info_t *info, char *i)
{
char *y, c;
int z;
y = strchr(i, '=');
if (!y)
return (1);
c = *y;
*y = 0;
z = index_dltnd(&(info->alias),
index_nde(info->alias, strt_nde(info->alias, i, -1)));
*y = c;
return (z);
}
/**
 * set_alias - IS sets alias
 * @info: first param
 *@i: the second param
 * Return: 0 on success, 1 on error
*/
int set_alias(info_t *info, char *i)
{
char *y;
y = strchr(i, '=');
if (!y)
return (1);
if (!*++y)
return (unset_alias(info, i));
unset_alias(info, i);
return (node_adend(&(info->alias), i, 0) == NULL);
}
/**
 * _printal - Is prints a string
 * @nd: the first param
 * Return: 0 on success, 1 on error
*/
int _printal(list_t *nd)
{
char *y = NULL, *a = NULL;
if (nd)
{
y = charc_stringf(nd->str, '=');
for (a = nd->str; a <= y; a++)
prtcharc (*a);
prtcharc('\'');
prtstring(y + 1);
prtstring("'\n");
return (0);
}
return (1);
}
/**
 * thealias - Is mimics alias
 * @info: first param
 * Return: 0
*/
int thealias(info_t *info)
{
int i = 0;
char *y = NULL;
list_t *nd = NULL;
if (info->argcount == 1)
{
nd = info->alias;
while (nd)
{
_printal(nd);
nd = nd->next;
}
return (0);
}
for (i = 1; info->argvarb[i]; i++)
{
y = strchr(info->argvarb[i], '=');
if (y)
set_alias(info, info->argvarb[i]);
else
_printal(strt_nde(info->alias, info->argvarb[i], '='));
}
return (0);
}
