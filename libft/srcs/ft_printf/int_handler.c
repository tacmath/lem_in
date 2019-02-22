/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   int_handler.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 14:41:51 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/11 17:56:36 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

/*
** Need to remove all
** if (str[0] == '0' && flist['.'] == 0  && flist['0'] > 0) after corrections
** Simple imitation
*/

int			flagd(int *flist, va_list *a, int fd)
{
	char		*str;

	if (!(str = printf_get_int(flist, a)))
		return (-1);
	if (str[0] == '0' && flist['.'] == 0)
	{
		free(str);
		if (!(str = ft_strdup("")))
			return (-1);
	}
	if (flist['.'] != -1)
		flist['0'] = 0;
	if (str[0] == '-' && flist['0'] > 0 && (flist['.'] > 0 ||
				flist['w'] > 0) && flist['-'] < 1)
	{
		if (!(str = ft_strsub_free(str, 1, ft_strlen(str) - 1)))
			return (-1);
		if (!(str = ft_fill_zero(flist, str, 1)))
			return (-1);
		if (str[0] != '0' && !(str = ft_strjoin_free(ft_strdup(" "), str)))
			return (-1);
		str[0] = '-';
	}
	return (format_numb(flist, str, fd));
}

int			flagdup(int *flist, va_list *a, int fd)
{
	flist['l'] = 1;
	return (flagd(flist, a, fd));
}

int			flago(int *flist, va_list *a, int fd)
{
	char		*str;
	int			zero;

	flist[(int)'+'] = 0;
	flist[(int)' '] = 0;
	if (!(str = printf_get_uint(flist, a, 8)))
		return (-1);
	if (str[0] == '0' && flist['.'] == 0)
		if (!(str = ft_str_replace(str, "")))
			return (-1);
	zero = str[0] == '0' ? 1 : 0;
	if (!(str = ft_fill_zero(flist, str, 1)))
		return (0);
	if (flist[(int)'#'] > 0 && zero != 1)
		if (!(str = ft_strjoin_free(ft_strdup("0"), str)))
			return (-1);
	return (format_numb(flist, str, fd));
}

int			flagx(int *flist, va_list *a, int fd)
{
	char		*str;
	int			zero;

	flist[(int)'+'] = 0;
	flist[(int)' '] = 0;
	if (!(str = printf_get_uint(flist, a, 16)))
		return (-1);
	str = ft_strtolower(str);
	if (str[0] == '0' && flist['.'] == 0)
	{
		if (!(str = ft_str_replace(str, "")))
			return (-1);
		flist['#'] = 0;
	}
	zero = str[0] == '0' ? 1 : 0;
	if (!(str = ft_fill_zero(flist, str, (!zero) * 2)))
		return (-1);
	if (flist[(int)'#'] > 0 && zero != 1)
		if (!(str = ft_strjoin_free(ft_strdup("0x"), str)))
			return (-1);
	return (format_numb(flist, str, fd));
}

int			flagxup(int *flist, va_list *a, int fd)
{
	char		*str;
	int			zero;

	flist[(int)'+'] = 0;
	flist[(int)' '] = 0;
	if (!(str = printf_get_uint(flist, a, 16)))
		return (-1);
	if (str[0] == '0' && flist['.'] == 0)
	{
		if (!(str = ft_str_replace(str, "")))
			return (-1);
		flist['#'] = 0;
	}
	zero = str[0] == '0' ? 1 : 0;
	if (!(str = ft_fill_zero(flist, str, 2)))
		return (-1);
	if (flist[(int)'#'] > 0 && zero != 1)
		if (!(str = ft_strjoin_free(ft_strdup("0X"), str)))
			return (-1);
	return (format_numb(flist, str, fd));
}
