/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 13:56:34 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 14:10:46 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		i;

	if (!(s1 && s2))
		return (NULL);
	if (!(out = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		out[i] = s1[i];
	--s2;
	while (*(++s2) != '\0')
	{
		out[i] = *s2;
		i++;
	}
	out[i] = '\0';
	return (out);
}
