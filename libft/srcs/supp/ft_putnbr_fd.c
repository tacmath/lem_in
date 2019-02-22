/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 15:14:10 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 15:14:13 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int a;
	int b;
	int neg;

	neg = 0;
	a = nb;
	if (nb == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			b = a % (10);
			a = a / (-10);
			neg = 1;
		}
		if (a >= 10)
			ft_putnbr_fd(a / 10, fd);
		if (a != 0)
			ft_putchar_fd(a % 10 + 48, fd);
		if (neg == 1)
			ft_putchar_fd(b * -1 + 48, fd);
	}
}
