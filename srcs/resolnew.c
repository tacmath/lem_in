/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resol.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:26:27 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 15:13:14 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void		put_resol(t_map *map, int ant, int room)
{
	ft_putchar('L');
	ft_putnbr(ant + 1);
	ft_putchar('-');
	ft_putstr(map->room[room].name);
	ft_putchar(' ');
}

void	push_test_compa(int	*test_compa, int path, int size)
{
	int		i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	test_compa[i] = path;
}

int		recur_get_step(int	*test_compa, int size)
{
	int	i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	return (i);
}

int		*cpy_megapath(int *src, int size)
{
	int	i;
	int	*dest;

	if (!(dest = malloc(sizeof(int) * size)))
		return (NULL);
	i = -1;
	while (++i < size)
		dest[i] = src[i];
	return (dest);
}


uint64_t	*bin_init(int size)
{
	int			i;
	uint64_t	*bin;

	i = -1;
	size = (size >> 6) + 1;
	if (!(bin = (malloc(sizeof(uint64_t) * size))))
		return (NULL);
	while (++i < size)
		bin[i] = 0xFFFFFFFFFFFFFFFF;
	return (bin);
}

int		test_new_path(uint64_t *megapath, int j)
{

	if ((megapath[j >> 6] & (1 << (j % 64))))
	{
		//			ft_printf( _GREEN_ "yep biatch\n" _EOC_);
		return (1);
	}
	//			ft_printf( _RED_ "nope biatch\n" _EOC_);

	return (0);
}


void	print_megapath(uint64_t *megapath, int size)
{
	int	i;
	int	j;

	size--;
	i = size >> 6;
	j  = size % 64;
	while (j > -1)
	{
		if (megapath[i >> 6] & 1 << (j))
			ft_putchar('1');
		else
			ft_putchar('0');
		j--;
	}

	while (i-- > 0)
	{
		j = 64;
		while (j-- > -1)
		{
			if (megapath[i] & 1 << (j % 64))
				ft_putchar('1');
			else
				ft_putchar('0');
		}
	}
	ft_putchar('\n');
}

uint64_t	*add_path(uint64_t *megapath, uint64_t *newpath, int size)
{
	int			i;
	uint64_t	*new_mega;
	//int old_size = size;
	i = -1;
	size = (size >> 6) + 1;
	if (!(new_mega = (malloc(sizeof(uint64_t) * size))))
		return (NULL);
	//	print_megapath(megapath, old_size);
	//	print_megapath(newpath, old_size);
	while (++i < size)
		new_mega[i] = megapath[i] & newpath[i];
	//	print_megapath(new_mega, old_size);
	return (new_mega);
}

/*int test_compa(t_map *map, int *compa)
{
	int n;
	int m;

	n = -1;
	while (compa[++n] != -1)
	{
		m = -1;
		while (compa[++m] != -1)
		{
			if (map->path_compat.matrix[compa[n]][compa[m]] == 0 && compa[m] != compa[n])
				return (0);
		}
	}
	return (1);
}*/
int		fucking_recursive(t_map *map, int j, uint64_t	*megapath,
		int	*test_comp)
{
	uint64_t	*tmp;
	int			speed;
	int			last_recur;
	int			i;

	last_recur = 1;
	//	ft_printf("We're lookin' %d\n", j + 1);
//	ft_putendl("test1");
	speed = 0;
	while (++j < map->nb_path && map->path_len[j] < map->best_speed)
	{
		if (test_new_path(megapath, j))
		{
			if (!(tmp = add_path(megapath, map->path_compat.matrixbin[j],
							map->nb_path)))
				return (0);
			push_test_compa(test_comp, j, map->nb_path);
			last_recur = 0;
//	ft_putendl("testmiddle");

	if ( map->best_speed > (speed = how_long_will_it_be(map,
				recur_get_step(test_comp, map->nb_path) -1 , 0, test_comp)))
	{
		i = -1;
		//		ft_printf("It's a progress\n");
		while (test_comp[++i] != -1)
		{
			map->best_compa[i] = test_comp[i]; //need to check if best_comp is initialized
			}
		//	ft_printf("same\n");
		map->best_speed = speed;
//		speed = 0;
	}

			(fucking_recursive(map, j, tmp, test_comp));
			free(tmp);
		//	test_comp[recur_get_step(test_comp, map->nb_path) - 1] = -1;
		}
	}
//	ft_putendl("testlast");
	ft_printf("%d\n", recur_get_step(test_comp, map->nb_path) - 1);
	for (int k = 0; k < recur_get_step(test_comp, map->nb_path); k++)
		ft_printf(_RED_ "%d " _EOC_ ,test_comp[k]);
	ft_putendl("");
	//if ((j = recur_get_step(test_comp, map->nb_path)))
	if (!last_recur)
	{
j = recur_get_step(test_comp, map->nb_path);
		test_comp[j - 1] = -1;
	}

	return  (1);
}

int		resol(t_map *map)
{
	uint64_t	*megapath;
	int			*test_comp;
	int			i;

	if(!(megapath = bin_init(map->nb_path)))
		return (0);
	if (!(test_comp = malloc(sizeof(int) * (map->nb_path + 1))))
	{
		free(megapath);
		return (0);
	}
	if (!(map->best_compa = malloc(sizeof(int) * (map->nb_path + 1))))
	{
		free(test_comp);
		free(megapath);
		return (0);
	}
	i = -1;
	map->best_speed = 66666666;
	while (++i < map->nb_path + 1)
	{
		test_comp[i] = -1;
		map->best_compa[i] = -1;
	}
	//	ft_printf("\nGO\n");
	fucking_recursive(map, -1, megapath, test_comp);
	//	ft_printf("\nUngo\n");
	int j = -1;
	while (map->best_compa[++j] != -1)
		ft_printf("%d  ",map->best_compa[j]);
	ft_putendl("");
	//freeeeeeeeeeeeeeeeee
	return (1);
}
