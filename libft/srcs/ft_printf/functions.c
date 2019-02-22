/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   functions.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 09:24:20 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 11:17:34 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

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

static int	invalid(int *flist, char c, int fd)
{
	int		size;

	size = 0;
	if (flist[(int)'w'] > 0)
	{
		size = put_zeroes(flist, c, fd);
	}
	else if (c != '%')
		size = write(fd, &c, 1);
	return (size);
}

static int	phony(int *s, va_list *a, int fd)
{
	char c;

	c = *(char*)a;
	return (invalid(s, c, fd));
}

static void	ft_more_funk(t_fnct *ret)
{
	ret[(int)('%')] = &flagpercent;
	ret[(int)('O')] = &flagoup;
	ret[(int)('F')] = &flagfup;
	ret[(int)('X')] = &flagxup;
	ret[(int)('f')] = &flagf;
	ret[(int)('b')] = &flagb;
	ret[(int)('S')] = &flagsup;
	ret[(int)('C')] = &flagcup;
	ret[(int)('U')] = &flaguup;
	ret[(int)('D')] = &flagdup;
}

void		ft_init_funk(t_fnct *ret)
{
	int	i;

	if (ret[0] == 0)
	{
		i = -1;
		while (++i < 128)
			ret[i] = &phony;
		ret[(int)('c')] = &flagc;
		ret[(int)('s')] = &flags;
		ret[(int)('p')] = &flagp;
		ret[(int)('d')] = &flagd;
		ret[(int)('i')] = &flagd;
		ret[(int)('o')] = &flago;
		ret[(int)('u')] = &flagu;
		ret[(int)('x')] = &flagx;
		ft_more_funk(ret);
	}
}
