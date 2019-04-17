/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 16:57:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 13:51:57 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void		put_resol(t_map *map, int ant, int room)
{
	ft_putchar('L');
	ft_putnbr(ant + 1);
	ft_putchar('-');
	ft_putstr(map->room[room].name);
	ft_putchar(' ');
}

int			free_map(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room && map->room)
	{
		free(map->room[n].name);
		free(map->room[n].connection);
	}
	n = -1;
	while (++n < map->nb_path)
	{
		if (map->path)
			free(map->path[n]);
		if (map->path_compat.matrix)
			free(map->path_compat.matrix[n]);
		if (map->path_compat.matrixbin)
			free(map->path_compat.matrixbin[n]);
		if (map->path_room)
			free(map->path_room[n]);
	}
	ft_super_free(11, map->path, map->path_compat.matrix,
map->path_compat.matrixbin, map->path_compat.nb_compat, map->best_compa,
map->path_len, map->ant_progress, map->ant, map->room, map->path_room, map);
	return (0);
}

int			get_error(t_map *map)
{
	if (map->nb_room == 0)
	{
		free(map->ant);
		free(map);
		ft_putendl("ERROR");
		return (0);
	}
	else if (map->start == -1 || map->end == -1)
	{
		free_map(map);
		ft_putendl("ERROR");
		return (0);
	}
	get_room_heat(map, map->end, 0);
	if (map->room[map->start].heat == -1)
	{
		free_map(map);
		ft_putendl("ERROR");
		return (0);
	}
	return (1);
}
