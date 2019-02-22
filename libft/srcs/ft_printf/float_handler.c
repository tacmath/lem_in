/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   float_handler.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 14:10:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 11:02:36 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char	*minus_zero(int *flist, char *str)
{
	char	*tmp;
	int		len;

	flist['.'] = flist['.'] == -1 ? 6 : flist['.'];
	if ((ft_strcmp(str, "-0") == 0) && flist['.'] > 0)
	{
		if (!(str = ft_strjoin_free(str, ft_strdup("."))))
			return (NULL);
		if (!(tmp = ft_strset(flist['.'], '0')))
			return (NULL);
		if (!(str = ft_strjoin_free(str, tmp)))
			return (NULL);
	}
	len = ft_strlen(str);
	if ((str[0] == '-' && flist['w'] - len > 0 && flist['0'] > 0))
	{
		str[0] = '0';
		if (!(tmp = ft_strset(flist['w'] - len, '0')))
			return (NULL);
		if (!(str = ft_strjoin_free(tmp, str)))
			return (NULL);
		flist['w'] = -1;
		str[0] = '-';
	}
	return (str);
}

int			flagf(int *flist, va_list *a, int fd)
{
	char		*str;

	if (flist['L'] > 0)
		str = ft_ldtoa(va_arg(*a, long double), flist['.']);
	else
		str = ft_ldtoa((long double)va_arg(*a, double), flist['.']);
	if (!str)
		return (-1);
	if (ft_isalpha(str[1]))
	{
		flist['0'] = -1;
		flist['.'] = -1;
		flist['+'] = -1;
		flist[' '] = -1;
	}
	if (!(str = minus_zero(flist, str)))
		return (-1);
	flist['.'] = -1;
	return (format_numb(flist, str, fd));
}

int			flagfup(int *flist, va_list *a, int fd)
{
	flist['l'] = 1;
	return (flagf(flist, a, fd));
}
