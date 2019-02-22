/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dtoat.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 12:26:09 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/23 16:25:29 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static int	ft_size(double nbr)
{
	int size;

	size = 1;
	if (nbr < 0)
	{
		size++;
	}
	if (nbr < 0.1 && nbr > -0.1)
		size++;
	while (nbr >= 1 || nbr <= -1)
	{
		nbr /= 10.;
		size++;
	}
	return (size);
}

char		*ft_dtoat(double nbr)
{
	char	*rep;
	int		i;
	int		size;
	int		temp;
	int		neg;

	nbr = ft_dbl_truncate(nbr);
	size = ft_size(nbr);
	i = 0;
	if (!(rep = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	if (nbr < 0)
		rep[0] = '-';
	neg = (nbr < 0) ? 1 : 0;
	while (i < size - 1 - neg)
	{
		temp = (int)(nbr - (ft_dbl_truncate(nbr / 10.) * 10.));
		nbr /= 10.;
		temp = temp < 0 ? temp * -1 : temp;
		temp = temp > 9 ? 0 : temp;
		rep[size - 2 - i] = temp + '0';
		i++;
	}
	return (rep);
}
