/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 14:09:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/01 14:58:20 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
#include <stdint.h>
# include <stdlib.h>

struct					s_room
{
	int					*connection;
	int					nb_connection;
	char				*name;
	int					heat;
};

typedef struct s_room	t_room;

struct					s_matrix
{
	char				**matrix;
	uint64_t			**matrixbin;
	int					*nb_compat;
};

typedef struct s_matrix	t_matrix;


struct					s_ant
{
	int					room;
	int					i_path;
	int					path;
};

typedef struct s_ant	t_ant;

struct					s_map
{
	t_room				*room;
	int					**path;
	uint64_t			**path_room;
	t_matrix			path_compat;
	int					*best_compa;
	double				best_flow;
	int					best_nb_compat;
	int					*path_len;
	int 				**comp;
	t_ant				*ant;
	int					*ant_progress;
	int					nb_room;
	int					nb_ant;
	int					nb_path;
	int					start;
	int					end;
};

typedef struct s_map	t_map;


int						get_room(t_map *map, char ***output);
int						rooms_init(t_map *map);
int						get_all_connection(t_map *map, char *line,
						char ***output);
int						sta_line(t_map *map, int room1, int room2);
int						init_struct(t_map *map, char ***output);
int						add_to_output(char ***output, char *new_line);
void					write_output(char **output);
void					free_map(t_map *map);
int						get_error(t_map *map);
void					get_room_heat(t_map *map, int room, int heat);
//void					kylie_jenner(t_map *map);
void					move_ant(t_map *map);
int						compatibility_all(t_map *map);
int						resol(t_map *map);
int						gogogo(t_map *map, int *count);
void					put_resol(t_map *map, int ant, int room);
void					sort_best_comp(t_map *map);
int						how_long_will_it_be(t_map *map, int min_path,
						int plusant)

#endif
