/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:49:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/28 13:24:59 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	gun_center(t_prog *prog)
{
	int	x;
	int	y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			ft_put_pixel(x + WIDTH / 2 - 2, y + HEIGHT / 2 - 2, 0xff0000);
			x++;
		}
		y++;
	}	
}

void	draw_gun(t_prog *prog)
{
	int			x;
	int			y;
	int			c;
	t_tex		*tex;

	if (prog->pressed_key[3] == 1)
		tex = prog->static_tex.gun[prog->frame % 5];
	else
		tex = prog->static_tex.gun[0];

	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH * 0.18;
		while (x < WIDTH * 0.82)
		{
			c = get_tex_color(tex, (x - WIDTH * 0.18) * tex->width / (WIDTH * 0.64),
				(y) * tex->height / (HEIGHT));
			if (c != -16777216)
				ft_put_pixel(x + WIDTH * 0.0875, y, c);
			x++;
		}
		y++;
	}
	gun_center(prog);
}

void	health_bar(t_prog *prog)
{
	int	x;
	int	y;
	int	w;
	int	h;

	y = 0;
	w = WIDTH / 4;
	h = HEIGHT / 50;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (y == 0 || y == h - 1 || x == 0 || x == w - 1)
				ft_put_pixel(x + (WIDTH - w) / 2, y + (HEIGHT - h) - 3, 0);
			else if (x < prog->player.health)
				ft_put_pixel(x + (WIDTH - w) / 2, y + (HEIGHT - h) - 3, 0x00ff00);
			x++;
		}
		y++;
	}
}

void	game_over(t_prog *prog)
{
	int		x;
	int		y;
	t_tex	*tex;

	replace_image(prog, WIDTH, HEIGHT);
	if (prog->frame % 100 > 50)
		tex = prog->static_tex.game_over[0];
	else
		tex = prog->static_tex.game_over[1];
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(x, y, get_tex_color(tex, x * tex->width / WIDTH, y * tex->height / HEIGHT));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
}
