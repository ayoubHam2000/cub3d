/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 14:49:03 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertival_line(int x, int length)
{
	int	s;
	int	e;
	int color;

	color = ((length * 255) / 100.0);
	printf("%d\n", color);
	color %= 255;
	color = (color << 16) | (color << 8) | color;
	s = (WIN_SIZE - length) / 2;
	e = (WIN_SIZE + length) / 2;
	while (s < e)
	{
		if (length)
		ft_put_pixel(x, s, color);
		s++;
	}
}

void	projection(void)
{
	t_player	*p;
	float		angle;
	float		max_angle;
	float		length;
	float		step;
	int			i;

	p = &(get_prog()->player);
	angle = p->angle - p->view_angle / 2;
	max_angle = p->angle + p->view_angle / 2;
	step = p->view_angle / WIN_SIZE;
	i = 0;
	draw_square(0, 0, WIN_SIZE / 2, 0x0000ff);
	draw_square(WIN_SIZE / 2, 0, WIN_SIZE / 2, 0x0000ff);
	draw_square(0, WIN_SIZE / 2, WIN_SIZE / 2, 0x1e1e63);
	draw_square(WIN_SIZE / 2, WIN_SIZE / 2, WIN_SIZE / 2, 0x1e1e63);
	while (angle < max_angle)
	{
		length = ray_casting(p, angle);
		draw_vertival_line(i, 2000 / length);
		//draw_line(angle, length, p->x, p->y, 0xff00ff);
		angle += step;
		i++;
	}
}

void	game(t_prog *prog)
{
	replace_image(prog, WIN_SIZE, WIN_SIZE);
	//draw_map_world();
	projection();
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
}

void	game_frame(t_prog *prog)
{
	game(prog);
	mini_map(prog);
}
