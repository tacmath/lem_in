/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 13:34:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/08 13:56:00 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static void	get_pipe_len(t_map *map)
{
	t_point	max;
	int		n;

	max.x = map->room[0].x;
	max.y = map->room[0].y;
	n = 0;
	while (++n < map->nb_room)
	{
		if (max.x < map->room[n].x)
			max.x = map->room[n].x;
		if (max.y < map->room[n].y)
			max.y = map->room[n].y;
	}
	map->pipe_len.x = (map->size.x - map->room_image.width - 50) / max.x;
	map->pipe_len.y = (map->size.y - map->room_image.height - 50) / max.y;
}

void		draw_all_room(t_map *map)
{
	int n;
	int x;
	int y;

	get_pipe_len(map);
	n = -1;
	while (++n < map->nb_room)
	{
		x = 25 + map->pipe_len.x * map->room[n].x;
		y = 25 + map->pipe_len.y * map->room[n].y;
		put_room_to_foreground(map, map->room_image, x, y);
	}
}

int			ft_struct_init(t_map *map)
{
	if (!(map->mlx_ptr = mlx_init()))
		return (0);
	if (!(get_all_images(map)))
		return (0);
	map->step = 0;
	map->total_step = 200;
	map->size.x = map->foreground.width;
	map->size.y = map->foreground.height;
	if (!get_info(map))
		return (0);
	if (!(map->win_ptr = mlx_new_window(map->mlx_ptr,
		map->size.x, map->size.y, "lem in")))
		return (0);
	return (1);
}
