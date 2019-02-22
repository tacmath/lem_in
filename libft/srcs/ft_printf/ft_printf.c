/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 16:49:13 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 11:32:20 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <locale.h>
#include "ft_printf.h"
#include "libft.h"

int		ft_printf(const char *restrict format, ...)
{
	int		size;
	va_list args;

	va_start(args, format);
	size = ft_parser(format, &args, 1);
	va_end(args);
	return (size);
}

int		ft_vprintf(const char *restrict format, va_list ap)
{
	return (ft_parser(format, (va_list*)&ap, 1));
}

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	int		size;
	va_list args;

	va_start(args, format);
	size = ft_parser(format, &args, fd);
	va_end(args);
	return (size);
}

int		ft_vdprintf(int fd, const char *restrict format, va_list ap)
{
	return (ft_parser(format, (va_list*)&ap, fd));
}
