#include "shell.h"
/**
 * mn_shl - Is main shell loop
 * @info: first param
 * @av: second param
 * Return: 0 on success, 1 on error
*/
int mn_shl(info_t *info, char **av)
{
ssize_t x = 0;
int builtin_ret = 0;
while (x != -1 && builtin_ret != -2)
{
infoclr(info);
if (isinteractv(info))
prtstring("$ ");
put_erchar(BUF_FLUSH);
x = gtusr_input(info);
if (x != -1)
{
infoset(info, av);
builtin_ret = builtin_findf(info);
if (builtin_ret == -1)
find_com(info);
}
else if (isinteractv(info))
prtcharc('\n');
infofr(info, 0);
}
hist_write(info);
infofr(info, 1);
if (!isinteractv(info) && info->allstatus)
exit(info->allstatus);
if (builtin_ret == -2)
{
if (info->error_numb == -1)
exit(info->allstatus);
exit(info->error_numb);
}
return (builtin_ret);
}
/**
 * builtin_findf - Is find command
 * @info: first param
 * Return: -1 ,-2 in exit()
*/
int builtin_findf(info_t *info)
{
int x, bRet = -1;
builtin_table builtintbl[] = {
{"exit", thexit},
{"env", thenviro},
{"help", thehelp},
{"history", thehistory},
{"setenv", thesetevn},
{"unsetenv", theunset_env},
{"alias", thealias},
{"x", thex},
{NULL, NULL}
};
for (x = 0; builtintbl[x].type; x++)
if (cmpstring(info->argvarb[0], builtintbl[x].type) == 0)
{
info->countli++;
bRet = builtintbl[x].func(info);
break;
}
return (bRet);
}
/**
 * find_com - Is find cmd
 * @info: first param
 * Return: void
*/
void find_com(info_t *info)
{
	char *pathfl = NULL;
	int x, k;
		info->pathfl = info->argvarb[0];
		if (info->licount_flg == 1)
		{
			info->countli++;
			info->licount_flg = 0;
		}
		for (x = 0, k = 0; info->argu[x]; x++)
		{
			if (!delim(info->argu[x], " \t\n"))
				k++;
		}
			if (!k)
				return;
			pathfl = path_fnd(info, enviro_get(info, "pathfl="), info->argvarb[0]);
			if (pathfl)
			{
				info->pathfl = pathfl;
				fork_com(info);
			}
			else
			{
				if ((isinteractv(info) || enviro_get(info, "pathfl=")
					|| info->argvarb[0][0] == '/') && thecmd(info, info->argvarb[0]))
				fork_com(info);
				else if (*(info->argu) != '\n')
				{
					info->allstatus = 127;
					errorprtt(info, "not found\n");
				}
			}
}
/**
 * fork_com - Is forks a an exec
 * @info: first param
 *Return: void
*/
void fork_com(info_t *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->pathfl, info->argvarb, get_thenviron(info)) == -1)
{
infofr(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->allstatus));
if (WIFEXITED(info->allstatus))
{
info->allstatus = WEXITSTATUS(info->allstatus);
if (info->allstatus == 126)
errorprtt(info, "Permission denied\n");
}
}
}
