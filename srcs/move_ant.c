/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 12:13:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 13:12:03 by mtaquet     ###    #+. /#+    ###.fr     */
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

int		how_long_will_it_be(t_map *map, int mpath, int antp, int *path)
{
	int	n;
	int	arr;
	int	bn;
	int incr;

	arr = 0;
	incr = 0;
	n = 0;
	while (arr < map->nb_ant + antp)
	{
		bn = n;
		n = incr <= mpath ? map->path_len[path[incr]] : n;
		if (incr <= mpath && (n - bn) * incr <= map->nb_ant + antp - arr)
		{
			arr += bn == 0 ? incr : (n - bn) * incr;
			while (incr <= mpath && map->path_len[path[incr]] == n && ++incr)
				arr++;
		}
		else
			while (arr < map->nb_ant + antp && ++n)
				arr += incr;
	}
	return (n);
}

int		how_long(t_map *map)
{
	int n;
	int m;
	int nb;

	nb = map->path_len[map->best_compa[0]];
	n = map->nb_ant;
	while (n > 0)
	{
		nb++;
		m = -1;
		while (map->best_compa[++m] != -1)
			if (map->path_len[map->best_compa[m]] <= nb)
				n--;
	}
	return (nb);
}
/*
** int		how_long_will_it_be(t_map *map, int min_path,
** int plusant, int	*path)
** {
**	int	count;
**	int	arrived;
**	int	i;
**	int incr;
**
**	count = map->path_len[path[0]] - 1;
**	arrived = 0;
**	incr = 0;
**	while (arrived < map->nb_ant + plusant)
**	{
**		count++;
**		i = incr - 1;
**		while (++i <= incr && i <= min_path)
**		{
**			if (count >= map->path_len[path[i]])
**				incr++;
**			else
**				break ;
**		}
**		arrived += ft_min(incr, min_path + 1);
**	}
**	return (count);
** }
*/

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

void	can_i_go(t_map *map, int *arrived, int ant)
{
	int	path;
	int m;
	int n;

	n = -1;
	m = 0;
	while (++n < ant && map->best_compa[m] != -1)
		if (map->ant[n].room == map->start)
		{
			path = map->best_compa[m];
			if (how_long(map) >= map->path_len[path])
			{
				map->nb_ant--;
				map->ant[n].i_path = 0;
				map->ant[n].path = path;
				map->ant[n].room = map->path[path][0];
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
			if (map->ant[j].room != map->end && map->ant[j].room != map->start)
				continue_path(map, j, &arrived);
		can_i_go(map, &arrived, ant);
		ft_putendl("");
	}
	map->nb_ant = ant;
	ft_printf("test = %d\n", how_long(map));
	ft_printf("count = %d\n", *count);
	return (1);
}
