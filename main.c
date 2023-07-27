#include "shell.h"
/**
* main - Is an entry point
* @ac: first param
* @av: second param
* Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;
	 asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puterror(av[0]);
				puterror(": 0: Can't open ");
				puterror(av[1]);
				put_erchar('\n');
				put_erchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		 info->inptfd = fd;
	}
	env_populate(info);
	hist_read(info);
	mn_shl(info, av);
	return (EXIT_SUCCESS);
}
