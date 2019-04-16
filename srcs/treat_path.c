/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   treat_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:43:43 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 14:30:11 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	path_cmp(int *path1, int *path2, int path_len)
{
	int n;

	n = -1;
	while (++n < path_len)
		if (path1[n] != path2[n])
			return (0);
	return (1);
}

static int	init_one_path(t_map *map, int **tmp, int n, int *nb_path)
{
	int m;

	tmp[*nb_path] = map->path[n];
	map->tmp[*nb_path] = map->path_len[n];
	if (!(map->path_room[*nb_path] =
				ft_memalloc(sizeof(uint64_t) * ((map->nb_room >> 6) + 1))))
		return (0);
	m = -1;
	while (tmp[*nb_path][++m] != map->end)
		map->path_room[*nb_path][tmp[*nb_path][m] >> 6] |= 1ULL
			<< (tmp[*nb_path][m] % 64);
	(*nb_path)++;
	return (1);
}

static int	path_init(t_map *map, int **tmp, int n)
{
	int nb_path;
	int m;
	int mem;

	nb_path = 0;
	while (++n < map->nb_path)
		if (map->path[n][map->path_len[n] - 1] == map->end)
		{
			mem = 0;
			m = n;
			while (++m < map->nb_path)
				if (map->path_len[n] == map->path_len[m] &&
						path_cmp(map->path[n], map->path[m], map->path_len[n]))
					mem = 1;
			if (mem == 0)
			{
				if (!init_one_path(map, tmp, n, &nb_path))
					return (0);
			}
			else
				free(map->path[n]);
		}
		else
			free(map->path[n]);
	return (1);
}

int			get_usable_path(t_map *map, int n, int nb_path)
{
	int **tmp;
	int mem;
	int m;

	while (++n < map->nb_path)
		if (map->path[n][map->path_len[n] - 1] == map->end && !(mem = 0))
		{
			m = n;
			while (++m < map->nb_path)
				if (map->path_len[n] == map->path_len[m] &&
	path_cmp(map->path[n], map->path[m], map->path_len[n]))
					mem = 1;
			if (mem == 0)
				nb_path++;
		}
	if (!(map->tmp = malloc(sizeof(int) * nb_path)) ||
	!(map->path_room = malloc(sizeof(uint64_t*) * nb_path)) ||
	!(tmp = malloc(sizeof(int*) * nb_path)) || !path_init(map, tmp, -1))
		return (0);
	ft_super_free(2, map->path_len, map->path);
	map->path = tmp;
	map->path_len = map->tmp;
	map->nb_path = nb_path;
	return (1);
}

void		sort_path(t_map *map)
{
	int			tmp_len;
	uint64_t	*tmp_bin;
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
				tmp_bin = map->path_room[n + 1];
				map->path[n + 1] = map->path[n];
				map->path_len[n + 1] = map->path_len[n];
				map->path_room[n + 1] = map->path_room[n];
				map->path[n] = tmp;
				map->path_len[n] = tmp_len;
				map->path_room[n] = tmp_bin;
			}
	}
}
