/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ldbl_truncate.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 13:50:23 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 16:12:08 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

long double	ft_ldbl_truncate(long double nbr)
{
	long double bu;

	bu = nbr;
	if (nbr == 1.0)
		return (nbr);
	nbr = ((nbr) + 0x1p64) - 0x1p64;
	if (nbr < 0)
		nbr = nbr < bu ? nbr + 1 : nbr;
	else if (nbr > 0)
		nbr = nbr > bu ? nbr - 1 : nbr;
	return (nbr);
}
