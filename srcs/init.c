/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:24:10 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:04:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

uint64_t	**bin_init(int size)
{
	int			i;
	int			j;
	uint64_t	**bin;

	i = -1;
	size = (size >> 6) + 1;
	if (!(bin = (malloc(sizeof(uint64_t *) * 1000))))
		return (NULL);
	j = -1;
	while (++j < 1000)
	{
		if (!(bin[j] = (malloc(sizeof(uint64_t) * size))))
		{
			while (--j >= 0)
				free(bin[j]);
			ft_super_free(1, bin);
			return (NULL);
		}
		while (++i < size)
			bin[j][i] = 0xFFFFFFFFFFFFFFFF;
	}
	return (bin);
}

void		pre_init(t_map *map)
{
	map->ant = NULL;
	map->path = NULL;
	map->path_room = NULL;
	map->best_compa = NULL;
	map->tmp = NULL;
	map->room = NULL;
	map->path_len = NULL;
	map->ant_progress = NULL;
	map->path_compat.matrix = NULL;
	map->path_compat.matrixbin = NULL;
	map->path_compat.nb_compat = NULL;
}

int			rooms_init(t_map *map)
{
	int n;
	int	i;

	if (map->nb_room < 1)
	{
		map->ant = 0;
		return (0);
	}
	n = -1;
	while (++n < map->nb_room)
	{
		map->room[n].connection = 0;
		map->room[n].heat = -1;
		map->room[n].nb_connection = 0;
	}
	n = -1;
	i = -1;
	if (!(map->ant = malloc(sizeof(t_ant) * map->nb_ant)))
		return (0);
	while (++i < map->nb_ant)
	{
		map->ant[i].room = map->start;
		map->ant[i].path = -1;
	}
	return (1);
}

static int	ant_init(t_map *map, char ***output)
{
	char	*line;
	int		n;
	int		ret;

	ret = 0;
	if (get_next_line(0, &line) < 1)
		return (0);
	n = -1;
	while (line[++n])
		if (line[n] < '0' || line[n] > '9')
			ret = 1;
	map->nb_ant = ft_atoi(line);
	if (map->nb_ant <= 0 || ret)
	{
		free(line);
		return (0);
	}
	if (!(add_to_output(output, line)))
		return (0);
	return (1);
}

int			init_struct(t_map *map, char ***output)
{
	pre_init(map);
	if (!(*output = ft_memalloc(sizeof(char*))))
		return (0);
	if (!ant_init(map, output))
		return (0);
	if (!(map->ant_progress = malloc(sizeof(int) * map->nb_ant)))
		return (free_map(map));
	map->nb_path = 0;
	map->room = 0;
	map->correction = 0;
	map->start = -1;
	map->end = -1;
	return (1);
}
