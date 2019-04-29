/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   image.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:11:40 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:00:30 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "visual.h"

int		get_image(void *mlx_ptr, t_image *image, char *name)
{
	int trash[3];

	if (!(image->ptr = mlx_xpm_file_to_image(mlx_ptr, name,
		&image->width, &image->height)))
		return (0);
	if (!(image->data = (int*)mlx_get_data_addr(image->ptr,
		&trash[0], &trash[1], &trash[2])))
	{
		free(image->ptr);
		return (0);
	}
	return (1);
}

int		get_new_image(void *mlx_ptr, t_image *image, int x, int y)
{
	int trash[3];

	image->width = x;
	image->height = y;
	if (!(image->ptr = mlx_new_image(mlx_ptr, x, y)))
		return (0);
	if (!(image->data = (int*)mlx_get_data_addr(image->ptr,
					&trash[0], &trash[1], &trash[2])))
	{
		free(image->ptr);
		return (0);
	}
	return (1);
}

void	put_image_to_image(t_image *image, t_image calque,
	int start_x, int start_y)
{
	int x;
	int y;

	if (start_x < 0 || start_y < 0)
		return ;
	y = -1;
	while (++y < calque.height && y + start_y < image->height)
	{
		x = -1;
		while (++x < calque.width && x + start_x < image->width)
			if (calque.data[y * calque.width + x] >> 24 != -1)
			{
				image->data[image->width * (y + start_y) + x + start_x] =
					calque.data[y * calque.width + x];
			}
	}
}
