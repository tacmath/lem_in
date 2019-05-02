/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 18:20:24 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 16:14:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	rev_path(t_map *map, int nb_path)
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

static int	get_path_fetos(t_map *map)
{
	int start_of_rev;
	int n;

	start_of_rev = map->nb_path;
	n = -1;
	res_heat(map);
	if (!(map->path = (int**)ft_realloc((void**)&(map->path), sizeof(int*) *
		map->nb_path, sizeof(int*) * (map->nb_path + 1000))) ||
		!(map->path_len = (int*)ft_realloc((void**)&(map->path_len),
		sizeof(int) * map->nb_path, sizeof(int) * (map->nb_path + 1000))))
		return (0);
	while (++n < map->room[map->end].nb_connection)
	{
		map->path[map->nb_path] = malloc(sizeof(int));
		map->path[map->nb_path][0] = map->room[map->end].connection[n];
		map->path_len[map->nb_path++] = 1;
		map->room[map->end].heat = 1;
		if (map->room[map->end].connection[n] != map->start)
			map->room[map->room[map->end].connection[n]].heat = 1;
	}
	if (!get_all_path(map, map->nb_path - n) && (n = start_of_rev - 1))
		return (0);
	while (++n < map->nb_path)
		rev_path(map, n);
	return (1);
}

int			get_multiple_path(t_map *map)
{
	int n;

	n = -1;
	res_heat(map);
	if (!(map->path = malloc(sizeof(int*) * 1000)) ||
			!(map->path_len = malloc(sizeof(int) * 1000)))
		return (0);
	while (++n < map->room[map->start].nb_connection)
	{
		map->path[map->nb_path] = malloc(sizeof(int));
		map->path[map->nb_path][0] = map->room[map->start].connection[n];
		map->path_len[map->nb_path++] = 1;
		map->room[map->start].heat = 1;
		if (map->room[map->start].connection[n] != map->end)
			map->room[map->room[map->start].connection[n]].heat = 1;
	}
	if (!get_all_path(map, map->nb_path - n) || !get_path_fetos(map))
		return (0);
	map->max_compa = ft_min(map->room[map->start].nb_connection,
			map->room[map->end].nb_connection);
	if (!get_usable_path(map, -1, 0))
		return (0);
	sort_path(map);
	return (!compatibility_all(map) ||
			!resol(map) || !get_last_path(map) ? 0 : 1);
}
