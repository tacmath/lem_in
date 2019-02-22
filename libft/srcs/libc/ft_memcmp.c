/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 14:54:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 16:24:13 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*in1;
	const unsigned char	*in2;
	size_t				i;

	i = 0;
	in1 = (const unsigned char *)s1;
	in2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (in1[i] == in2[i] && i < n - 1)
		i++;
	return ((int)(in1[i] - in2[i]));
}
