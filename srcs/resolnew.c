/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resolnew.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 18:09:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 13:08:44 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"




#include <time.h>
clock_t timet;
clock_t tt;




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
	test_compa[size] = path;
}

int		recur_get_step(int	*test_compa, int size)
{
	int	i;

	i = -1;
	while (++i < size && test_compa[i] != -1)
		;
	return (i);
}

uint64_t		*cpy_megapath(uint64_t *src, int size)
{
	int	i;
	uint64_t	*dest;

//	tt = clock();
	if (!(dest = malloc(sizeof(uint64_t) * size)))
		return (NULL);
	i = -1;
	while (++i < size)
		dest[i] = src[i];
//timet += ((double) (clock() - tt));

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

	if ((megapath[j >> 6] & (1ULL << (j % 64))))
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
		if (megapath[i] & 1ULL << (j))
			ft_putchar('1');
		else
			ft_putchar('0');
		j--;
	}
//ft_printf("  %llu  ",megapath[i >> 6] );
	while (--i >= 0)
	{
		j = 64;
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

/*uint64_t	*add_path(uint64_t *megapath, uint64_t *newpath, int size)
  {
  int			i;
  uint64_t	*new_mega;
  int old_size = size;
  i = -1;
  size = (size >> 6) + 1;
  if (!(new_mega = (malloc(sizeof(uint64_t) * size))))
  return (NULL);
  print_megapath(megapath, old_size);
  print_megapath(newpath, old_size);
  while (++i < size)
  new_mega[i] = megapath[i] & newpath[i];
  print_megapath(new_mega, old_size);
  return (new_mega);
  }*/

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
/*
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

//	for (int k = 0; k < recur_get_step(test_comp, map->nb_path); k++)
//		ft_printf(_BLUE_ "%d " _EOC_ ,test_comp[k]);
//	ft_putendl("");
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
//	ft_printf("%d\n", recur_get_step(test_comp, map->nb_path) - 1);
//	for (int k = 0; k < recur_get_step(test_comp, map->nb_path); k++)
//		ft_printf(_RED_ "%d " _EOC_ ,test_comp[k]);
//	ft_putendl("");
//if ((j = recur_get_step(test_comp, map->nb_path)))
//	if (last_recur)
{
j = recur_get_step(test_comp, map->nb_path);
test_comp[j - 1] = -1;
}
//	ft_printf(_GREEN_ "out\n" _EOC_);
return  (1);
}*/

void	add_path(uint64_t *megapath , uint64_t *new_path, int size)
{
	int			i;

//		int old_size = size;
	i = -1;
	size = (size >> 6) + 1;
//		if (!(new_mega = (malloc(sizeof(uint64_t) * size))))
//			return (NULL);
//			print_megapath(megapath, old_size);
//			print_megapath(new_path, old_size);
	while (++i < size)
		megapath[i] &= new_path[i];
//			print_megapath(megapath, old_size);
//	ft_putendl("");
}


void	reset_megapath(uint64_t *megapath, int *test_comp, t_map *map,
		int whereami)
{
	int	i;
	int	size;
	
//	tt = clock();
	size = (map->nb_path >> 6) + 1;
	i = -1;
	while (++i < size)
		megapath[i] = 0xFFFFFFFFFFFFFFFF;
	i = -1;
//	ft_printf(_CYAN_);
	while (++i < whereami)
		add_path(megapath, map->path_compat.matrixbin[test_comp[i]], map->nb_path);
//	ft_printf(_EOC_);
//timet += ((double) (clock() - tt));
}

int		fucking_recursive(t_map *map, int j, uint64_t *megapath, int *test_comp)
{
	int			speed;
	int			i;
	int			whereami;
//	uint64_t	*tmp;

//	ft_printf(_GREEN_ "In\n" _EOC_);
	whereami = recur_get_step(test_comp, map->nb_path);
	while (++j < map->nb_path && map->path_len[j] < map->best_speed)
		if (test_new_path(megapath, j))
		{
			push_test_compa(test_comp, j, whereami);
	//		if(!(tmp = cpy_megapath(megapath, map->nb_path)))
	//			return (0);

	//		add_path(tmp, map->path_compat.matrixbin[j], map->nb_path);
//how_long_will_it_be(map, whereami, 0, test_comp);
			add_path(megapath, map->path_compat.matrixbin[j], map->nb_path);
			if ( map->best_speed > (speed = how_long_will_it_be(map,
							whereami, 0, test_comp)))
			{
				i = -1;
				while (test_comp[++i] != -1)
					map->best_compa[i] = test_comp[i];
				map->best_speed = speed;
			}
			(fucking_recursive(map, j, megapath, test_comp));

			//(fucking_recursive(map, j, tmp, test_comp));
		reset_megapath(megapath, test_comp, map, whereami);
//		reset_megapath(megapath, test_comp, map, whereami);

		//	free(tmp);
		}
	if ((whereami = recur_get_step(test_comp, map->nb_path))) 
		test_comp[whereami - 1] = -1;
//	ft_printf(_RED_ "out\n" _EOC_);
	return  (1);
}


void	print_matrix(t_map *map)
{
	int i;
	int	j;

	i = -1;
	while (++i < map->nb_path)
	{
		j = map->nb_path;
		if ( i == 0)
			ft_printf("MATRIX =\n");
		while (--j >= 0)
			ft_printf (_GREEN_ "%d" _EOC_, map->path_compat.matrix[i][j]);
	//	if ( i ==0)
		ft_putendl("");
	}
	ft_printf("BINARY=\n");
			print_megapath( map->path_compat.matrixbin[0], map->nb_path);
	ft_putendl("");
}

int		resol(t_map *map)
{
	uint64_t	*megapath;
	int			*test_comp;
	int			i;
	timet = 0;

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
	map->best_speed = INT_MAX;
	while (++i < map->nb_path + 1)
	{
		test_comp[i] = -1;
		map->best_compa[i] = -1;
	}
	//	ft_printf("\nGO\n");
//	print_matrix(map);
	fucking_recursive(map, -1, megapath, test_comp);
	//	ft_printf("\nUngo\n");
	int j = -1;
	while (map->best_compa[++j] != -1)
		ft_printf("%d  ",map->best_compa[j]);
	ft_putendl("");
	ft_printf("reset time = %f\n", (double)timet / CLOCKS_PER_SEC );
	//freeeeeeeeeeeeeeeeee
	return (1);
}
