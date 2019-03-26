/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compat.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 13:30:43 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 17:23:05 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

char		compatibility_one(uint64_t *rooms1, uint64_t *rooms2, int size)
{
	int	i;

	i = -1;
	while (++i <= size)
		if(rooms1[i] & rooms2[i])
			return (0);
	return (1);
}

int			nb_path_compat(t_map *map)
{
	int		i;
	int		j;

	i = -1;
	
	if (!(map->path_compat.nb_compat = ft_memalloc(sizeof(int) * map->nb_path)))
		return (0);
	while (++i < map->nb_path)
	{
		j = -1;
		while (++j < map->nb_path)
			if (map->path_compat.matrix[j][i])
				map->path_compat.nb_compat[i]++;
	}
	return (1);
}

int			binarize(t_map *map)
{
	int		size;
	int		i;
	int		j;

	size = (map->nb_path >> 6) + 1;
	if (!(map->path_compat.matrixbin = malloc(sizeof(uint64_t *) * map->nb_path)))
		return (0);
	i = -1;
	while (++i < map->nb_path)
	{
		if (!(map->path_compat.matrixbin[i] = ft_memalloc(sizeof(uint64_t) * size))) //need to free
			return (0);
		j = -1;
		while (++j < map->nb_path)
		{
		//	ft_printf( _BLUE_ "%d " _EOC_, 1 << (j % 64));
			if (map->path_compat.matrix[i][j] == 1)
				map->path_compat.matrixbin[i][j >> 6] =  1 << (j % 64);
		}
		ft_printf("\n");
	}
	return (1);
}

int			compatibility_all(t_map *map)
{
	int		i;
	int		j;

	if (!(map->path_compat.matrix = malloc(sizeof(char *) * map->nb_path)))
		return (0);
	i = -1;
	while (++i < map->nb_path)
		if(!(map->path_compat.matrix[i] =
					ft_memalloc(sizeof(char) * map->nb_path)))
			return (0);
	i = -1;
	while (++i < map->nb_path)
	{
		j = i;
		while (++j < map->nb_path)
		{
			if (map->path[i][0] != map->path[j][0])
			{
				map->path_compat.matrix[i][j] = 
	compatibility_one(map->path_room[i],map->path_room[j], map->nb_room >> 6);
			map->path_compat.matrix[j][i] = map->path_compat.matrix[i][j];
			}
		}
	}
	if (!(binarize(map)))
		return (-1);
	return (nb_path_compat(map));
}
