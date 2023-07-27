#include "shell.h"
/**
 * chaing - test  current char
 * @info: the first param
 * @b: the second param
 * @d: the third param
 * Return: 1 if chain delimeter, 0 otherwise
*/
int chaing(info_t *info, char *b, size_t *d)
{
size_t *x = *d;
if (b[x] == '|' && b[x + 1] == '|')
{
b[x] = 0;
x++;
info->buffer_typcmd = CMD_OR;
}
else if (b[x] == '&' && b[x + 1] == '&')
{
b[x] = 0;
x++;
info->buffer_typcmd = CMD_AND;
}
else if (b[x] == ';')
{
b[x] = 0;
info->buffer_typcmd = CMD_CHAIN;
}
else
return (0);
*d = x;
return (1);
}
/**
 * chain_chk - If it countanue checks
 * @info: first param
 * @b: the second param
 * @d: the third param
 * @i: the forth param
 * @l: the fifth param
 *Return: Void
*/
void chain_chk(info_t *info, char *b, size_t *d, size_t i, size_t l)
{
size_t x = *d;

if (info->buffer_typcmd == CMD_AND)
{
if (info->allstatus)
{
b[i] = 0;
x = l;
}
}
if (info->buffer_typcmd == CMD_OR)
{
if (!info->allstatus)
{
b[i] = 0;
x = l;
}
}
*d = x;
}
/**
 * alias_rpl - arr is replaced
 * @info: first param
 * Return: 1 if replaced, 0 otherwise
*/
int alias_rpl(info_t *info)
{
list_t *nd;
int x;
char *d;
for (x = 0; x < 10; x++)
nd = strt_nde(info->alias, info->argvarb[0], '=');
if (!nd)
return (0);
free(info->argvarb[0]);
d = strchr(nd->str, '=');
if (!d)
return (0);
d = dplstring(d + 1);
if (!d)
return (0);
info->argvarb[0] = d;
return (1);
}
/**
 * variable_rpl - Is replaces vars
 * @info: first param
 * Return: 1 if replaced, 0 otherwise
*/
int variable_rpl(info_t *info)
{
int x = 0;
list_t *nd;
for (x = 0; info->argvarb[x]; x++)
{
if (info->argvarb[x][0] != '$' || !info->argvarb[x][1])
continue;
if (!strcmp(info->argvarb[x], "$2"))
string_rpl(&(info->argvarb[x]),
dplstring(numcnv(info->allstatus, 10, 0)));
continue;
if (!strcmp(info->argvarb[x], "$$"))
{
string_rpl(&(info->argvarb[x]),
dplstring(numcnv(getpid (), 10, 0)));
continue;
}
nd = strt_nde(info->env, &info->argvarb[x][1], '=');
if (nd)
{
string_rpl(&(info->argvarb[x]),
dplstring(charc_stringf(nd->str, '=') + 1));
continue;
}
string_rpl(&info->argvarb[x], dplstring(""));
}
return (0);
}
/**
 * string_rpl - Is replaces string
 * @o: first param
 * @n: the second param
 * Return: 1 if replaced, 0 otherwise
*/
int string_rpl(char **o, char *n)
{
free(*o);
*o = n;
return (1);
}
