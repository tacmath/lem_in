/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 11:15:15 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 17:19:01 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*out;
	size_t	i;

	i = 0;
	if (!(out = malloc(size)))
		return (NULL);
	while (i < size)
	{
		out[i] = '\0';
		i++;
	}
	return ((void *)out);
}
