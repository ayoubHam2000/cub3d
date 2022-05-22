/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/22 10:55:56 by aben-ham         ###   ########.fr       */
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

	//line.x = (ray->line_height * (-1) + HEIGHT) * 0.5;
	//line.y = (ray->line_height + HEIGHT) * 0.5;
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
	while (line.x < line.y)
	{
		color = get_tex_color(tex, x, y);
		color = shade_color(color, ray->dist * 0.4);
		ft_put_pixel(win_x, line.x, color);
		line.x++;
		y += step;
	}
}

void	draw_sky_floor(t_prog *prog)
{
	int	y;
	int	x;
	int p;
	double	pos_z;
	double	row_dist;
	double	ray_dir_x_0;
	double	ray_dir_x_1;
	double	ray_dir_y_0;
	double	ray_dir_y_1;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		color;
	t_tex	*tex;
	t_tex	*ceil_tex;

	tex = prog->texs[0];
	ceil_tex = prog->texs[1];

	ray_dir_x_0 = prog->player.dir_x - prog->player.plane_x;
	ray_dir_y_0 = prog->player.dir_y - prog->player.plane_y;
	ray_dir_x_1 = prog->player.dir_x + prog->player.plane_x;
	ray_dir_y_1 = prog->player.dir_y + prog->player.plane_y;
	double	per_x = (2 * prog->player.plane_x) / WIDTH;
	double	per_y = (2 * prog->player.plane_y) / WIDTH;
	y = HEIGHT * 0.50;
	while (y < HEIGHT)
	{
		p = y - (HEIGHT / 2);
		pos_z = (0.5) * HEIGHT;
		row_dist = pos_z / p;

		floor_step_x = row_dist * per_x;
		floor_step_y = row_dist * per_y;
		//printf("%f, %f\n", floor_step_x, floor_step_y);

		floor_x = prog->player.x + row_dist * ray_dir_x_0;
		floor_y = prog->player.y + row_dist * ray_dir_y_0;
		
		x = 0;
		while (x < WIDTH)
		{
			cell_x = (int)(floor_x);
			cell_y = (int)(floor_y);

			tx = (int)(tex->width * (floor_x - cell_x)) & (tex->width - 1);
			ty = (int)(tex->height * (floor_y - cell_y)) & (tex->height - 1);
			floor_x += floor_step_x;	
			floor_y += floor_step_y;

			//if (y >= HEIGHT * 0.5)
			//{
				//floor
				color = get_tex_color(tex, tx, ty);
				color = (color >> 1) & 8355711;
				ft_put_pixel(x, y, color);

				color = get_tex_color(ceil_tex, tx, ty);
				//color = (color >> 1) & 8355711;
				ft_put_pixel(x, (HEIGHT - y - 1), color);
			//}
			x++;
		}
		y++;
	}
}

void	my_floor(t_prog *prog)
{
	int	x;
	int	y;
	double	dist;
	double	floor_x;
	double	floor_y;
	double	step_x;
	double	step_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	t_tex	*ceil_tex;
	t_tex	*floor_tex;
	int		color;
	double	m_p;

	ceil_tex = prog->texs[prog->floor[0]];
	floor_tex = prog->texs[prog->floor[1]];
	m_p = prog->m_y;
	y = m_p;
	while (y < HEIGHT)
	{
		dist = (HEIGHT * 0.5) / (y - m_p);
		floor_x = prog->player.x + dist * (prog->player.dir_x - prog->player.plane_x);
		floor_y = prog->player.y + dist * (prog->player.dir_y - prog->player.plane_y);
		step_x = dist * (2 * prog->player.plane_x) / WIDTH;
		step_y = dist * (2 * prog->player.plane_y) / WIDTH;
		x = 0;
		while (x < WIDTH)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = (int)(ceil_tex->width * (floor_x - cell_x)) & (ceil_tex->width -1);
			ty = (int)(ceil_tex->height * (floor_y - cell_y)) & (ceil_tex->height -1);
			
		
			if (y > m_p)
			{
				color = get_tex_color(ceil_tex, tx, ty);
				color = (color >> 1) & 8355711;
				ft_put_pixel(x, HEIGHT - y, color);
			}
			floor_x += step_x;
			floor_y += step_y;
			x++;
		}
		y++;
	}
	m_p = HEIGHT - prog->m_y;
	y = m_p;
	while (y < HEIGHT)
	{
		dist = (HEIGHT * 0.5) / (y - m_p);
		floor_x = prog->player.x + dist * (prog->player.dir_x - prog->player.plane_x);
		floor_y = prog->player.y + dist * (prog->player.dir_y - prog->player.plane_y);
		step_x = dist * (2 * prog->player.plane_x) / WIDTH;
		step_y = dist * (2 * prog->player.plane_y) / WIDTH;
		x = 0;
		while (x < WIDTH)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = (int)(ceil_tex->width * (floor_x - cell_x)) & (ceil_tex->width -1);
			ty = (int)(ceil_tex->height * (floor_y - cell_y)) & (ceil_tex->height -1);
			
		
			//if (y > m_p)
			//{
				color = get_tex_color(floor_tex, tx, ty);
				color = (color >> 1) & 8355711;
				ft_put_pixel(x, y, color);
			//}
			floor_x += step_x;
			floor_y += step_y;
			x++;
		}
		y++;
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
				if (map[y][x].timer >= 1.0f)
				{
					prog->player.map[y][x] = '1';
					map[y][x].timer = 1.0;
				}
				if (map[y][x].timer <= 0.0f)
				{
					map[y][x].timer = 0;
					prog->player.map[y][x] = '0';
				}
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
	t_ray	ray;
	int		x;
	double	cameraX;
	int tex_index;
	
	replace_image(prog, WIDTH, HEIGHT);
	//draw_sky_floor(prog->map);
	//draw_sky_floor(prog);
	my_floor(prog);

	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	x = 0;
	events(prog);
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1.0;
		
		raycasting(cameraX, &ray, &prog->player);
		if (prog->player.map_info[ray.map_y][ray.map_x].type == 'D')
			tex_index = get_tex(ray.map_x, ray.map_y)[0];
		else
			tex_index = get_tex(ray.map_x, ray.map_y)[ray.side];
		draw_tex_line(prog->texs[tex_index], x, &ray);
		x++;
	}
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
	static size_t	frame;
	size_t		time;
	
	//change_mouse_location(prog);
	game(prog);
	time = get_time();
	frame++;
	//system("clear");
	//if (time)
	//	printf("frame: %lu -- time: %lu -- fps: %lu\n", frame, time / 1000, (frame * 1000000 / time));
	//printf("---> %d %d\n", prog->m_x, prog->m_y);

	mini_map(prog);
	return (0);
}

void	game_frame(t_prog *prog)
{
	mlx_loop_hook(prog->mlx, the_game, prog);
}
