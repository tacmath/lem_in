/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uitoa_basem.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 12:52:05 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 13:03:39 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_uitoa_basem(unsigned int nbr, int base)
{
	char *s;

	s = ft_uitoa_base(nbr, base);
	if (!s)
		return (NULL);
	s = ft_strtolower(s);
	return (s);
}

char	*ft_luitoa_basem(unsigned long int nbr, int base)
{
	char *s;

	s = ft_luitoa_base(nbr, base);
	if (!s)
		return (NULL);
	s = ft_strtolower(s);
	return (s);
}

char	*ft_lluitoa_basem(unsigned long long int nbr, int base)
{
	char *s;

	s = ft_lluitoa_base(nbr, base);
	if (!s)
		return (NULL);
	s = ft_strtolower(s);
	return (s);
}
