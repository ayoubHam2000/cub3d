/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/01 18:17:43 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player()
{
	t_player	*p;

	p = &(get_prog()->player);
	draw_square(p->x, p->y, 4, 0xff00ff);
}

void	projection(void)
{
	t_player	*p;
	float		angle;
	float		max_angle;
	float		length;

	p = &(get_prog()->player);
	angle = p->angle - 2;
	max_angle = p->angle + 2;
	while (angle < max_angle)
	{
		length = ray_casting(p, angle);
		//draw_line(angle, length, p->x, p->y, 0xff00ff);
		angle += 0.01;
	}
}

void	mini_map(t_prog *prog)
{
	t_point	size;
	
	size.x = get_longest_line_width(prog->map->map) * TILE_SIZE;
	size.y = prog->map->len * TILE_SIZE;
	replace_image(prog, size.x, size.y);
	draw_map();
	draw_player();
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, WIN_SIZE - size.x, WIN_SIZE - size.y);
}

void	game(t_prog *prog)
{
	replace_image(prog, WIN_SIZE, WIN_SIZE);
	draw_square(0, 0, 40, 0xff5588);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
}

void	game_frame(t_prog *prog)
{
	game(prog);
	mini_map(prog);
}
