/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/28 14:36:58 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		wall_tex(t_prog *prog, int x, int y, int side)
{
	t_m_info	**map_info;

	map_info = prog->player.map_info;
	//printf("%d %d %d\n", x, y, side);
	if (side == SO && map_info[y - 1][x].type == 'D')
		return (get_tex(x, y - 1)[1]);
	else if (side == NO && map_info[y + 1][x].type == 'D')
		return (get_tex(x, y + 1)[1]);
	else if (side == EA && map_info[y][x - 1].type == 'D')
		return (get_tex(x - 1, y)[1]);
	else if (side == WE && map_info[y][x + 1].type == 'D')
		return (get_tex(x + 1, y)[1]);
	return (get_tex(x, y)[side]);
}

void	draw_tex_line(t_prog *prog, int win_x, t_ray *ray)
{
	t_point	line;
	int		x;
	double	y;
	double	step;
	int		color;
	t_tex	*tex;
	int		tex_index;

	//line.x = (ray->line_height * (-1) + HEIGHT) * 0.5;
	//line.y = (ray->line_height + HEIGHT) * 0.5;
	if (prog->player.map_info[ray->map_y][ray->map_x].type == 'D')
		tex_index = get_tex(ray->map_x, ray->map_y)[0];
	else
		tex_index = wall_tex(prog, ray->map_x, ray->map_y, ray->side);
	tex = prog->texs[tex_index];
	int i = HEIGHT - get_prog()->m_y;
	line.x = -0.5 * ray->line_height + i;
	line.y = 0.5 * ray->line_height + i;
	step = 1.0 * tex->height / ray->line_height;
	if (line.x < 0)
	{
		y = -line.x * step;
		line.x = 0;
	}
	if (line.y > HEIGHT)
		line.y = HEIGHT;
	x = tex->width * ray->wall_x;
	if (get_prog()->player.map_info[ray->map_y][ray->map_x].type == 'D')
		x -= get_prog()->player.map_info[ray->map_y][ray->map_x].timer * tex->width;
	while (line.x < line.y)
	{
		color = get_tex_color(tex, x, y);
		color = shade_color(color, ray->dist * 0.4);
		ft_put_pixel(win_x, line.x, color);
		line.x++;
		y += step;
	}
}

void	events(t_prog *prog)
{
	t_m_info	**map;
	int	x;
	int	y;

	map = prog->player.map_info;
	y = 0;
	while (prog->player.map[y])
	{
		x = 0;
		while (prog->player.map[y][x])
		{
			if (map[y][x].on)
			{
				map[y][x].timer += TIMER_CONST * map[y][x].on;
				if (map[y][x].on < 0)
					prog->player.map[y][x] = '1';
				if (map[y][x].timer >= 1.0f)
				{
					prog->player.map[y][x] = '0';
					map[y][x].timer = 1.0;
				}
				if (map[y][x].timer <= 0.0f)
					map[y][x].timer = 0;
				if (map[y][x].timer >= 1.0f || map[y][x].timer <= 0.0f)
					map[y][x].on = 0;
				//printf("%d %d->%.2f\n", x, y, map[y][x].timer);
			}
			x++;
		}
		y++;
	}
}

void	game(t_prog *prog)
{
	t_ray		ray;
	int			x;
	double		cameraX;
	double		Zbuffer[WIDTH];
	
	replace_image(prog, WIDTH, HEIGHT);
	//draw_sky_floor(prog->map);
	//draw_sky_floor(prog);
	draw_floor(prog);
	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	x = 0;
	events(prog);
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1.0;
		raycasting(cameraX, &ray, &prog->player);
		Zbuffer[x] = ray.dist;
		draw_tex_line(prog, x, &ray);
		x++;
	}
	sprite(prog, Zbuffer);
	draw_gun(prog);
	health_bar(prog);
	draw_minimap(prog);
	perform_events(prog);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	
}

void	change_mouse_location(t_prog *prog)
{
	int x;
	int y;
	int	to_x;

	to_x = -1;
	if (prog->m_x > WIDTH)
		to_x = 0;
	if (prog->m_x < 0)
		to_x = WIDTH;
	if (to_x == -1)
		return ;
	mlx_mouse_get_pos(prog->win, &x, &y);
	mlx_mouse_move(prog->win, to_x, y);
	prog->old_m_x = to_x;
	prog->m_x = to_x;
}

int	the_game(t_prog *prog)
{
	size_t		time;
	
	//change_mouse_location(prog);
	if (prog->player.health > 0)
	{
		game(prog);
	}
	else
	{
		game_over(prog);
		printf("%d -> Game Over\n", prog->frame);
	}
	prog->frame++;
	time = get_time();
	//system("clear");
	//if (time)
	//	printf("frame: %lu -- time: %lu -- fps: %lu\n", frame, time / 1000, (frame * 1000000 / time));
	//printf("---> %d %d\n", prog->m_x, prog->m_y);

	
	//mini_map(prog);
	return (0);
}

void	start_game(t_prog *prog)
{
	mlx_loop_hook(prog->mlx, the_game, prog);
}
