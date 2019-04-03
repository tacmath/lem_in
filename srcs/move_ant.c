/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 12:13:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/01 15:01:47 by lperron     ###    #+. /#+    ###.fr     */
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
	put_resol(map, j, map->ant[j].room);
}

int		how_long_will_it_be(t_map *map, int min_path, int plusant, int	*path)
{
	int	count;
	int	arrived;
	int	i;
	int incr;

	count = map->path_len[path[0]] - 1;
	arrived = 0;
	incr = 0;
	while (arrived < map->nb_ant + plusant)
	{
		count++;
		i = incr - 1;
		while (++i <= incr && i <= min_path)
		{
			if (count >= map->path_len[path[i]])
				incr++;
			else
				break ;
		}
		arrived += ft_min(incr, min_path + 1);
	}
	return (count);
}

int		get_min_path(t_map *map, int ant)
{
	int ok;
	int min_path;
	int	i;

	min_path = -1;
	ok = 0;
	while (!ok && map->best_compa[++min_path] != -1)
	{
		i = -1;
		ok = 1;
		while (++i < ant)
		{
			if (map->ant[i].room == map->path[map->best_compa[min_path]][0])
				ok = 0;
			if (!ok)
				break ;
		}
	}
	return (min_path);
}

void	can_i_go(t_map *map, int j, int *arrived, int ant)
{
	int	min_path;

	min_path = get_min_path(map, ant);
	if (map->best_compa[min_path] != -1)
	{
		if (min_path == 0 || (how_long_will_it_be(map, min_path - 1, min_path,
		map->best_compa) > how_long_will_it_be(map,
		min_path, min_path, map->best_compa)))
		{
			map->nb_ant--;
			map->ant[j].i_path = 0;
			map->ant[j].path = map->best_compa[min_path];
			map->ant[j].room = map->path[map->best_compa[min_path]][0];
			put_resol(map, j, map->ant[j].room);
			if (map->ant[j].room == map->end)
			{
				map->ant[j].room = -1;
				(*arrived)++;
			}
		}
	}
}

int		gogogo(t_map *map, int *count)
{
	int	ant;
	int	arrived;
	int	j;

	ant = map->nb_ant;
	arrived = 0;
	sort_best_comp(map);
	while (arrived != ant)
	{
		(*count)++;
		j = -1;
		while (++j < ant)
		{
			if (map->ant[j].room == map->end || (j != 0 &&
						map->ant[j - 1].room == map->start))
				;
			else if (map->ant[j].room == map->start)
				can_i_go(map, j, &arrived, ant);
			else
				continue_path(map, j, &arrived);
		}
		ft_putendl("");
	}
	ft_printf("count = %d\n", *count);
	return (1);
}