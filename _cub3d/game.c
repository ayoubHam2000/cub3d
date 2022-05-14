/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/14 14:43:09 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tex_line(t_tex *tex, int win_x, t_ray *ray)
{
	t_point	line;
	int		x;
	double	y;
	double	step;
	int		color;

	line.x = (ray->line_height * (-1) + HEIGHT) * 0.5;
	line.y = (ray->line_height + HEIGHT) * 0.5;
	step = 1.0 * tex->height / ray->line_height;
	if (line.x < 0)
	{
		y = -line.x * step;
		line.x = 0;
	}
	if (line.y > HEIGHT)
		line.y = HEIGHT;
	x = tex->width * ray->wall_x;
	while (line.x < line.y)
	{
		color = get_tex_color(tex, x, y);
		color = shade_color(color, ray->dist * 0.4);
		ft_put_pixel(win_x, line.x, color);
		line.x++;
		y += step;
	}
}

int		get_color(char *str)
{
	char	**colors;
	int		color;

	color = 0;
	colors = ft_split(str, ',');
	color += (ft_atoi(colors[0]) << 16);
	color += (ft_atoi(colors[1]) << 8);
	color += (ft_atoi(colors[2]));
	free_all(NULL);
	return (color);
}

void	draw_sky_floor(t_map *map)
{
	int	x;
	int	y;
	int	c1;
	int	c2;

	x = 0;
	c1 = get_color(map->types[4]->data);
	c2 = get_color(map->types[5]->data);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				ft_put_pixel(x, y, shade_color(c2, (y + 200) * 0.005));
			else
				ft_put_pixel(x, y, shade_color(c1, (HEIGHT - y + 200) * 0.005));
			y++;
		}
		x++;
	}
}

void	game(t_prog *prog)
{
	t_ray	ray;
	int		x;
	double	cameraX;
	
	replace_image(prog, WIDTH, HEIGHT);
	draw_sky_floor(prog->map);
	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1.0;
		raycasting(cameraX, &ray, &prog->player, prog->map->map);
		draw_tex_line(prog->texs[ray.side], x, &ray);
		x++;
	}
	perform_events(prog);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
}

int	the_game(t_prog *prog)
{
	static size_t	frame;
	size_t		time;
	game(prog);
	time = get_time();
	frame++;
	system("clear");
	if (time)
		printf("frame: %lu -- time: %lu -- fps: %lu\n", frame, time / 1000, (frame * 1000000 / time));
	mini_map(prog);
	return (0);
}

void	game_frame(t_prog *prog)
{
	mlx_loop_hook(prog->mlx, the_game, prog);
}
