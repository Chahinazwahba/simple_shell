#include "shell.h"
/**
 * buf_in - Is chaing commands
 * @info: first param
 * @buf: second param
 * @len: third param
 * Return: byte
*/
ssize_t buf_in(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;
		if (!*len)
		{
			free(*buf);
			*buf = NULL;
			signal(SIGINT, ctrlc_handle);
#if USE_GETLINE
x = getline(buf, &len_p, stdin);
#else
x = linegt(info, buf, &len_p);
#endif
if (x > 0)
{
if ((*buf)[x - 1] == '\n')
{
(*buf)[x - 1] = '\0';
x--;
}
info->licount_flg = 1;
cmmrmv(*buf);
hist_list(info, *buf, info->counting_hist++);
{
*len = x;
info->buffer_cmd = buf;
}
}
		}
return (x);
}

/**
 * gtusr_input - Is get line
 * @info: first param
 * Return: bytes read
*/
ssize_t gtusr_input(info_t *info)
{
static char *buf;
static size_t x, y, l;
ssize_t z = 0;
char **buf_p = &(info->argu), *p;
prtcharc(BUF_FLUSH);
z = buf_in(info, &buf, &l);
if (z == -1)
return (-1);
if (l)
{
y = x;
p = buf + x;
chain_chk(info, buf, &y, x, l);
while (y < l)
{
if (chaing(info, buf, &y))
break;
y++;
}
x = y + 1;
if (x >= l)
{
x = l = 0;
info->buffer_typcmd = CMD_NORM;
}
*buf_p = p;
return (lenstring(p));
}
*buf_p = buf;
return (z);
}
/**
 * read_buf - Is reads a buffer
 * @info: first param
 * @buf: second param
 * @x: third param
 *Return: z
*/
ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
ssize_t z = 0;
if (*x)
return (0);
z = read(info->inptfd, buf, READ_BUF_SIZE);
if (z >= 0)
*x = z;
return (z);
}
/**
 * linegt - Is gets the next line
 * @info: first param
 * @ptr: second param
 * @length: third param
 *Return: S
*/
int linegt(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, l;
	size_t g;
	ssize_t z = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
		p = *ptr;
	if (p && length)
		s = *length;
	if (x == l)
		x = l = 0;
	z = read_buf(info, buf, &l);
	if (z == -1 || (z == 0 && l == 0))
	{
		return (-1);
	}
	c = charc_stringf(buf + x, '\n');
	g = c ? 1 + (unsigned int) (c - buf) : l;
	new_p = mmry_reallc(p, s, s ? s + g : g + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
if (s)
cat_nstring(new_p, buf + x, g - x);
else
cpy_nstring(new_p, buf + x, g - x + 1);
s += g - x;
x = g;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}
/**
 * ctrlc_handle - Is blocks ctrl-C
 * @sig_num: first param
 * Return: void
*/
void ctrlc_handle(__attribute__((unused)) int sig_num)
{
prtstring("\n");
prtstring("$ ");
prtcharc(BUF_FLUSH);
}
