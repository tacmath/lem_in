/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unico_handler.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 15:56:11 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 11:49:33 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <wchar.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

unsigned char			*check_wstr(va_list *a)
{
	unsigned char	*str;
	wchar_t			*tmp;

	tmp = ((wchar_t*)va_arg(*a, wchar_t*));
	if (!tmp)
	{
		str = (unsigned char *)ft_strdup("(null)");
	}
	else
		str = ft_handle_wchar(tmp);
	if (!str)
		return (NULL);
	return (str);
}

static unsigned char	*ft_sub_wchar(int *flist, unsigned char *str)
{
	int		i;
	int		lastend;
	int		len;

	len = ft_strlen((char *)str);
	i = 0;
	if (flist['.'] <= len && flist['.'] != -1)
	{
		while (i <= flist['.'])
		{
			lastend = 4;
			if (str[i] < 128)
				lastend = 1;
			else if (str[i] < 224)
				lastend = 2;
			else if (str[i] < 240)
				lastend = 3;
			if (i + lastend > flist['.'])
				str[i] = '\0';
			i += lastend;
		}
	}
	return (str);
}

int						flagsup(int *flist, va_list *a, int fd)
{
	unsigned char *str;

	if (!(str = check_wstr(a)))
		return (-1);
	flist[(int)' '] = 0;
	flist[(int)'+'] = 0;
	flist[(int)'#'] = 0;
	str = ft_sub_wchar(flist, str);
	flist[(int)'.'] = -1;
	return (format_numb(flist, (char*)str, fd));
}

int						flagcup(int *flist, va_list *a, int fd)
{
	wchar_t			*tmp;
	unsigned char	*str;

	if (!(tmp = malloc(sizeof(wchar_t) * 2)))
		return (-1);
	tmp[0] = va_arg(*a, wchar_t);
	tmp[1] = L'\0';
	str = ft_handle_wchar(tmp);
	if (tmp[0] == 0)
	{
		free(tmp);
		return (write(fd, "\0", 1));
	}
	free(tmp);
	if (!str)
		return (-1);
	flist[(int)' '] = 0;
	flist[(int)'+'] = 0;
	flist[(int)'#'] = 0;
	flist[(int)'.'] = -1;
	return (format_numb(flist, (char*)str, fd));
}
