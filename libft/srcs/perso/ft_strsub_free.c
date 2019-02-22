/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub_free.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/09 10:19:38 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 10:21:26 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start + (unsigned int)len > (unsigned int)ft_strlen(s))
	{
		free(s);
		return (NULL);
	}
	if (!(out = malloc(sizeof(char) * ((unsigned int)len + 1))))
	{
		free(s);
		return (NULL);
	}
	while (i < len)
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	free(s);
	return (out);
}
