/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   image_manip.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:13:48 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:01:13 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

int		image_vertical_rev(void *mlx_ptr, t_image *rev, t_image image)
{
	int x;
	int y;

	if (!get_new_image(mlx_ptr, rev, image.width, image.height))
		return (0);
	y = -1;
	while (++y < image.height)
	{
		x = -1;
		while (++x < image.width)
			rev->data[y * rev->width + x] =
				image.data[(image.height - y - 1) * image.width + x];
	}
	return (1);
}

int		image_horizontal_rev(void *mlx_ptr, t_image *rev, t_image image)
{
	int x;
	int y;

	if (!get_new_image(mlx_ptr, rev, image.width, image.height))
		return (0);
	y = -1;
	while (++y < image.height)
	{
		x = -1;
		while (++x < image.width)
			rev->data[y * rev->width + x] =
				image.data[y * image.width + (image.width - x - 1)];
	}
	return (1);
}

int		image_rotate(void *mlx_ptr, t_image *rev, t_image image)
{
	int x;
	int y;

	if (!get_new_image(mlx_ptr, rev, image.height, image.width))
		return (0);
	y = -1;
	while (++y < rev->height)
	{
		x = -1;
		while (++x < rev->width)
			rev->data[y * rev->width + x] = image.data[x * image.width + y];
	}
	return (1);
}
