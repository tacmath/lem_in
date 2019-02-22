/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ldbl_get_deci.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 13:54:10 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 14:17:03 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

long double			ft_ldbl_get_deci(long double nbr)
{
	return ((nbr - (ft_ldbl_truncate(nbr))));
}
