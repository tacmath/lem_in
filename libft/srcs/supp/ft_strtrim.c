/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 14:16:14 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 17:16:23 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		beg;
	int		end;
	char	*out;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	beg = 0;
	size = ft_strlen(s);
	while (s[beg] == ' ' || s[beg] == '\t' || s[beg] == '\n')
		beg++;
	beg--;
	end = size - 1;
	while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
		end--;
	end++;
	size = (end != 0) ? end - beg : 1;
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	i = -1;
	while (++beg < end)
		out[++i] = s[beg];
	out[++i] = '\0';
	return (out);
}
