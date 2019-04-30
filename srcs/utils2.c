/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 16:57:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:12:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int	add_ant_to_line(char **line, int ant, char *room_name, int *len)
{
	int		n;
	int		m;
	char	*ant_nb;
	char	*tmp;

	if (!(ant_nb = ft_itoa(ant + 1)) ||
			!(tmp = malloc(sizeof(int) * (*len + ft_strlen(ant_nb) + 4 +
						ft_strlen(room_name)))) || !(n = -1))
		return (ft_super_free(1, *line));
	while (++n < *len)
		tmp[n] = (*line)[n];
	tmp[n] = 'L';
	*len += ft_strlen(ant_nb) + 1;
	m = -1;
	while (++n < *len)
		tmp[n] = ant_nb[++m];
	tmp[n] = '-';
	*len += ft_strlen(room_name) + 1;
	m = -1;
	while (++n < *len)
		tmp[n] = room_name[++m];
	tmp[n] = ' ';
	tmp[n + 1] = '\0';
	*len = n + 1;
	return (!(ft_super_free(2, *line, ant_nb)) && (*line = tmp));
}

int	free_map(t_map *map)
{
	int n;

	if (!map)
		return (0);
	n = -1;
	while (++n < map->nb_room && map->room)
		ft_super_free(2, map->room[n].name, map->room[n].connection);
	n = -1;
	while (++n < map->nb_path)
	{
		if (map->path)
			free(map->path[n]);
		if (map->path_compat.matrix)
			free(map->path_compat.matrix[n]);
		if (map->path_compat.matrixbin)
			free(map->path_compat.matrixbin[n]);
		if (map->path_room)
			free(map->path_room[n]);
	}
	ft_super_free(12, map->path, map->path_compat.matrix, map->ant, map->room,
	map->path_compat.matrixbin, map->path_compat.nb_compat, map->best_compa,
	map->path_len, map->ant_progress, map->path_room, map->tmp, map);
	return (0);
}

int	get_error(t_map *map)
{
	if (map->nb_room == 0)
		return (0);
	if (map->start == -1 || map->end == -1)
		return (0);
	get_room_heat(map, map->end);
	if (map->room[map->start].heat == -1)
		return (0);
	return (1);
}
