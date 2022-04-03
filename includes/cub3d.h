/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:48:49 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/03 12:36:46 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "utilities.h"
# include "mlx_utils.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>

#define INF 2000000
#define MAX_LINE 1000
#define TILE_SIZE 50
#define TILE_SIZE_MAP 10
#define RAY_LEN 100

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_pointf
{
	float	x;
	float	y;
}	t_pointf;

//parsing -> map
int		check_map(char **map);
char	**get_map_matrix(int fd);
int		check_identifier(char *identifier, int type);
t_type	**get_types(int	fd);
t_map	*get_map(char *file);

//map ->utils
char	*remove_break_line(char *str);
int		is_empty_line(char *line);
int		get_longest_line_width(char **map);

//events
int		on_mouse_down(int button, int x, int y, t_prog *prog);
int		on_key_down(int keycode, t_prog *prog);
int		on_key_up(int keycode, t_prog *prog);
int		exit_cube3d(t_prog *prog);

//general
int		check_arg(int ac, char **av);
t_prog	*get_prog(void);
void	*init_mlx(t_prog *prog);
void	*replace_image(t_prog *prog, int w, int h);
void	ft_put_pixel(int x, int y, int color);
void	ft_put_pixel_color(int x, int y);
void	game_frame(t_prog *prog);

//draw
void	draw_map(void);
void	draw_square(int x, int y, int length, int color);
void	draw_line(float angle, float length, float offsetx, float offsety, float color);

//ray_casting
float	ray_casting_x(t_player *player);
float	ray_casting_y(t_player *player);
float	ray_casting(t_player *player, float angle);

//game utils
void	draw_line(float angle, float length, float offsetx, float offsety, float color);
void	draw_ray(void);
void	draw_square(int x, int y, int length, int color);
void	draw_rectangle(int x, int y, int w, int h);
void	draw_map();
int		is_tile(t_map *map, int x, int y);
void	draw_player_in_map();

void	*get_texture(t_prog *prog, void *path);
int		get_tex_color(t_tex *tex, int x, int y);
int		shade_color(int color, float divide);
int		load_textures(t_prog *prog);

void	draw_player();
void	draw_map_world(void);
void	mini_map(t_prog *prog);
#endif
