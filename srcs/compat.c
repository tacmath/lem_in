/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compat.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 13:30:43 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 17:16:55 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

char		compatibility_one(uint64_t *rooms1, uint64_t *rooms2, int size)
{
	int	i;
	int res;

	res = 0;
	i = -1;
	while (++i <= size)
		if(rooms1[i] & rooms2[i])
			return (0);
	return (1);
}

int			compatibility_all(t_map *map)
{
	int		i;
	int		j;

	if (!(map->matrix = malloc(sizeof(char *) * map->nb_path)))
		return (0);
	i = -1;
	while (++i < map->nb_path)
		if(!(map->matrix[i] = ft_memalloc(sizeof(char) * map->nb_path)))
			return (0);
	i = -1;
	while (++i < map->nb_path)
	{
		j = i;
		while (++j < map->nb_path)
		{
			map->matrix[i][j] = compatibility_one(map->path_room[i],
					map->path_room[j], map->nb_room >> 6);
			map->matrix[j][i] = map->matrix[i][j];
		}
	}
	return (1);
}
