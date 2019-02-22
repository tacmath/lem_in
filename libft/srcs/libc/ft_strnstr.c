/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:32:52 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 09:00:36 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int i;
	int pos;

	i = 1;
	pos = -1;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[++pos] && pos < (int)len)
	{
		if (str[pos] == to_find[0])
		{
			while (str[pos + i] == to_find[i] &&
				to_find[i] && to_find != '\0' && i + pos < (int)len)
				i++;
			if (to_find[i] == '\0')
				return ((char *)&str[pos]);
			i = 1;
		}
	}
	return (0);
}
