/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uitoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 14:20:32 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 14:29:23 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_size(unsigned int nbr, unsigned int base)
{
	int size;

	size = 0;
	if (nbr == 0)
		size++;
	while (nbr != 0)
	{
		nbr /= base;
		size++;
	}
	return (++size);
}

char		*ft_uitoa_base(unsigned int value, int base)
{
	char			*rep;
	int				i;
	int				size;
	unsigned int	temp;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_size(value, (unsigned int)base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	rep[0] = '-';
	while (++i < size - 1)
	{
		temp = value % (unsigned int)base;
		value /= (unsigned int)base;
		if (temp < 10 && size - 2 - i >= 0)
			rep[size - 2 - i] = temp + '0';
		else if (size - 2 - i >= 0)
			rep[size - 2 - i] = temp - 10 + 'A';
	}
	return (rep);
}
