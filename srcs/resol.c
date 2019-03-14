/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:26:27 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 15:24:55 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		put_moving_ant(t_map *map, int ant, int room)
{
	ft_putchar('L');
	ft_putnbr(ant + 1);
	ft_putchar('-');
	ft_putstr(map->room[room].name);
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
		i = -1;
		hype_max = -1;
		room = &(map->room[map->ant[ant]]);
		while (++i < room->nb_connection)
			if (room->connection[i].hype >
					hype_max && room->connection[i].ant == 0)
				best_room = i;
		put_moving_ant(map, ant, room->connection[best_room]);
		map->room[room->connection[best_room]].ant = 1;
		room->ant = 0;
		map->ant[ant] = room->connection[best_room];
	}
	ft_putchar('\n');
}
