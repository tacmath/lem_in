/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_replace.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 10:46:04 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 13:58:56 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_str_replace(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	free(s1);
	s1 = ft_strdup(s2);
	if (!s1)
		return (NULL);
	return (s1);
}
