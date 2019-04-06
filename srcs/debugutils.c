/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debugutils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/06 16:58:34 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 17:31:19 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void		print_megapath(uint64_t *megapath, int size)
{
	int	i;
	int	j;

	size--;
	i = size >> 6;
	j = size % 64;
	while (j > -1)
	{
		if (megapath[i] & 1ULL << (j))
			ft_putchar('1');
		else
			ft_putchar('0');
		j--;
	}
	while (--i >= 0 && (j = 64) > 0)
	{
		while (--j > -1)
		{
			if (megapath[i] & 1ULL << (j % 64))
				ft_putchar('1');
			else
				ft_putchar('0');
		}
	}
	ft_putchar('\n');
}

void		print_matrix(t_map *map)
{
	int i;
	int	j;

	i = -1;
	while (++i < map->nb_path)
	{
		j = map->nb_path;
		if (i == 0)
			ft_printf("MATRIX =\n");
		while (--j >= 0)
			ft_printf(_GREEN_ "%d" _EOC_, map->path_compat.matrix[i][j]);
		ft_putendl("");
	}
	ft_printf("BINARY=\n");
	print_megapath(map->path_compat.matrixbin[0], map->nb_path);
	ft_putendl("");
}

void		printf_best_compa(t_map *map)
{
	int	i;

	i = -1;
	while (map->best_compa[++i] != -1)
		ft_printf(_BLUE_ "path : %d   len : %d\n" _EOC_, map->best_compa[i],
				map->path_len[map->best_compa[i]]);
	ft_putchar('\n');
}
