/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_litoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 12:34:25 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 14:19:31 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_lsize(unsigned long int nbr, int base)
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

char		*ft_luitoa_base(unsigned long int value, int base)
{
	char				*rep;
	int					i;
	int					size;
	unsigned long int	temp;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_lsize(value, base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	while (++i < size - 1)
	{
		temp = value % base;
		value /= base;
		if ((temp = ft_abs(temp)) < 10 && size - 2 - i >= 0)
			rep[size - 2 - i] = temp + '0';
		else if (size - 2 - i >= 0)
			rep[size - 2 - i] = temp - 10 + 'A';
	}
	return (rep);
}

static int	ft_llsize(unsigned long long int nbr, int base)
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

char		*ft_lluitoa_base(unsigned long long int value, int base)
{
	char					*rep;
	int						i;
	int						size;
	unsigned long long int	temp;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_llsize(value, base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	while (++i < size - 1)
	{
		temp = value % base;
		value /= base;
		if ((temp = ft_abs(temp)) < 10 && size - 2 - i >= 0)
			rep[size - 2 - i] = temp + '0';
		else if (size - 2 - i >= 0)
			rep[size - 2 - i] = temp - 10 + 'A';
	}
	return (rep);
}
