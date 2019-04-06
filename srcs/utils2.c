/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 16:57:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 18:02:04 by lperron     ###    #+. /#+    ###.fr     */
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

void		free_map(t_map *map)
{
	int n;

	n = -1;
	free(map->ant);
	while (++n < map->nb_room)
	{
		free(map->room[n].name);
		free(map->room[n].connection);
	}
	n = -1;
	while (++n < map->nb_path)
		ft_super_free(4, map->path[n], map->path_compat.matrix[n],
				map->path_compat.matrixbin[n], map->path_room[n]);
	ft_super_free(3, map->path, map->path_compat.matrix,
		map->path_compat.matrixbin);
	free(map->path_compat.nb_compat);
	free(map->best_compa);
	free(map->path_len);
	free(map->ant_progress);
	free(map->room);
	free(map->path_room);
	free(map);
}

void		sort_best_comp(t_map *map)
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
			if (map->path_len[map->best_compa[i]] >
					map->path_len[map->best_compa[j]])
			{
				tmp = map->best_compa[i];
				map->best_compa[i] = map->best_compa[j];
				map->best_compa[j] = tmp;
			}
		}
	}
	i = -1;
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
