/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 12:29:22 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 12:54:51 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*out;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	i = -1;
	if (!(out = malloc(sizeof(char) * size)))
		return (NULL);
	while (s[++i] != '\0')
		out[i] = f(s[i]);
	out[i] = '\0';
	return (out);
}
