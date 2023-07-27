#include "shell.h"
/**
 * thecmd - Is file executable command
 * @info: the first param
 * @pathfl: the second param
 * Return: 1
*/
int thecmd(info_t *info, char *pathfl)
{
struct stat st;
(void)info;
if (!pathfl || stat(pathfl, &st))
return (0);
if (st.st_mode && S_IFREG)
{
return (1);
}
return (0);
}
/**
 * *charac_dplct - Is duple characters
 * *@pathistr: the first param
 * @start: the second param
 * @end: the third param
 * Return: arr
*/
char *charac_dplct(char *pathistr, int start, int end)
{
static char buf[1024];
int x = 0, z = 0;
for (z = 0, x = start; x < end; x++)
if (pathistr[x] != ':')
buf[z++] = pathistr[x];
buf[z] = 0;
return (buf);
}
/**
 * *path_fnd - If find cmd pathfl
 * @info: the first param
 * @pathistr: the second param
 * @cmd: the third param
 * Return: pathfl of cmd
*/
char *path_fnd(info_t *info, char *pathistr, char *cmd)
{
int x = 0, curr_pos = 0;
char *pathfl;
if (!pathistr)
return (NULL);
if ((lenstring(cmd) > 2) && string_strtw(cmd, "./"))
{
if (thecmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathistr[x] || pathistr[x] == ':')
{
pathfl = charac_dplct(pathistr, curr_pos, x);
if (!*pathfl)
catstring(pathfl, cmd);
else
{
catstring(pathfl, "/");
catstring(pathfl, cmd);
}
if (thecmd(info, pathfl))
return (pathfl);
if (!pathistr[x])
break;
curr_pos = x;
}
x++;
}
return (NULL);
}
