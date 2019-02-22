/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dbl_truncate.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 15:44:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/23 15:50:23 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

double	ft_dbl_truncate(double nbr)
{
	double bu;

	bu = nbr;
	nbr = ((nbr) + 0x1p52) - 0x1p52;
	if (nbr < 0)
		nbr = nbr < bu ? nbr + 1. : nbr;
	else if (nbr > 0)
		nbr = nbr > bu ? nbr - 1. : nbr;
	return (nbr);
}
