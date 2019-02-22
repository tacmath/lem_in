/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 13:16:05 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 13:55:43 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start + (unsigned int)len > (unsigned int)ft_strlen(s))
		return (NULL);
	if (!(out = malloc(sizeof(char) * ((unsigned int)len + 1))))
		return (NULL);
	while (i < len)
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}
