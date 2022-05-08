/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:03:21 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/04 00:02:40 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# include <sys/time.h>

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}

int		is_hit_a_tile(t_map *map, int x, int y)
{
	if (y >= 0 && x >= 0 && y < map->len && x < ft_strlen(map->map[y]))
	{
		if (map->map[y][x] == '1')
			return (1);
		else
			return (0);
	}
	return (1);
}

void	verLine(int x, int s, int e, int color)
{
	while (s < e)
	{
		ft_put_pixel(x, s, color);
		s++;
	}
}

void	draw_tex_line(t_tex *tex, double wall_x, int lineHeight, double perpWallDist, int win_x)
{
	int		dlx;
	int		dly;
	int		x;
	double	y;
	int		color;
	double	step;
	int		h;
	size_t	s;
	int		bg;

	s = get_time();
	h = WIN_SIZE;
	dlx = (lineHeight * (-1) + h) * 0.5;
	dly = (lineHeight + h) * 0.5;
	x = tex->width * wall_x;
	step = 1.0 * tex->height / lineHeight;
	y = 0.0;
	bg = -1;
	color = 0xffffff;
	while (dlx < dly)
	{
		/*if (bg != (int)y)
		{
			color = get_tex_color(tex, x, y);
			bg = (int)y;
		}*/
		ft_put_pixel(win_x, dlx, color);
		dlx++;
		y += step;
	}
	printf("%lu\n", get_time() - s);
}

void	game(t_prog *prog)
{
	int			w, h;
	int			x;
	t_pointf	ray;
	t_pointf	deltaDist;
	t_pointf	sideDist;
	t_pointf	pos;
	t_point		map_pos;
	t_point		step;
	double		cameraX;
	double		perpWallDist;
	int			hit;
	int			side; //was a NS or a EW wall hit?
	int			lineHeight;
	double		wall_x;
	t_tex		*tex;
	size_t		s;

	s = get_time();
	replace_image(prog, WIN_SIZE, WIN_SIZE);
	w = WIN_SIZE;
	h = WIN_SIZE;
	x = 0;
	
	pos = prog->player.pos;
	while (x < w)
	{
		cameraX = 2 * x / (double)w - 1.0;
		ray.x = prog->player.dir.x + prog->player.plane.x * cameraX;
		ray.y = prog->player.dir.y + prog->player.plane.y * cameraX;

		deltaDist.x = (ray.x == 0) ? 1e30 : fabs(1.0 / ray.x);
		deltaDist.y = (ray.y == 0) ? 1e30 : fabs(1.0 / ray.y);

		map_pos.x = (int)pos.x;
		map_pos.y = (int)pos.y;

		if (ray.x < 0)
		{
			step.x = -1;
			sideDist.x = (pos.x - map_pos.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map_pos.x + 1 - pos.x) * deltaDist.x;
		}
		if (ray.y < 0)
		{
			step.y = -1;
			sideDist.y = (pos.y - map_pos.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map_pos.y + 1 - pos.y) * deltaDist.y;
		}
		hit = 0;
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				map_pos.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map_pos.y += step.y;
				side = 1;
			}
			if (is_hit_a_tile(prog->map, map_pos.x, map_pos.y))
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;
		
		lineHeight = (h / perpWallDist);
		//texture--------------------------
		//texture--------------------------
		if (side == 0)
		{
			wall_x = pos.y + perpWallDist * ray.y;
			if (map_pos.x < pos.x)
				tex = prog->texs[0];
			else
				tex = prog->texs[1];
		}
		else
		{
			wall_x = pos.x + perpWallDist * ray.x;
			if (map_pos.y < pos.y)
				tex = prog->texs[2];
			else
				tex = prog->texs[3];
		}
		wall_x = wall_x - (int)wall_x;
		draw_tex_line(tex, wall_x, lineHeight, perpWallDist, x);
		x++;
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	printf("--->%lu\n", get_time() - s);
}

void	game_frame(t_prog *prog)
{
	game(prog);
	//mini_map(prog);
}
