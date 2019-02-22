/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 14:08:48 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 17:26:24 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*out;
	const char	*in;

	i = 0;
	in = (const char *)src;
	out = (char *)dst;
	if (src < dst)
	{
		while (i < n)
		{
			out[n - i - 1] = in[n - i - 1];
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			out[i] = in[i];
			i++;
		}
	}
	return ((void *)out);
}
