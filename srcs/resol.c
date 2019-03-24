/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:26:27 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 16:07:13 by lperron     ###    #+. /#+    ###.fr     */
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

int		resol(t_map *map)
{
	int i;
}
