/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_juitoa_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 16:55:22 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 14:14:40 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_jsize(uintmax_t nbr, int base)
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

char		*ft_juitoa_base(uintmax_t value, int base)
{
	char				*rep;
	int					i;
	int					size;
	uintmax_t			temp;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_jsize(value, base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	while (++i < size - 1)
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

static int	ft_zsize(size_t nbr, int base)
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

char		*ft_zuitoa_base(size_t value, int base)
{
	char					*rep;
	int						i;
	int						size;
	size_t					temp;

	if (base < 2 || base > 16)
		return (NULL);
	size = ft_zsize(value, base);
	i = -1;
	if (!(rep = ft_strnew(sizeof(char) * size)))
		return (NULL);
	while (++i < size - 1)
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
