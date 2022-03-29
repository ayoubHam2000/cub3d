/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:48:49 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:31:50 by aben-ham         ###   ########.fr       */
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

//parsing -> map
int		check_map(char **map);
char	**get_map_matrix(int fd);
int		check_identifier(char *identifier, int type);
t_type	**get_types(int	fd);
t_map	*get_map(char *file);

//map ->utils
char	*remove_break_line(char *str);
int		is_empty_line(char *line);
int		get_longest_line_len(char **map);

//events
int		on_mouse_down(int button, int x, int y, t_prog *prog);
int		on_key_up(int keycode, t_prog *prog);
int		exit_cube3d(t_prog *prog);

//general
int		check_arg(int ac, char **av);
void	*init_mlx(t_prog *prog);
t_prog	*init_prog(void);
void	*replace_image(t_prog *prog);
void	mlx_img_pixel_put(t_prog *prog, int x, int y, int color);

#endif
