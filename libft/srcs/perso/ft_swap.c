/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_swap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 10:32:04 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 10:33:29 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	unsigned char	*tmpa;
	unsigned char	*tmpb;
	size_t			i;

	i = 0;
	if (a == b)
		return ;
	tmpa = (unsigned char *)a;
	tmpb = (unsigned char *)b;
	while (i < size)
	{
		tmpa[i] = tmpa[i] ^ tmpb[i];
		tmpb[i] = tmpb[i] ^ tmpa[i];
		tmpa[i] = tmpa[i] ^ tmpb[i];
		i++;
	}
}
