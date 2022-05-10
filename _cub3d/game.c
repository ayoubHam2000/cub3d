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
	while (dlx < dly)
	{
		if (bg != (int)y)
		{
			color = get_tex_color(tex, x, y);
			bg = (int)y;
		}
		ft_put_pixel(win_x, dlx, color);
		dlx++;
		y += step;
	}
	printf("%lu\n", get_time() - s);
}

static int	dda_loop(char **map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	dda(char **map, t_ray *ray, t_ray_info *ray_info)
{
	ray->step_x = (ray->ray_x >= 0.0) * 2 - 1;
	ray->step_y = (ray->ray_y >= 0.0) * 2 - 1;
	if (ray->step_x == 1)	
		ray->side_dist_x = (ray->map_x + 1 - ray->pos_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	if (ray->step_y == 1)	
		ray->side_dist_y = (ray->map_y + 1 - ray->pos_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	dda_loop(map, ray);
	if (ray->side == 0)
	{
		ray_info->perpWallDist = ray->side_dist_x - ray->delta_dist_x;
		ray_info->wall_x = ray->pos_x + ray->delta_dist_x * ray_info->perpWallDist;
		ray_info->side = ray->map_x < ray->pos_x;
	}
	else
	{
		ray_info->perpWallDist = ray->side_dist_y - ray->delta_dist_y;
		ray_info->wall_x = ray->pos_x + ray->delta_dist_y * ray_info->perpWallDist;
		ray_info->side = 2 + ray->map_y < ray->pos_y;
	}
}

void	raycasting(t_player *p, char **map, t_ray_info *ray_info)
{
	int			x;
	double		camera_x;
	t_ray		ray;

	x = 0;
	ray.pos_x = p->pos.x;
	ray.pos_y = p->pos.y;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1.0;
		ray.ray_x = p->dir.x + p->plane.x * camera_x;
		ray.ray_y = p->dir.y + p->plane.y * camera_x;
		ray.delta_dist_x = 1e30;
		if (ray.ray_x != 0.0)
			ray.delta_dist_x = fabs(1.0 / ray.ray_x);
		ray.delta_dist_y = 1e30;
		if (ray.ray_y != 0.0)
			ray.delta_dist_y = fabs(1.0 / ray.ray_y);
		dda(map, &ray, ray_info + x);
		x++;
	}
}

void	projection(t_prog *prog)
{
	t_ray_info	ray_info[WIN_WIDTH];
	int			x;
	int			y;
	int			y_end;
	int			line_height;
	double		step;
	t_tex		*tex;
	int			color;

	raycasting(&prog->player, prog->map->map, ray_info);
	x = 0;
	while (x < WIN_WIDTH)
	{
		tex = prog->texs[ray_info[x].side];
		line_height = (WIN_HEIGHT / ray_info[x].perpWallDist);
		y = (line_height * -1 + WIN_HEIGHT) / 2;
		y_end = (line_height + WIN_HEIGHT) / 2;
		step = 1.0 * tex->height / line_height;
		while (y < y_end)
		{
			color = get_tex_color(tex, tex->width * ray_info[x].wall_x, )
			ft_put_pixel(x, y, color);
			y++;
		}
		x++;
	}
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
