/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 10:18:37 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 10:47:26 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void **in, size_t old_size, size_t new_size)
{
	unsigned char	*new;
	unsigned char	*old;
	size_t			i;

	old = (unsigned char *)(*in);
	if (!(in && *in))
		return (NULL);
	if (!(new = malloc(new_size)))
	{
		free(*in);
		*in = NULL;
		return (NULL);
	}
	i = 0;
	while (i < old_size && i < new_size)
	{
		new[i] = old[i];
		i++;
	}
	free(*in);
	*in = (void *)new;
	return (*in);
}
