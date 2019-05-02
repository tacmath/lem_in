/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:32:47 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 16:15:49 by mtaquet     ###    #+. /#+    ###.fr     */
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

static int	get_path(t_map *map, int room, int heat, int *path_len)
{
	int n;
	int co;
	int ret;

	ret = 0;
	map->room[room].heat = heat;
	if ((n = -1) && room == map->end && !(ft_ssuper_free(1, &map->tmp)))
	{
		if (!(map->tmp = malloc(sizeof(int) * (heat))))
			return (-1);
		*path_len = heat;
		map->tmp[heat - 1] = map->end;
		return (1);
	}
	while (++n < map->room[room].nb_connection &&
	(co = map->room[room].connection[n]) == map->room[room].connection[n])
		if ((map->room[co].heat == -1 || (map->room[co].heat > heat + 1 &&
				map->room[co].heat != 1)) && !(co == map->end && heat == 0))
			if (!(co = get_path(map, co, heat + 1, path_len) == 1 && ++ret)
					&& co == -1)
				return (-1);
	return ((ret > 0 && room != map->start &&
				(map->tmp[heat - 1] = room) == room) ? 1 : 0);
}

static int	get_best_path(t_map *map, int m)
{
	int **tmp;
	int *tmp_len;
	int n;

	if (!(tmp = ft_memalloc(sizeof(int*) * map->max_compa)) ||
			!(tmp_len = ft_memalloc(sizeof(int) * map->max_compa)))
		return (0);
	n = -1;
	while (++n < map->nb_path)
		if (n == map->best_compa[m] && map->best_compa[m] != -1)
		{
			tmp[m] = map->path[n];
			tmp_len[m++] = map->path_len[n];
			ft_super_free(3, map->path_compat.matrix[n],
					map->path_compat.matrixbin[n], map->path_room[n]);
		}
		else
			ft_super_free(4, map->path_compat.matrix[n],
			map->path_compat.matrixbin[n], map->path_room[n], map->path[n]);
	ft_super_free(2, map->path, map->path_len);
	map->path = tmp;
	map->path_len = tmp_len;
	map->nb_path = m;
	return (!ft_ssuper_free(3, &map->path_compat.matrix,
				&map->path_compat.matrixbin, &map->path_room));
}

static void	sort_pathe(t_map *map)
{
	int tmp_len;
	int n;
	int m;
	int *tmp;

	m = -1;
	while (++m < map->nb_path)
	{
		n = -1;
		while (++n < map->nb_path - 1)
			if (map->path_len[n] > map->path_len[n + 1])
			{
				tmp_len = map->path_len[n + 1];
				tmp = map->path[n + 1];
				map->path[n + 1] = map->path[n];
				map->path_len[n + 1] = map->path_len[n];
				map->path[n] = tmp;
				map->path_len[n] = tmp_len;
			}
	}
}

int			get_last_path(t_map *map)
{
	int n;
	int m;
	int path_len;

	get_best_path(map, 0);
	while (!(map->tmp = 0) && res_heat(map))
	{
		path_len = -1;
		n = -1;
		while (++n < map->nb_path && (m = -1) < 0)
			while (map->path[n][0] != map->end && ++m < map->path_len[n] - 1)
				map->room[map->path[n][m]].heat = 1;
		if (get_path(map, map->start, 0, &path_len) == -1)
			return (0);
		if (path_len < map->best_speed && path_len > 1)
		{
			map->path[map->nb_path] = map->tmp;
			map->path_len[map->nb_path++] = path_len;
			sort_pathe(map);
			map->best_speed = how_long(map);
		}
		else
			break ;
	}
	return (!ft_ssuper_free(1, &map->tmp));
}
