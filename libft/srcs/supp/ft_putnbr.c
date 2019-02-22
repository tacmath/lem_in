/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/06 09:53:04 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 15:09:08 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	int a;
	int b;
	int neg;

	neg = 0;
	a = nb;
	if (nb == 0)
		ft_putchar('0');
	else
	{
		if (nb < 0)
		{
			ft_putchar('-');
			b = a % (10);
			a = a / (-10);
			neg = 1;
		}
		if (a >= 10)
			ft_putnbr(a / 10);
		if (a != 0)
			ft_putchar(a % 10 + 48);
		if (neg == 1)
			ft_putchar(b * -1 + 48);
	}
}
