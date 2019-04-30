/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 11:53:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:25:45 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void		ft_pointswap(t_point *p1, t_point *p2)
{
	t_point tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

t_point		fill_point(int x, int y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}

int			get_ant_in_start(t_map *map)
{
	int n;
	int ant;

	ant = 0;
	n = -1;
	while (++n < map->nb_ant)
		if (map->ant[n] == map->start && map->ant_goal[n] == -1)
			ant++;
	return (ant);
}

int			get_ant_in_end(t_map *map)
{
	int n;
	int ant;

	ant = 0;
	n = -1;
	while (++n < map->nb_ant)
		if (map->ant[n] == map->end && map->ant_goal[n] == -1)
			ant++;
	return (ant);
}

void		ft_free_map(t_map *map, int n)
{
	n = -1;
	while (++n < map->nb_room)
		free(map->room[n].name);
	n = -1;
	while (++n < 11)
		mlx_destroy_image(map->mlx_ptr, map->number[n].ptr);
	mlx_destroy_image(map->mlx_ptr, map->start_image.ptr);
	mlx_destroy_image(map->mlx_ptr, map->end_image.ptr);
	mlx_destroy_image(map->mlx_ptr, map->background.ptr);
	mlx_destroy_image(map->mlx_ptr, map->foreground.ptr);
	n = -1;
	while (++n < 5)
		mlx_destroy_image(map->mlx_ptr, map->room_image[n].ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_up1.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_up2.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_down1.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_down2.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_right1.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_right2.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_left1.ptr);
	mlx_destroy_image(map->mlx_ptr, map->ant_left2.ptr);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	ft_super_free(6, map->room, map->ant, map->ant_goal,
		map->path, map->mlx_ptr, map);
}
