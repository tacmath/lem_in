/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 16:30:25 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 15:20:31 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*in1;
	unsigned char	*in2;

	i = 0;
	in1 = (unsigned char *)s1;
	in2 = (unsigned char *)s2;
	in1--;
	in2--;
	if (n == 0)
		return (0);
	while ((*(++in1) == *(++in2) &&
				(*in1 != '\0' || *in2 != '\0')) && i < n - 1)
		i++;
	return (*(in1) - *(in2));
}
