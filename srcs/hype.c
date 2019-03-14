/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hype.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:41:02 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 15:30:02 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	kylie_jenner(t_map *map)
{
	int	i;
	int	n;
	int	j;

	i = -1;
	while (++i < map->nb_ant)
	{
		n = map->room[map->ant[i]].nb_connection;
		j = -1;
		while (++j < n)
			map->room[map->room[map->ant[i]].connection[j]].hype += 1;
	}
	i = -1;
	while (++i < map->nb_room)
		if (i != map->end)
			map->room[i].hype /= map->room[i].heat;
}
