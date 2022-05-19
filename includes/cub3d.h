/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:48:49 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/19 15:21:59 by aben-ham         ###   ########.fr       */
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
# include <sys/time.h>
# include "mlx.h"

#define TILE_SIZE 30
#define TILE_SIZE_MAP 30
#define MAX_LINE 1000

# define WIN_TITLE "cub3d"

# define HEIGHT (500)
# define WIDTH (900)

//parsing -> setup
int		check_map(t_prog *prog, char **map);
char	**load_map(t_prog *prog, t_queue *map);
int		load_textures(t_prog *prog, t_queue *texs);
t_file_data	*read_file(char *file);
int		load_types(t_prog *prog, t_queue *texs, t_queue *types);
int		setup(t_prog *prog, char *file);
char	get_key_type(char c);

//map ->utils
int		is_empty_line(char *line);
int		get_longest_line_width(char **map);
int		is_comment(char *line);
size_t	get_time(void);

//events
int		on_mouse_move(int x, int y, t_prog *prog);
int		on_key_down(int keycode, t_prog *prog);
int		on_key_up(int keycode, t_prog *prog);
int		exit_cube3d(t_prog *prog);
void	perform_events(t_prog *prog);

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
void	raycasting(double camera_x, t_ray *ray, t_player *player);

//game utils
void	draw_line(float angle, float length, float offsetx, float offsety, float color);
void	draw_ray(void);
void	draw_square(int x, int y, int length, int color);
void	draw_rectangle(int x, int y, int w, int h);
void	draw_map();
void	draw_player_in_map();

int		get_tex_color(t_tex *tex, int x, int y);
int		shade_color(int color, float divide);

void	draw_player();
void	draw_map_world(void);
void	mini_map(t_prog *prog);


#endif
