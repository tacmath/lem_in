/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 13:24:59 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 10:13:41 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*out;
	const char	*in;

	i = 0;
	in = (const char *)src;
	out = (char *)dst;
	while (i < n)
	{
		out[i] = in[i];
		i++;
	}
	return (dst);
}
