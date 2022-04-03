/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/03 12:27:36 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertival_line(int x, int length)
{
	int	s;
	int	e;
	int color;

	//color = ((length * 255.0) / (WIN_SIZE * 2));
	color = shade_color(255, 1 / ((float)length / (WIN_SIZE * 0.25)));
	//printf("%d\n", color);
	if (color > 255)
		color = 255;
	if (color < 20)
		color = 20;
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
/*
void	draw_vertival_line(int angle, int x, int length)
{
	int	s;
	int	e;
	int	i;
	int tex_type;
	int color;
	t_tex	*t;
	
	if (!length)
		return ;
	if (angle <= M_PI * 0.5f)
		tex_type = NO;
	else if (angle <= M_PI)
		tex_type = SO;
	else if (angle <= M_PI * 1.5f)
		tex_type = WE;
	else
		tex_type = EA;
	t = get_prog()->texs[tex_type];
	s = (WIN_SIZE - length) / 2;
	e = (WIN_SIZE + length) / 2;
	i = s;
	while (i < e)
	{
		color = get_tex_color(t, ((x % length) * t->width) / length, ((i - s) * t->height) / length);
		color = shade_color(color, 1 / ((float)length / (WIN_SIZE * 0.25)));
		ft_put_pixel(x, i, color);
		i++;
	}
}*/

void	make_sky_floor()
{
	get_prog()->color = 0x0000ff;
	draw_rectangle(0, 0, WIN_SIZE, WIN_SIZE / 2);
	get_prog()->color = 0x1e1e63;
	draw_rectangle(0, WIN_SIZE / 2, WIN_SIZE, WIN_SIZE / 2);
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
	make_sky_floor();
	while (angle < max_angle)
	{
		length = ray_casting(p, angle);
		length = fabs(cosf(angle - p->angle) * length);
		length = WIN_SIZE * TILE_SIZE / length;
		if (length > WIN_SIZE)
			length = WIN_SIZE;
		draw_vertival_line(i, length);
		angle += step;
		i++;
	}
}

void	game(t_prog *prog)
{
	int	i;
	int	j;

	replace_image(prog, WIN_SIZE, WIN_SIZE);
	//draw_map_world();
	//projection();
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
}

void	game_frame(t_prog *prog)
{
	//game(prog);
	mini_map(prog);
}
