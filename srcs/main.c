/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:34:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/21 17:29:56 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		get_room(t_map *map)
{
	char	*line;
	int		room;

	room = 0;
	if (get_next_line(0, &line) < 1)
		return (0);
	while (ft_strchr(line, ' ') || ft_strchr(line, '#'))
	{
		if (ft_strcmp(line, "##start"))
		{
			ft_putendl(line);
			free(line);
			if (get_next_line(0, &line) < 1)
				return (0);
			map->start = ft_atoi(line);
		}
		if (ft_strcmp(line, "##end"))
		{
			ft_putendl(line);
			free(line);
			if (get_next_line(0, &line) < 1)
				return (0);
			map->end = ft_atoi(line);
		}
		room++;	
		ft_putendl(line);
		free(line);
		if (get_next_line(0, &line) < 1)
			return (0);
	}
	if (!(map->room = malloc(sizeof(t_room) * room)))
		return (0);

	return (1);
}

int		main(void)
{
	t_map	*map;
	char	*line;

	if (!(map = malloc(sizeof(t_map))))
		return (-1);
	if (get_next_line(0, &line) < 1)
		return (-1);
	map->nb_ant = ft_atoi(line);
	ft_putendl(line);
	free(line);
	if (!(map->ant = malloc(sizeof(int) * map->nb_ant)))
		return (-1);


	
	return (0);
}
