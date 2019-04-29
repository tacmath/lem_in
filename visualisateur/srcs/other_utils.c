/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   other_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 14:45:36 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 15:16:01 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

void	string_put(t_map *map, t_point coord, char *str)
{
	int n;

	n = -1;
	while (str[++n])
	{
		if (str[n] >= '0' && str[n] <= '9')
		{
			mlx_put_image_to_window(map->mlx_ptr,
				map->win_ptr, map->number[str[n] - '0'].ptr, coord.x, coord.y);
			coord.x += map->number[str[n] - '0'].width;
		}
	}
	mlx_put_image_to_window(map->mlx_ptr,
			map->win_ptr, map->number[10].ptr, coord.x, coord.y);
}

int		draw_info(t_map *map)
{
	char	*tmp;
	int		x;
	int		y;

	mlx_put_image_to_window(map->mlx_ptr,
			map->win_ptr, map->foreground.ptr, 0, 0);
	if (!(tmp = ft_itoa(get_ant_in_start(map))))
		return (0);
	x = 25 + map->room[map->start].x * map->pipe_len.x + map->room_image.width
	/ 2 - (ft_strlen(tmp) + 1) * 17 - map->start_image.width / 2;
	y = 18 + map->room[map->start].y * map->pipe_len.y +
		map->room_image.height;
	mlx_put_image_to_window(map->mlx_ptr,
			map->win_ptr, map->start_image.ptr, x, y);
	string_put(map, fill_point(x + map->start_image.width, y), tmp);
	if (ft_super_free(1, tmp) || !(tmp = ft_itoa(get_ant_in_end(map))))
		return (0);
	x = 25 + map->room[map->end].x * map->pipe_len.x + map->room_image.width
	/ 2 - (ft_strlen(tmp) + 1) * 17 - map->end_image.width / 2;
	y = 18 + map->room[map->end].y * map->pipe_len.y +
		map->room_image.height;
	mlx_put_image_to_window(map->mlx_ptr,
			map->win_ptr, map->end_image.ptr, x, y);
	string_put(map, fill_point(x + map->end_image.width, y), tmp);
	return (!ft_super_free(1, tmp));
}
