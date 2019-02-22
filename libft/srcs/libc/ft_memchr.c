/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 14:38:56 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 17:08:14 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*in;
	size_t					i;

	i = 0;
	in = (const unsigned char *)s;
	while (i < n)
	{
		if (*(in + i) == (unsigned char)c)
			return ((void *)(in + i));
		i++;
	}
	return (NULL);
}
