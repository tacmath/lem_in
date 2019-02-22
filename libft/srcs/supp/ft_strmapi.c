/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 13:00:27 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 15:17:07 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*out;
	int		size;
	int		i;

	if (!(s && f))
		return (NULL);
	size = ft_strlen(s) + 1;
	i = -1;
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	while (s[++i] != '\0')
		out[i] = f((unsigned int)i, s[i]);
	out[i] = '\0';
	return (out);
}
