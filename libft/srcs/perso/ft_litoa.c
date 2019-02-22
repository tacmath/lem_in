/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_litoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 11:55:32 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 12:00:45 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lsize(long int nbr)
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

char		*ft_litoa(long int nbr)
{
	char			*rep;
	int				i;
	int				size;
	long int		temp;
	int				neg;

	neg = -1;
	size = ft_lsize(nbr);
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

static int	ft_llsize(long long int nbr)
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

char		*ft_llitoa(long long int nbr)
{
	char				*rep;
	int					i;
	int					size;
	long long int		temp;
	int					neg;

	neg = -1;
	size = ft_llsize(nbr);
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
