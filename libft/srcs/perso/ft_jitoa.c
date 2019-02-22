/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jitoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 16:48:42 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/04 16:50:43 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_jsize(intmax_t nbr)
{
	int size;

	size = 1;
	if (nbr < 0)
	{
		size++;
	}
	if (nbr == 0)
		size++;
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

char		*ft_jitoa(intmax_t nbr)
{
	char			*rep;
	int				i;
	int				size;
	intmax_t		temp;
	int				neg;

	neg = -1;
	size = ft_jsize(nbr);
	i = 0;
	if (!(rep = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	if (nbr < 0)
		rep[0] = '-';
	neg = (nbr < 0) ? 1 : 0;
	while (i < size - 1 - neg)
	{
		temp = nbr % 10;
		nbr /= 10;
		if (temp < 0)
			temp *= -1;
		rep[size - 2 - i] = temp + '0';
		i++;
	}
	return (rep);
}

static int	ft_zsize(ssize_t nbr)
{
	int size;

	size = 1;
	if (nbr < 0)
	{
		size++;
	}
	if (nbr == 0)
		size++;
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

char		*ft_zitoa(ssize_t nbr)
{
	char				*rep;
	int					i;
	int					size;
	ssize_t				temp;
	int					neg;

	neg = -1;
	size = ft_zsize(nbr);
	i = 0;
	if (!(rep = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	if (nbr < 0)
		rep[0] = '-';
	neg = (nbr < 0) ? 1 : 0;
	while (i < size - 1 - neg)
	{
		temp = nbr % 10;
		nbr /= 10;
		if (temp < 0)
			temp *= -1;
		rep[size - 2 - i] = temp + '0';
		i++;
	}
	return (rep);
}
