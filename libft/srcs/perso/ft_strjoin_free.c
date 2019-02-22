/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/18 13:12:12 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 14:20:11 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*cleaner(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

char		*ft_strjoin_free(char *s1, char *s2)
{
	char	*out;
	int		i;
	char	*tmp;

	tmp = s2;
	if (!(s1 && s2))
		return (cleaner(s1, s2));
	if (!(out = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (cleaner(s1, s2));
	i = -1;
	while (s1[++i] != '\0')
		out[i] = s1[i];
	--s2;
	while (*(++s2) != '\0' && ++i)
		out[i - 1] = *s2;
	out[i] = '\0';
	free((void*)s1);
	free((void*)tmp);
	return (out);
}
