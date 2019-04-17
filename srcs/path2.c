/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:32:47 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 13:11:29 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			res_heat(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room)
		map->room[n].heat = -1;
	return (1);
}

void		rev_path(t_map *map, int nb_path)
{
	int n;
	int tmp;

	if (map->path[nb_path][map->path_len[nb_path] - 1] == map->start)
	{
		map->path[nb_path][map->path_len[nb_path] - 1] = map->end;
		n = -1;
		while (++n < (map->path_len[nb_path] - 1) / 2)
		{
			tmp = map->path[nb_path][n];
			map->path[nb_path][n] =
				map->path[nb_path][map->path_len[nb_path] - n - 2];
			map->path[nb_path][map->path_len[nb_path] - n - 2] = tmp;
		}
		map->path[nb_path][map->path_len[nb_path] - 1] = map->end;
	}
}
