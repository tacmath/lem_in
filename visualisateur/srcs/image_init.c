/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   image_init.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 14:41:43 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 15:12:37 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

static int	get_all_ant(t_map *map, char *path, char *name)
{
	if (!(name = ft_strjoin(path, "lemin_ant1.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->ant_up1), name)))
		return (0);
	free(name);
	if (!(name = ft_strjoin(path, "lemin_ant2.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->ant_up2), name)))
		return (0);
	free(name);
	if (!image_vertical_rev(map->mlx_ptr, &map->ant_down1, map->ant_up1))
		return (0);
	if (!image_vertical_rev(map->mlx_ptr, &map->ant_down2, map->ant_up2))
		return (0);
	if (!image_rotate(map->mlx_ptr, &map->ant_left1, map->ant_up1))
		return (0);
	if (!image_rotate(map->mlx_ptr, &map->ant_left2, map->ant_up2))
		return (0);
	if (!image_horizontal_rev(map->mlx_ptr, &map->ant_right1, map->ant_left1))
		return (0);
	if (!image_horizontal_rev(map->mlx_ptr, &map->ant_right2, map->ant_left2))
		return (0);
	return (1);
}

static int	get_number_images(t_map *map, char *path)
{
	int		n;
	char	number[2];
	char	*name;
	char	*tmp;

	if (!(tmp = ft_strjoin(path, "number/")))
		return (0);
	free(path);
	path = tmp;
	n = -1;
	while (++n < 10)
	{
		number[0] = n + '0';
		number[1] = '\0';
		if (!(tmp = ft_strjoin(number, ".xpm")))
			return (0);
		if (!(name = ft_strjoin(path, tmp)))
			return (0);
		free(tmp);
		if (!(get_image(map->mlx_ptr, &(map->number[n]), name)))
			return (0);
		free(name);
	}
	free(path);
	return (1);
}

static int	get_other_images(t_map *map, char *path)
{
	char *name;

	if (!(name = ft_strjoin(path, "End.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->end_image), name)))
		return (0);
	free(name);
	if (!(name = ft_strjoin(path, "Start.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->start_image), name)))
		return (0);
	free(name);
	if (!(name = ft_strjoin(path, "FinParenthese.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->number[10]), name)))
		return (0);
	free(name);
	if (!get_all_ant(map, path, name))
		return (0);
	if (!get_number_images(map, path))
		return (0);
	return (1);
}

int			get_all_images(t_map *map)
{
	char *path;
	char *name;

	if (!(path = ft_strjoin(map->path, IMAGE_PATH)))
		return (0);
	if (!(name = ft_strjoin(path, "background_lemin.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->background), name)))
		return (0);
	free(name);
	if (!(name = ft_strjoin(path, "foreground_lemin.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->foreground), name)))
		return (0);
	free(name);
	if (!(name = ft_strjoin(path, "ellipsoide_lemin.xpm")))
		return (0);
	if (!(get_image(map->mlx_ptr, &(map->room_image), name)))
		return (0);
	free(name);
	if (!get_other_images(map, path))
		return (0);
	return (1);
}
