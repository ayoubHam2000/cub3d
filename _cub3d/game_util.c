/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:35:13 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/04 00:02:28 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player()
{
	t_player	*p;
	t_point		pos;

	p = &(get_prog()->player);
	pos.x = (p->x / TILE_SIZE);
	pos.y = (p->y / TILE_SIZE);
	draw_square(pos.x * TILE_SIZE_MAP, pos.y * TILE_SIZE_MAP, TILE_SIZE_MAP, 0xff00ff);
}

void	draw_player_in_map()
{
	t_player	*p;
	float		angle;
	float		max_angle;
	float		length;

	p = &(get_prog()->player);
	angle = p->angle - p->view_angle / 2;
	max_angle = p->angle + p->view_angle / 2;
	while (angle < max_angle)
	{
		length = ray_casting(p, angle);
		draw_line(angle, length, p->x, p->y, 0xff00ff);
		angle += 0.01;
	}
}

void	draw_map_world(void)
{
	char	**map;
	int		x;
	int		y;
	int		size;

	map = get_prog()->map->map;
	size = TILE_SIZE;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '1')
				draw_square(y * size, x * size, size, 0xffffff);
			else
				draw_square(y * size, x * size, size, 0x223322);
			y++;
		}
		x++;
	}
}

void	mini_map(t_prog *prog)
{
	t_point	size;
	
	size.x = get_longest_line_width(prog->map->map) * TILE_SIZE_MAP;
	size.y = prog->map->len * TILE_SIZE_MAP;
	//replace_image(prog, size.x, size.y);
	replace_image(prog, WIN_SIZE, WIN_SIZE);
	draw_map_world();
	draw_player_in_map();
	//draw_map();
	//draw_player();
	//mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, WIN_SIZE - size.x, WIN_SIZE - size.y);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, WIN_SIZE, 0);
}
