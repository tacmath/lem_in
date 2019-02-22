/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_format_numb.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 08:59:31 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 11:14:25 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static void	check_minus(char *str)
{
	int i;

	i = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '-')
		{
			str[i] = '0';
			str[0] = '-';
		}
	}
}

static void	check_space(char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (str[++i] != '\0')
	{
		if (str[i] == ' ')
		{
			if (ft_ischarset(str[i + 1], "0123456789"))
				str[i] = '0';
			if (ft_ischarset(str[i + 1], "0123456789"))
				str[0] = ' ';
		}
	}
}

static int	finish_numb(int *fl, char *s, int fd)
{
	int len;
	int size;

	if (fl[(int)'+'] > 0 && s[0] != '-')
		s = ft_strjoin_free(ft_strdup("+"), s);
	else if (fl[(int)' '] > 0 && s[0] != '-')
		s = ft_strjoin_free(ft_strdup(" "), s);
	if (!s)
		return (-1);
	len = ft_strlen(s);
	if (fl[(int)'0'] > 0 && fl[(int)'w'] > len && fl[(int)'-'] == 0
			&& fl[(int)'.'] < 1)
		s = ft_strjoin_free(ft_strset(fl[(int)'w'] - (ft_strlen(s)), '0'), s);
	else if (fl[(int)'w'] > len && fl[(int)'-'] == 0)
		s = ft_strjoin_free(ft_strset(fl[(int)'w'] - (ft_strlen(s)), ' '), s);
	else if (fl[(int)'w'] > len)
		s = ft_strjoin_free(s, ft_strset(fl[(int)'w'] - (ft_strlen(s)), ' '));
	if (!s)
		return (-1);
	if (fl[(int)'0'] > 0)
		check_space(s);
	size = write(fd, s, ft_strlen(s));
	free(s);
	return (size);
}

static int	precision(int *flist, char *str, int fd)
{
	int		minus;
	int		x;

	if (flist['.'] < 1)
		return (finish_numb(flist, str, fd));
	minus = str[0] == '-' ? 1 : 0;
	x = flist[(int)'.'] - (ft_strlen(str) - minus);
	if (x > 0)
		str = ft_strjoin_free(ft_strset(flist[(int)'.']
					- (ft_strlen(str) - minus), '0'), str);
	if (!str)
		return (-1);
	check_minus(str);
	return (finish_numb(flist, str, fd));
}

int			format_numb(int *fl, char *s, int fd)
{
	int			size;

	if (!s)
		return (-1);
	if (fl['.'] == -2)
		fl['0'] = 0;
	if (fl['0'] > 0 && fl['+'] > 0 && fl['-'] == 0 && fl['.'] < 1)
	{
		if (!(s = ft_strjoin_free(ft_strset(fl[(int)'w']
							- (ft_strlen(s) + 1), '0'), s)))
			return (-1);
		if (!(s = ft_strjoin_free(ft_strdup("+"), s)))
			return (-1);
		check_minus(s);
		size = write(fd, s, ft_strlen(s));
		free(s);
	}
	else
		size = precision(fl, s, fd);
	return (size);
}
