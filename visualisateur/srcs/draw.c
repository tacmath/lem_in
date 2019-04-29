/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:18:55 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/08 14:22:47 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static void	draw_horizontal_ant(t_map *map, t_point coord, t_point dif)
{
	if (dif.y >= 0)
	{
		if (map->step % 10 >= 5)
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
				map->ant_up1.ptr, coord.x, coord.y);
		else
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
				map->ant_up2.ptr, coord.x, coord.y);
	}
	else
	{
		if (map->step % 10 >= 5)
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
				map->ant_down1.ptr, coord.x, coord.y);
		else
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
				map->ant_down2.ptr, coord.x, coord.y);
	}
}

static void	draw_ant(t_map *map, t_point coord, t_point dif)
{
	if (ft_abs(dif.x) >= ft_abs(dif.y))
	{
		if (dif.x >= 0 && ft_abs(dif.x) >= ft_abs(dif.y))
		{
			if (map->step % 10 >= 5)
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->ant_left1.ptr, coord.x, coord.y);
			else
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->ant_left2.ptr, coord.x, coord.y);
		}
		else
		{
			if (map->step % 10 >= 5)
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->ant_right1.ptr, coord.x, coord.y);
			else
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->ant_right2.ptr, coord.x, coord.y);
		}
	}
	else
		draw_horizontal_ant(map, coord, dif);
}

static void	draw_moving_ant(t_map *map, int x, int y, int n)
{
	x = 25 + map->room[map->ant[n]].x * map->pipe_len.x +
		map->room_image.width / 2 - map->ant_right1.width / 2 -
		(((map->room[map->ant[n]].x - map->room[map->ant_goal[n]].x)
		* map->step * map->pipe_len.x) / map->total_step);
	y = 25 + map->room[map->ant[n]].y * map->pipe_len.y +
		map->room_image.height / 2 - map->ant_right1.height / 2
		- (((map->room[map->ant[n]].y - map->room[map->ant_goal[n]].y)
		* map->step * map->pipe_len.y) / map->total_step);
	draw_ant(map, fill_point(x + 5, y), fill_point((map->room[map->ant[n]].x
		- map->room[map->ant_goal[n]].x) * map->pipe_len.x,
		(map->room[map->ant[n]].y - map->room[map->ant_goal[n]].y)
		* map->pipe_len.y));
}

void		draw_all_ant(t_map *map)
{
	int n;
	int x;
	int y;

	n = -1;
	while (++n < map->nb_ant)
	{
		if (map->ant_goal[n] == -1)
		{
			x = 25 + map->room[map->ant[n]].x * map->pipe_len.x +
				map->room_image.width / 2 - map->ant_right1.width / 2;
			y = 25 + map->room[map->ant[n]].y * map->pipe_len.y +
				map->room_image.height / 2 - map->ant_right1.height / 2;
			mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
				map->ant_right1.ptr, x, y);
		}
		else
			draw_moving_ant(map, x, y, n);
	}
}
