/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 18:20:24 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 13:22:27 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			get_path(t_map *map, int room, int heat, int *path_len)
{
	int		n;
	int		co;
	int		ret;

	ret = 0;
	map->room[room].heat = heat;
	if (room == map->end)
	{
		free(map->tmp);
		if (!(map->tmp = malloc(sizeof(int) * (heat))))
			return (0);
		map->tmp[heat - 1] = map->end;
		*path_len = heat;
		return (1);
	}
	n = -1;
	while (++n < map->room[room].nb_connection &&
		(co = map->room[room].connection[n]) == map->room[room].connection[n])
		if (map->room[co].heat == -1 ||
				(map->room[co].heat > heat + 1 && map->room[co].heat != 1))
			if (get_path(map, co, heat + 1, path_len))
				ret++;
	if (ret > 0 && room != map->start && (map->tmp[heat - 1] = room) == room)
		return (1);
	return (0);
}

int			get_best_path(t_map *map, int m)
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
	return (!(ft_ssuper_free(3, &map->path_compat.matrix,
					&map->path_compat.matrixbin, &map->path_room)));
}

void		sort_pathe(t_map *map)
{
	int			tmp_len;
	int			n;
	int			m;
	int			*tmp;

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
			while (++m < map->path_len[n] - 1)
				map->room[map->path[n][m]].heat = 1;
		get_path(map, map->start, 0, &path_len);
		if (path_len < map->best_speed && path_len != -1)
		{
			map->path[map->nb_path] = map->tmp;
			map->path_len[map->nb_path++] = path_len;
			sort_pathe(map);
			map->best_speed = how_long(map);
		}
		else
			break ;
	}
	return (ft_ssuper_free(1, &map->tmp));
}

int			get_multiple_path(t_map *map)
{
	int n;
	int start_path;
	int start_of_rev;
	int	count;

	n = -1;
	map->nb_path = 0;
	res_heat(map);
	map->path = malloc(sizeof(int*) * 1000);
	map->path_len = malloc(sizeof(int) * 1000);
	start_path = map->nb_path;
	while (++n < map->room[map->start].nb_connection)
	{
		map->path[start_path + n] = malloc(sizeof(int));
		map->path[start_path + n][0] = map->room[map->start].connection[n];
		map->nb_path++;
		map->path_len[start_path + n] = 1;
		map->room[map->start].heat = 1;
		map->room[map->room[map->start].connection[n]].heat = 1;
	}
	get_all_path(map, start_path);
	start_of_rev = map->nb_path;
	n = -1;
	res_heat(map);
	map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*)
			* map->nb_path, sizeof(int*) * (map->nb_path + 1000));
	map->path_len = (int*)ft_realloc((void**)&(map->path_len), sizeof(int)
			* map->nb_path, sizeof(int) * (map->nb_path + 1000));
	start_path = map->nb_path;
	while (++n < map->room[map->end].nb_connection)
	{
		map->path[start_path + n] = malloc(sizeof(int));
		map->path[start_path + n][0] = map->room[map->end].connection[n];
		map->nb_path++;
		map->path_len[start_path + n] = 1;
		map->room[map->end].heat = 1;
		map->room[map->room[map->end].connection[n]].heat = 1;
	}
	get_all_path(map, start_path);
	n = start_of_rev - 1;
	while (++n < map->nb_path)
		rev_path(map, n);
	map->max_compa = ft_min(map->room[map->start].nb_connection,
			map->room[map->end].nb_connection);
	if (!get_usable_path(map, -1, 0))
		return (0);
	sort_path(map);
	if (!compatibility_all(map))
		return (0);
	resol(map);
	get_last_path(map);
	count = 0;
	gogogo(map, &count);
	return (1);
}
