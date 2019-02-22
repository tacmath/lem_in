/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parser.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/25 13:08:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/13 09:27:40 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

static int	ft_endformat(const char *format)
{
	int	i;

	i = -1;
	while (format[++i] != '\0')
	{
		if (!(ft_ischarset(format[i], "hHlLjz .#0123456789+-*")))
		{
			return (i);
		}
	}
	return (-1);
}

/*
** we put all the flags in flist at the index [flag]
** width in w & precision in .
*/

static int	ft_arg_handler_bis(char *flags, t_fnct *fnct, int *flist, int fd)
{
	int size;

	size = 0;
	if (fnct[(int)flags[(int)flags[0]]] != fnct[0] || flags[(int)flags[0]] ==
			'@')
		;
	else if (flags[(int)flags[0]] == '!')
	{
		fnct[0] = NULL;
		ft_init_funk(fnct);
		size = write(fd, "ft_printf Reset!", 16);
	}
	else
		size = fnct[(int)flags[(int)flags[0]]](flist,
				(va_list *)&flags[(int)flags[0]], fd);
	free(flist);
	free(flags);
	if (size < 0)
		return (-1);
	return (size);
}

static int	ft_arg_handler(char *flags, va_list *args, int fd, int i)
{
	int				*flist;
	int				len;
	int				size;
	static t_fnct	fnct[128] = {0};

	size = 0;
	if (!flags)
		return (-1);
	if ((len = ft_strlen(flags)) < 2)
		free(flags);
	if (len < 2 || !args || (flist = ft_memalloc(sizeof(int) * 128)) == NULL)
		return (len < 2 ? 0 : -1);
	ft_init_funk(fnct);
	flags[0] = (int)len - 1;
	while (++i < len - 1)
		flist[(int)flags[i]] += 1;
	ft_getprec(flags, flist, args);
	if (fnct[(int)flags[len - 1]] != fnct[0] && flags[len - 1] != '@'
			&& flags[len - 1] != '!')
		size = fnct[(int)flags[len - 1]]((int*)flist, (va_list*)args, fd);
	else if (flags[len - 1] == '@')
		size = flagadd(fnct, args, fd);
	return (size + ft_arg_handler_bis(flags, fnct, flist, fd));
}

static int	checksize(int *size, int write_ret)
{
	if (*size > -1 && write_ret > -1)
		*size += write_ret;
	else
		*size = -1;
	return (*size);
}

int			ft_parser(const char *restrict str, va_list *args, int fd)
{
	int			start;
	int			end;
	int			last;
	int			size;

	size = 0;
	end = -2;
	last = 0;
	while (end != 0 && end != -1)
	{
		start = ft_strchri((char *)&(str[last]), '%');
		start = start == -1 ? -1 : start + last;
		end = 0;
		if (start != -1)
		{
			checksize(&size, write(fd, &str[last], start - last));
			end = ft_endformat(&str[start + 1]) + 1;
			if (end != -1)
				checksize(&size, ft_arg_handler(ft_strsub(str, start, end + 1),
						args, fd, 0));
			last = end != -1 ? start + end + 1 : last;
		}
	}
	return (checksize(&size, write(fd, &(str[last]), ft_strlen(str) - last)));
}
