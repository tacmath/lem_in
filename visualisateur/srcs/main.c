/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:23:16 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static int	get_room_id(t_map *map, char *line)
{
	int n;
	int m;

	n = -1;
	while (line[++n] != '-' && line[n] != '\0')
		;
	m = -1;
	while (++m < map->nb_room)
		if (!ft_strncmp(&(line[n + 1]), map->room[m].name,
				ft_strlen(map->room[m].name)))
			return (m);
	return (-1);
}

static int	get_ant_goal(t_map *map)
{
	char	*line;
	int		n;

	if (get_next_line(0, &line) < 1)
		return (0);
	n = -1;
	while (line[++n])
		if (line[n] == 'L' && (n == 0 || line[n - 1] == ' '))
			map->ant_goal[ft_atoi(&(line[n + 1])) - 1] =
				get_room_id(map, &(line[n]));
	free(line);
	return (1);
}

static int	ft_loop(t_map *map)
{
	int n;

	if (map->step == 0)
	{
		get_ant_goal(map);
		map->step++;
	}
	else
	{
		draw_info(map);
		draw_all_ant(map);
		map->step++;
		if (map->step == map->total_step)
		{
			n = -1;
			while (++n < map->nb_ant)
				if (map->ant_goal[n] != -1)
				{
					map->ant[n] = map->ant_goal[n];
					map->ant_goal[n] = -1;
				}
			map->step = 0;
		}
	}
	return (1);
}

static int	ft_get_path(t_map *map, char *name)
{
	int n;

	n = ft_strlen(name);
	while (name[--n] != '/')
		;
	if (!(map->path = ft_strsub(name, 0, n + 1)))
		return (0);
	return (1);
}

int			main(int ac, char **av)
{
	t_map *map;

	ac = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (0);
	if (!ft_get_path(map, av[0]))
		return (0);
	if (!(ft_struct_init(map)))
		return (0);
	mlx_loop_hook(map->mlx_ptr, ft_loop, map);
	mlx_hook(map->win_ptr, DESTROY_NOTIFY, 0, ft_destroy, map);
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_loop(map->mlx_ptr);
	return (1);
}
