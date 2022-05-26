/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:48:49 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/26 17:54:16 by aben-ham         ###   ########.fr       */
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
# include <fcntl.h>
# include <mlx.h>
# include "../_cub3d/debug/debug.h"

# define WIN_TITLE "cub3d"
# define WIDTH (700)
# define HEIGHT (500)
# define MINIMAP_W (170)
# define MINIMAP_H (120)

# define NO 0
# define SO 1
# define WE 2
# define EA 3

//init
int			check_arg(int ac, char **av);
t_prog		*get_prog(void);
void		*init_mlx(t_prog *prog);

//rendering
void		*replace_image(t_prog *prog, int w, int h);
void		ft_put_pixel(int x, int y, int color);
void		ft_put_pixel_in(int x, int y, int color);
void		ft_put_pixel_color(int x, int y);
int			get_tex_color(t_tex *tex, int x, int y);
int			shade_color(int color, float divide);

//start
void		draw_floor(t_prog *prog);
void		draw_ceil(t_prog *prog);
void		start_game(t_prog *prog);

//parsing -> setup
int			check_map(t_prog *prog, char **map);
int			load_map(t_prog *prog, t_queue *map);
int			load_textures(t_prog *prog, t_queue *texs);
t_file_data	*read_file(char *file);
int			load_types(t_prog *prog, t_queue *texs, t_queue *types);
void		init_player_pos(t_player *player);
int			setup(t_prog *prog, char *file);

//events
int			on_mouse_move(int x, int y, t_prog *prog);
int			on_key_down(int keycode, t_prog *prog);
int			on_key_up(int keycode, t_prog *prog);
int			exit_cube3d(t_prog *prog);
void		perform_events(t_prog *prog);

//ray_casting
void		raycasting(double camera_x, t_ray *ray, t_player *player);

//mini_map
void		draw_minimap(t_prog *prog);

//utils
int			is_empty_line(char *line);
int			get_longest_line_width(char **map);
int			is_comment(char *line);
size_t		get_time(void);
int			*get_tex(int x, int y);

//sprite
void		 sprite(t_prog *prog, double *ZBuffer);

#endif
