/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 13:37:31 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 13:51:45 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	*add_room_to_path(int *path, int room, int len)
{
	int *new_path;
	int n;

	if (!(new_path = malloc(sizeof(int) * (len + 1))))
		return (0);
	n = -1;
	while (++n < len)
		new_path[n] = path[n];
	new_path[n] = room;
	return (new_path);
}

static int	split_path(t_map *map, int n, int m, int room)
{
	if (map->tmp == 0 && (map->tmp = map->path[n]))
	{
		if (!(map->path[n] = add_room_to_path(map->tmp,
						map->room[room].connection[m], map->path_len[n]++)))
			return (0);
	}
	else
	{
		if (map->nb_path % 1000 == 0 && (!(map->path =
						(int**)ft_realloc((void**)&(map->path),
							sizeof(int*) * map->nb_path, sizeof(int*) *
							(map->nb_path + 1000))) || !(map->path_len =
							(int*)ft_realloc((void**)&(map->path_len),
								sizeof(int) * map->nb_path, sizeof(int) *
								(map->nb_path + 1000)))))
			return (0);
		if (!(map->path[map->nb_path] = add_room_to_path(map->tmp,
						map->room[room].connection[m], map->path_len[n] - 1)))
			return (0);
		map->path_len[map->nb_path++] = map->path_len[n];
	}
	if (map->room[room].connection[m] != map->end &&
			map->room[room].connection[m] != map->start)
		map->room[map->room[room].connection[m]].heat = 1;
	return (1);
}

int			get_all_path(t_map *map, int start_path)
{
	int n;
	int m;
	int room;
	int ret;
	int nb_path;

	ret = 1;
	while (ret && !(ret = 0))
	{
		nb_path = map->nb_path;
		n = start_path - 1;
		while (++n < nb_path && !(map->tmp = 0))
			if ((room = map->path[n][map->path_len[n] - 1])
					!= map->end && room != map->start)
			{
				m = -1;
				while (++m < map->room[room].nb_connection)
					if (
map->room[map->room[room].connection[m]].heat == -1 && (++ret))
						if (!split_path(map, n, m, room))
							return (0);
				free(map->tmp);
			}
	}
	return (1);
}
