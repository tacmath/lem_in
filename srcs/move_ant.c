/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 12:13:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 14:37:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	continue_path(t_map *map, int j, int *arrived)
{
	map->ant[j].i_path++;
	map->ant[j].room = map->path[map->ant[j].path][map->ant[j].i_path];
	if (map->ant[j].room == map->end)
		(*arrived)++;
	if (!map->correction)
		put_resol(map, j, map->ant[j].room);
}

int		how_long(t_map *map)
{
	int n;
	int m;
	int nb;

	nb = map->path_len[0] - 1;
	n = map->nb_ant;
	while (n > 0)
	{
		nb++;
		m = -1;
		while (++m < map->nb_path)
			if (map->path_len[m] <= nb)
				n--;
	}
	return (nb);
}

void	can_i_go(t_map *map, int *arrived, int ant)
{
	int m;
	int n;

	n = -1;
	m = 0;
	while (++n < ant && m < map->nb_path)
		if (map->ant[n].room == map->start)
		{
			if (how_long(map) >= map->path_len[m])
			{
				map->nb_ant--;
				map->ant[n].i_path = 0;
				map->ant[n].path = m;
				map->ant[n].room = map->path[m][0];
				if (!map->correction)
					put_resol(map, n, map->ant[n].room);
				if (map->ant[n].room == map->end)
				{
					map->ant[n].room = -1;
					(*arrived)++;
				}
			}
			m++;
		}
}

int		gogogo(t_map *map)
{
	int	ant;
	int	arrived;
	int count;
	int	j;

	ant = map->nb_ant;
	arrived = 0;
	count = 0;
	while (arrived != ant)
	{
		count++;
		j = -1;
		while (++j < ant)
			if (map->ant[j].room != map->end && map->ant[j].room != map->start)
				continue_path(map, j, &arrived);
		can_i_go(map, &arrived, ant);
		if (!map->correction)
			ft_putendl("");
	}
	if (map->correction)
		ft_printf("lines = %d\n", count);
	return (1);
}
