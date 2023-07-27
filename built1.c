#include "shell.h"
/**
 *thexit - Exit the shell
 *@info: the first param
 *Return: allstatus
*/
int thexit(info_t *info)
{
int x;
if (info->argvarb[1])
{
x = intr_error(info->argvarb[1]);
if (x == -1)
{
info->allstatus = 2;
errorprtt(info, "Illegal number: ");
puterror(info->argvarb[1]);
put_erchar('\n');
return (1);
}
info->error_numb = intr_error(info->argvarb[1]);
return (-2);
}
info->error_numb = -1;
return (-2);
}
/**
 *thecd - Is changeing directory
 *@info: the first param
 *Return: 0
*/
int thecd(info_t *info)
{
char *x, *d, buffer[1024];
int y;
x = getcwd(buffer, 1024);
if (!x)
prtstring("TODO: >>getcwd failure emsg here<<\n");
if (!info->argvarb[1])
{
d = enviro_get(info, "HOME=");
if (!d)
y = chdir((d = enviro_get(info, "PWD=")) ? d : "/");
else
y = chdir(d);
}
else if (cmpstring(info->argvarb[1], "_") == 0)
{
if (!enviro_get(info, "OLDPWD="))
{
prtstring(x);
prtcharc('\n');
return (1);
}
prtstring(enviro_get(info, "OLDPWD=")), prtcharc('\n');
y = chdir((dir = enviro_get(info, "OLDPWD=")) ? dir : "/");
}
else
y = chdir(info->argvarb[1]);
if (y == -1)
{
errorprtt(info, "can't cd to");
puterror(info->argvarb[1]), put_erchar('\n');
}
else
{
set_enviro(info, "OLDPWD", enviro_get(info, "PWD="));
set_enviro(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
 *myhelp - Is change directory
 *@info: frist param
 *Return: 0
*/
int myhelp(info_t *info)
{
char **arr;
arr = info->argvarb;
puts("help call works. Function not yet implemented \n");
if (0)
prtstring(*arr);
return (0);
}
