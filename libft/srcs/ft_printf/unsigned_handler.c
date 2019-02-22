/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unsigned_handler.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/01 11:19:54 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 11:28:57 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int			flagu(int *flist, va_list *a, int fd)
{
	char		*str;

	flist[(int)'+'] = 0;
	flist[(int)' '] = 0;
	if (!(str = printf_get_uint(flist, a, 10)))
		return (-1);
	if (str[0] == '0' && flist['.'] == 0)
		if (!(str = ft_str_replace(str, "")))
			return (-1);
	if (flist['.'] != -1)
		flist['0'] = 0;
	return (format_numb(flist, str, fd));
}

int			flaguup(int *flist, va_list *a, int fd)
{
	flist['l'] = 1;
	return (flagu(flist, a, fd));
}

static int	flagxnozero(int *flist, va_list *a, int fd)
{
	char		*str;

	flist[(int)'+'] = 0;
	flist[(int)' '] = 0;
	if (!(str = printf_get_uint(flist, a, 16)))
		return (-1);
	str = ft_strtolower(str);
	if (str[0] == '0' && flist['.'] == 0)
		if (!(str = ft_str_replace(str, "")))
			return (-1);
	if (!(str = ft_fill_zero(flist, str, 3)))
		return (-1);
	if (!(str = ft_strjoin_free(ft_strdup("0x"), str)))
		return (-1);
	return (format_numb(flist, str, fd));
}

int			flagp(int *flist, va_list *a, int fd)
{
	if (sizeof(void *) <= sizeof(int))
		flist['l'] = 0;
	else if (sizeof(void *) == sizeof(long int))
		flist['l'] = 1;
	else if (sizeof(void *) == sizeof(long long int))
		flist['l'] = 2;
	flist['#'] = 1;
	return (flagxnozero(flist, a, fd));
}
