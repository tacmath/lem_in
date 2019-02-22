/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_mult.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 10:08:05 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/13 11:15:12 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

char	*ft_strjoin_mult(int n, ...)
{
	char	*out;
	char	*tmp;
	va_list	a;

	va_start(a, n);
	if (n < 1)
		return (NULL);
	if (!(out = ft_strdup("")))
		return (NULL);
	while (n--)
	{
		tmp = out;
		if (!(out = ft_strjoin(out, va_arg(a, char *))))
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	va_end(a);
	return (out);
}
