/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/03 13:32:22 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/03 14:03:38 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_size(int nbr, int base)
{
	int size;

	size = 0;
	if (nbr < 0 && base == 10)
		size++;
	if (nbr == 0)
		size++;
	while (nbr != 0)
	{
		nbr /= base;
		size++;
	}
	return (++size);
}

char		*ft_itoa_base(int value, int base)
{
	char	*rep;
	int		i;
	int		size;
	int		temp;
	int		neg;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_size(value, base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	rep[0] = '-';
	neg = (value < 0 && base == 10) ? 1 : -1;
	while (++i < size - 1 - neg)
	{
		temp = value % base;
		value /= base;
		if ((temp = ft_abs(temp)) < 10)
			rep[size - 2 - i] = temp + '0';
		else
			rep[size - 2 - i] = temp - 10 + 'A';
	}
	return (rep);
}
