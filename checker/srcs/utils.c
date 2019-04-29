/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:21:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 13:51:33 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "checker.h"

int			isroom(char *str)
{
	int n;

	if (str[0] == 'L' && str[0] == ' ')
		return (0);
	n = -1;
	while (str[++n] != ' ')
		if (str[n] == '\0')
			return (0);
	while (str[++n] != ' ')
		if (str[n] < '0' || str[n] > '9')
			return (0);
	while (str[++n])
		if (str[n] < '0' || str[n] > '9')
			return (0);
	return (1);
}

int			free_map(t_map *map)
{
	int n;

	n = -1;
	while (++n < map->nb_room && map->room)
	{
		free(map->room[n].name);
		free(map->room[n].connection);
	}
	n = -1;
	ft_super_free(3, map->ant, map->room, map);
	return (0);
}
