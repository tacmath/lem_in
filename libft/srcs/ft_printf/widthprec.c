/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   widthprec.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 18:02:39 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 15:45:28 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static void		getwidth(char *flags, int *flist, int *i)
{
	if (flags[*i] == '0')
	{
		flist[(int)'0'] = 1;
		while (flags[*i] == '0')
			(*i)++;
	}
	if (flags[*i] >= '0' && flags[*i] <= '9')
		flist[(int)'w'] = ft_atoi(&flags[*i]);
	while (ft_isdigit(flags[*i]))
		(*i)++;
	(*i)--;
}

static void		ft_getdot(char *str, int *i, int *flist)
{
	int nbr;

	nbr = 0;
	flist['.'] = nbr;
	if (ft_isdigit(str[*i + 1]))
	{
		while (ft_isdigit(str[++(*i)]))
			nbr = nbr * 10 + str[*i] - '0';
		flist['.'] = nbr;
	}
	else
		flist[(int)'.'] = 0;
}

static void		ft_get_wild(char *str, va_list *a, int *flist)
{
	int	nbr;

	nbr = va_arg(*a, int);
	if (nbr < 0)
	{
		nbr *= -1;
		if (str[0] == '.')
		{
			nbr = -1;
		}
		else
		{
			flist['-']++;
		}
	}
	if (str[0] == '.')
		flist[(int)'.'] = nbr;
	else
		flist[(int)'w'] = nbr;
}

void			ft_getprec(char *flags, int *flist, va_list *a)
{
	int	i;
	int len;
	int temp;

	i = 0;
	len = ft_strlen(flags);
	temp = flist[(int)'.'];
	flist[(int)'.'] = -1;
	flist[(int)'w'] = -1;
	flist[(int)'0'] = 0;
	while (++i < len)
	{
		if (flags[i] == '.')
			ft_getdot(flags, &i, flist);
		else if (flags[i] >= '0' && flags[i] <= '9')
		{
			if (flags[i - 1] != '.')
				getwidth(flags, flist, &i);
		}
		else if (flags[i] == '*')
			ft_get_wild(&flags[i - 1], a, flist);
	}
}
