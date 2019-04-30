/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 04:34:44 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:26:59 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

int		deal_key(int key, t_map *map)
{
	if (key == KEY_ESCAPE)
	{
		ft_free_map(map, 0);
		exit(1);
	}
	return (1);
}

int		ft_destroy(t_map *map)
{
	ft_free_map(map, 0);
	exit(1);
	return (1);
}
