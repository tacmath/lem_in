/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_add.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/01 10:04:11 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/10 11:06:08 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

int		flagadd(t_fnct *fnct, va_list *a, int fd)
{
	int		id;
	t_fnct	f;
	int		size;

	id = va_arg(*a, int);
	f = va_arg(*a, t_fnct);
	if (id <= 0 || id > 127 || ft_ischarset(id, "0123456789.+- lLhH#w@!zj*"))
	{
		return (write(fd, "Invalid Identifier", 18));
	}
	else
	{
		fnct[id] = f;
		size = write(fd, "New Function Added With Identifier ", 35);
		size = size == -1 ? -1 : size + write(fd, &id, 1);
		return (size);
	}
}
