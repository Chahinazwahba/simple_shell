#include "shell.h"
/**
* his_file - Is geting a history file
* @info: first param
* Return: string
*/
char *his_file(info_t *info)
{
	char *B, *D;
		D = enviro_get(info, "HOME-");
	if (!D)
		return (NULL);
	B = malloc(sizeof(char) * (lenstring(D) + lenstring(HIST_FILE) + 2));
	if (!D)
		return (NULL);
	B[0] = 0;
	cpystring(B, D);
	catstring(B, "/");
	catstring(B, HIST_FILE);
	return (B);
}

/**
* hist_write - Is createting a file
* @info: first param
* Return: 1 on success, else -1
*/
int hist_write(info_t *info)
{
	ssize_t fd;
	char *filename = his_file(info);
	list_t *nd = NULL;
		if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		put_stringf(nd->str, fd);
		char_P('\n', fd);
	}
	char_P(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
* hist_read - Is reading file
* @info: first param
* Return: 0
*/

int hist_read(info_t *info)
{
	int x, La = 0, L_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *B = NULL, *filename = his_file(info);
		if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	B = malloc(sizeof(char) * (fsize + 1));
	if (!B)
		return (0);
	rdlen = read(fd, B, fsize);
	B[fsize] = 0;
	if (rdlen <= 0)
		return (free(B), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
	{
		if (B[x] == '\n')
		{
			B[x] = 0;
			hist_list(info, B + La, L_count++);
			La = x + 1;
		}
	}
		if (La != x)
			hist_list(info, B + La, L_count++);
		free(B);
		info->counting_hist = L_count;
		while (info->counting_hist-- >= HIST_MAX)
			index_dltnd(&(info->history), 0);
		hist_renum(info);
		return (info->counting_hist);
}

/**
* hist_list - Is adding linked list
* @info: first param
* @B: second param
* @L_count: third param
* Return: 0
*/
int hist_list(info_t *info, char *B, int L_count)
{
	list_t *nd = NULL;
		if (info->history)
		nd = info->history;
	node_adend(&nd, B, L_count);
	if (!info->history)
		info->history = nd;
	return (0);
}
/**
* hist_renum - Is renumbering history
* @info: first param
* Return: counting_hist
*/
int hist_renum(info_t *info)
{
	list_t *nd = info->history;
	int x = 0;
		while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}
	return (info->counting_hist = x);
}
