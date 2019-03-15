/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 14:09:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 17:03:55 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>

struct					s_room
{
	int					*connection;
	int					nb_connection;
	char				*name;
	float				hype;
	int					heat;
	char				ant;
};

typedef struct s_room	t_room;

struct					s_map
{
	t_room				*room;
	int					*ant;
	int					*last_room;
	int					nb_room;
	int					nb_ant;
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
void					kylie_jenner(t_map *map);
void					move_ant(t_map *map);
#endif
