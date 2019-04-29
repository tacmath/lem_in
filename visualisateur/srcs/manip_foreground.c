/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mamip_foreground.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:15:18 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:35:13 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void		put_room_to_foreground(t_map *map, t_image room,
	int start_x, int start_y)
{
	int x;
	int y;

	if (start_x < 0 || start_y < 0)
		return ;
	y = -1;
	while (++y < room.height && y + start_y < map->foreground.height)
	{
		x = -1;
		while (++x < room.width && x + start_x < map->foreground.width)
			if (room.data[y * room.width + x] != 0)
			{
				map->foreground.data[map->foreground.width * (y + start_y)
					+ x + start_x] = map->background.data[(y + start_y) *
					map->background.width + x + start_x];
			}
	}
}

static void	ft_big_pix(t_map *map, int start_x, int start_y)
{
	int x;
	int y;

	y = start_y - PIPE / 2 - 1;
	while (++y < start_y + PIPE / 2)
	{
		x = start_x - PIPE / 2 - 1;
		while (++x < start_x + PIPE / 2)
			map->foreground.data[y * map->foreground.width + x] =
				map->background.data[y * map->background.width + x];
	}
}

static void	ft_linex(t_map *map, t_point start, t_point *pix, double dir)
{
	if ((int)(dir * ((*pix).x - start.x) + start.y) != (*pix).y)
	{
		while ((int)(dir * ((*pix).x - start.x) + start.y) != (*pix).y)
		{
			ft_big_pix(map, (*pix).x - 1, (*pix).y);
			if ((int)(dir * ((*pix).x - start.x) + start.y) > (*pix).y)
				(*pix).y++;
			else
				(*pix).y--;
		}
	}
	else
		ft_big_pix(map, (*pix).x - 1, (*pix).y);
	(*pix).x++;
}

static void	get_room_coord(t_map *map, t_point *point, int room)
{
	(*point).x = 25 + map->room[room].x * map->pipe_len.x
		+ map->room_image.width / 2;
	(*point).y = 25 + map->room[room].y * map->pipe_len.y
		+ map->room_image.height / 2;
}

void		draw_pipe(t_map *map, int room1, int room2)
{
	double	dir;
	t_point	pix;
	t_point	start;
	t_point	end;

	get_room_coord(map, &start, room1);
	get_room_coord(map, &end, room2);
	if (end.x < start.x)
		ft_pointswap(&end, &start);
	pix.x = start.x + 1;
	if ((dir = end.x - start.x) != 0)
		dir = (end.y - start.y) / dir;
	pix.y = start.y;
	while (pix.x <= end.x)
		ft_linex(map, start, &pix, dir);
	if ((end.x - start.x) == 0)
		while (end.y != pix.y)
		{
			ft_big_pix(map, pix.x - 1, pix.y);
			if (end.y > pix.y)
				pix.y++;
			else
				pix.y--;
		}
}
