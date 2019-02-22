/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string_handler.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 15:54:14 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 11:18:40 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static char	*check_str(va_list *a, int *flist)
{
	char *str;

	flist[(int)' '] = 0;
	flist[(int)'+'] = 0;
	flist[(int)'#'] = 0;
	str = ((char*)va_arg(*a, char*));
	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (!str)
		return (NULL);
	return (str);
}

int			flags(int *flist, va_list *a, int fd)
{
	char *str;
	char *tmp;

	if (flist['l'] > 0)
		return (flagsup(flist, a, fd));
	if (!(str = check_str(a, flist)))
		return (-1);
	tmp = str;
	if (flist[(int)'.'] > 0 && flist[(int)'.'] < (int)ft_strlen(str))
	{
		str = ft_strsub(str, 0, flist[(int)'.']);
		free(tmp);
	}
	else if (flist[(int)'.'] == 0)
	{
		free(tmp);
		if (!(str = ft_memalloc(1)))
			return (-1);
	}
	flist[(int)'.'] = -1;
	return (format_numb(flist, str, fd));
}

static int	put_zeroes(int *flist, char c, int fd)
{
	char	*filler;
	int		size;
	char	d;

	size = 0;
	d = flist[(int)'0'] > 0 && flist[(int)'-'] < 1 ? '0' : ' ';
	filler = ft_strset(flist[(int)'w'] - 1, d);
	if (!filler)
		return (-1);
	if (flist[(int)'-'] > 0)
		size += write(1, &c, 1);
	size += write(fd, filler, ft_strlen(filler));
	if (flist[(int)'-'] < 1)
		size += write(1, &c, 1);
	free(filler);
	return (size);
}

int			flagc(int *flist, va_list *a, int fd)
{
	char	c;
	int		size;

	if (flist['l'] > 0)
		return (flagcup(flist, a, fd));
	c = va_arg(*a, int);
	if (flist[(int)'w'] > 0)
	{
		size = put_zeroes(flist, c, fd);
	}
	else
		size = write(fd, &c, 1);
	return (size);
}
