/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visual.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 14:37:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:26:25 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# define PIPE				40
# define IMAGE_PATH			"visualisateur/images/"
# define KEY_PRESS			2
# define DESTROY_NOTIFY		17
# define KEY_ESCAPE			53

struct						s_point
{
	int						x;
	int						y;
};

typedef struct s_point		t_point;

struct						s_room
{
	char					*name;
	int						x;
	int						y;
};

typedef struct s_room		t_room;

struct						s_image
{
	void					*ptr;
	int						*data;
	int						width;
	int						height;
};

typedef struct s_image		t_image;

struct						s_map
{
	void					*mlx_ptr;
	void					*win_ptr;
	t_image					number[11];
	t_image					start_image;
	t_image					end_image;
	t_image					background;
	t_image					foreground;
	t_image					room_image[5];
	t_image					ant_up1;
	t_image					ant_up2;
	t_image					ant_down1;
	t_image					ant_down2;
	t_image					ant_right1;
	t_image					ant_right2;
	t_image					ant_left1;
	t_image					ant_left2;
	char					*path;
	t_room					*room;
	int						*ant;
	int						*ant_goal;
	int						step;
	int						total_step;
	int						nb_room;
	int						nb_ant;
	int						start;
	int						end;
	t_point					pipe_len;
	t_point					size;
};

typedef struct s_map		t_map;

int							image_vertical_rev(void *mlx_ptr,
							t_image *rev, t_image image);
int							image_horizontal_rev(void *mlx_ptr,
							t_image *rev, t_image image);
int							image_rotate(void *mlx_ptr,
							t_image *rev, t_image image);
int							get_room(t_map *map);
void						draw_all_ant(t_map *map);
int							draw_info(t_map *map);
void						put_room_to_foreground(t_map *map,
							t_image room, int start_x, int start_y);
void						ft_pointswap(t_point *p1, t_point *p2);
t_point						fill_point(int x, int y);
int							get_ant_in_start(t_map *map);
int							get_ant_in_end(t_map *map);
int							get_all_connection(t_map *map, char *line);
int							get_new_image(void *mlx_ptr,
							t_image *image, int x, int y);
int							get_image(void *mlx_ptr,
							t_image *image, char *name);
void						draw_pipe(t_map *map, int room1, int room2);
void						draw_all_room(t_map *map);
void						put_image_to_image(t_image *image,
							t_image calque, int x_start, int y_start);
void						put_room_to_foreground(t_map *map,
							t_image room, int x_start, int y_start);
int							get_info(t_map *map);
int							get_all_images(t_map *map);
int							ft_destroy(t_map *map);
int							deal_key(int key, t_map *map);
int							ft_struct_init(t_map *map);
void						ft_free_map(t_map *map, int n);

#endif
