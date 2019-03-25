/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:26:27 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 13:49:51 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"
/*
void		put_resol(t_map *map, int ant, int room)
{
	ft_putchar('L');
	ft_putnbr(ant + 1);
	ft_putchar('-');
	ft_putstr(map->room[room].name);
	ft_putchar(' ');
}




void	move_ant(t_map	*map)
{
	int		hype_max;
	int		best_room;
	int		i;
	t_room	*room;
	int		ant;

	ant = -1;
	while (++ant < map->nb_ant)
	{
		if (map->ant[ant] != map->end)
		{
		i = -1;
		hype_max = 99999999;
		best_room = -1;
		room = &(map->room[map->ant[ant]]);
//		hype_max = map->room[room->connection[0]].hype + 1;
		while (++i < room->nb_connection)
		{
		//	ft_printf("???????%d\n",i);
			if (map->room[room->connection[i]].hype <
					hype_max && map->room[room->connection[i]].ant == 0 && room->connection[i] != map->last_room[ant])
			{
				best_room = i;
				hype_max = map->room[room->connection[best_room]].hype;
	//			ft_printf("Best room = %s\n", map->room[room->connection[best_room]].name);
			}
	//		ft_printf("%s : %f\n", map->room[room->connection[best_room]].name, map->room[room->connection[best_room]].hype);
	//
		}
		if (best_room != -1)
		{
			put_moving_ant(map, ant, room->connection[best_room]);
			if (room->connection[best_room] != map->end)
				map->room[room->connection[best_room]].ant = 1;
			room->ant = 0;
			map->last_room[ant] = map->ant[ant];
			map->ant[ant] = room->connection[best_room];
		}
	}
	}
	ft_putchar('\n');
}*/

void	push_test_compa(int	*test_compa, int room, int size)
{
	int		i;

	i = -1;
	while (test_compa[i] != -1 && i < size)
		;
	test_compa[i] = room;
}

int		fucking_recursive(t_map *map, int **test_compa, int size, int j)
{
	int		i;
	int		*best;
	int		ok;

	i = -1;
	if (*test_compa = NULL)
	{
		if (!(*test_compa = malloc(sizeof(int) * size)))
			return (-1);
		while (++i < size)
			*test[i] = -1;
	}
	while (++j < map->nb_room) // we add a room in the path and recur !!!!!!
	{
		i = -1;
		ok = 1;
		while(++i < size)
			if (test_compa[i] != -1 && map->path_compat[test_compat[i]][j] == 0)
				ok = 0;
		if (ok)
		{
			push_test_compa(*
		}
	}
}

int		resol(t_map *map)
{
	int		i;
	int		test_flow;
	int		*test_compa;

	i = 1;
	map->best_flow = 0;
	map->best_compa = NULL;
	while (++i < map->nb_ant)
	{
		test_compa = NULL;
		if (((test_flow = fucking_recursive(map, &test_compa, i, -1)) < 0))
			return (0);
		if (map->best_flow > test_flow) //in the recursive, if we can't find a new path, we need to set test_flow to 0;
		{
			free (test_compa);
			break;
		}
		map->best_flow = test_flow;
		if (map->best_compa)
			free(map->best_compa);
		map->best_compa = test_compa;
	}
	return (1);
}
