/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:54:47 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/25 20:50:15 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
#define DEBUG_H

# include "structs.h"
# include <sys/time.h>

# define TILE_SIZE_MAP 8
# define MAX_LINE 1000

//draw
void	draw_map(void);
void	draw_square(int x, int y, int length, int color);
void	draw_line(float angle, float length, float offsetx, float offsety, float color);

void	draw_line(float angle, float length, float offsetx, float offsety, float color);
void	draw_ray(void);
void	draw_square(int x, int y, int length, int color);
void	draw_map();
void	draw_player_in_map();
void	draw_player();
void	draw_map_world(void);
void	mini_map(t_prog *prog);

#endif
