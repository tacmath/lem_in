/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: exam <marvin@le-101.fr>                    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 19:17:27 by exam         #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 14:46:31 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int nbr)
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

char		*ft_itoa(int nbr)
{
	char	*rep;
	int		i;
	int		size;
	int		temp;
	int		neg;

	neg = -1;
	size = ft_size(nbr);
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
