/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_ant.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 12:13:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/31 18:21:21 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_best_comp(t_map *map)
{
	int	i;
	int	j;
	int tmp;

	i = -1;
	while (map->best_compa[++i] != -1)
	{
		j = i;
		while (map->best_compa[++j] != -1)
		{
			if (map->path_len[map->best_compa[i]] > map->path_len[map->best_compa[j]])
			{
				tmp = map->best_compa[i];
				map->best_compa[i] = map->best_compa[j];
				map->best_compa[j] = tmp;
			}
		}
	}
	i = -1;
	while (map->best_compa[++i] != -1)
	ft_printf( _BLUE_ "%d\n" _EOC_ , map->path_len[map->best_compa[i]]);
}
/*
int		compute_speed(t_map *map, int nb_comp)
{
		
}

int		how_many_at_the_same_time(t_map *map)
{
	int	i;
	int	nb;
	int	best;
	int	test;

	i = 0;
	nb = 0;
	test = 0;
	best = map->path_len[map->best_comp[0]] + map->nb_ant - 1;
	sort_best_comp(map);
	while (map->best_comp[++nb] != -1)
		;
	while (++i < nb)
	{
		
	}
}*/
#include <unistd.h>
void	continue_path(t_map *map, int j, int *arrived)
{
	map->ant[j].i_path++;
	map->ant[j].room = map->path[map->ant[j].path][map->ant[j].i_path];
	if (map->ant[j].room == map->end)
	{
	//	ft_printf("arrived %d\n", j);
	//	if (j > 280)
	//	sleep(1);
		(*arrived)++;
	}
	put_resol(map, j, map->ant[j].room);
}


int		how_long_will_it_be(t_map *map, int min_path, int plusant) 
{
	int	count;
	int	arrived;
	int	i;
	int incr;

	count = 0;
	arrived = 0;
	incr = 0;
	while (arrived < map->nb_ant + plusant)
	{

		count++;
		i = incr - 1;
		while (++i <= incr && i <= min_path)
		{
			if (count >= map->path_len[map->best_compa[i]])
				incr++;
			else
				break;
		}
		arrived += ft_min(incr, min_path + 1);
	}
	return (count);
}


void	can_i_go(t_map *map, int j, int *arrived, int ant)
{
	int	min_path;
	int	i;
	int	ok;

	min_path = -1;
	while (map->best_compa[++min_path] != -1)
	{
		i = -1;
		ok = 1;
		while (++i < ant)
		{
			if(map->ant[i].room == map->path[map->best_compa[min_path]][0])
				ok = 0;
	//		ft_printf("ant %d room = %d, start = %d\n",i, map->ant[i].room, map->path[map->best_compa[min_path]][0]);
			if (!ok)
				break;
		}
		if (ok)
			break;
	}
//	ft_printf( _RED_ "path = %d\n" _EOC_ , min_path);
	if (map->best_compa[min_path] != -1)
	{
		if (min_path == 0 || (how_long_will_it_be(map, min_path - 1, min_path) > how_long_will_it_be(map, min_path, min_path)))
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
		//	ft_printf( _RED_ " pathlen = %d " _EOC_ , map->path_len[map->best_compa[min_path]]);
		}
	}
}


int		gogogo(t_map *map)
{
	int	ant;
	int	arrived;
	int	j;
	int count;

	count = 0;
	ant = map->nb_ant;
	arrived = 0;
	sort_best_comp(map);
//	if (init_ant(map) == 0)
//		return (0);

	while (arrived != ant)
	{
count++;
		j = -1;
		while (++j < ant)
		{
			if (map->ant[j].room == map->end)
				;
			else if (map->ant[j].room == map->start)
				can_i_go(map, j, &arrived, ant);
			else
				continue_path(map, j, &arrived);
		}
		ft_putendl("");
	//	sleep(10);
	}
	ft_printf("count = %d\n", count);
	return (1);
}
