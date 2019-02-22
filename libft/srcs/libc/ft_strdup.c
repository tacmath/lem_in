/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 10:26:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 10:26:08 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int		i;
	char	*res;

	i = 0;
	res = 0;
	while (src[i] != '\0')
		i++;
	res = (char*)malloc((sizeof(*res) * (i + 1)));
	if (res)
	{
		i = 0;
		while (src[i] != '\0')
		{
			res[i] = src[i];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
