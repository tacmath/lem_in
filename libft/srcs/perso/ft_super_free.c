/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_super_free.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/13 11:02:04 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 17:51:05 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

int		ft_super_free(int n, ...)
{
	va_list a;

	va_start(a, n);
	while (n--)
	{
		free((void *)va_arg(a, char *));
	}
	va_end(a);
	return (0);
}

int		ft_ssuper_free(int n, ...)
{
	va_list a;

	va_start(a, n);
	while (n--)
	{
		ft_memdel((void**)va_arg(a, char**));
	}
	va_end(a);
	return (0);
}
