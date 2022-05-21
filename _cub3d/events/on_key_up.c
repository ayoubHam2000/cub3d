/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:35:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/21 14:43:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	switch_door(t_prog *prog)
{
	t_player	*p;
	double		sx;
	double		sy;
	double		wall_x;
	double		wall_y;

	p = &prog->player;

	if (p->dir_x < 0)
		sx = (p->x - (int)p->x) * (1.0 / p->dir_x);
	else
		sx = ((int)p->x + 1 - p->x) * (1.0 / p->dir_x);
	if (p->dir_y < 0)
		sy = (p->y - (int)p->y) * (1.0 / p->dir_y);
	else
		sy = ((int)p->y + 1 - p->y) * (1.0 / p->dir_y);

	wall_x = p->x + sx * p->dir_y;
	wall_y = p->y + sy * p->dir_x;
	//wall_x = wall_x - (int)wall_x;
	wall_y = wall_y - p->x;
	printf("=> %.2f %.2f || %.2f %.2f || %.2f %.2f\n", p->x, p->y, sx, sy, wall_x, wall_y);
	if (p->dir_y < 0 && is_tile(p->map, p->x, p->y - 1))
		wall_y = 0;
	else if (p->dir_y >= 0 && is_tile(p->map, p->x, p->y + 1))
		wall_y = 1;
	if (p->dir_x < 0 && is_tile(p->map, p->x - 1, p->y))
		wall_x = 0;
	else if (p->dir_x >= 0 && is_tile(p->map, p->x + 1, p->y))
		wall_x = 1;
	printf("%.2f %.2f || %.2f %.2f || %.2f %.2f\n", p->x, p->y, sx, sy, wall_x, wall_y);
}

void	k(t_prog *prog)
{
	t_player	*p;
	t_ray		ray;
	int			f;
	int x, y;

	p = &prog->player;
	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	ray.flag = 0;
	raycasting(0.0, &ray, p);
	f = -1;
	x = p->x;
	y = p->y;
	if (get_key_type(p->map[ray.map_y][ray.map_x]) == 'D')
	{
		if (p->dir_y < 0 && ray.map_x == (int)x && ray.map_y == y - 1)
			f = 0;
		else if (p->dir_y >= 0 && ray.map_x == x && ray.map_y == y + 1)
			f = 1;
		else if (p->dir_x < 0 && ray.map_x == x - 1 && ray.map_y == y)
			f = 2;
		else if (p->dir_x >= 0 && ray.map_x == x + 1 && ray.map_y == y)
			f = 3;
		if (f != -1)
			p->map[ray.map_y][ray.map_x] *= -1;
	}
	printf("%d -> %d\n", p->map[ray.map_y][ray.map_x], p->map[ray.map_y][ray.map_x] * -1);
	printf("%d %d || %d %d || %d (%f, %f)\n",(int)p->x, (int)p->y, ray.map_x, ray.map_y, f, p->dir_x, p->dir_y);
}

int	on_key_up(int keycode, t_prog *prog)
{
	if (keycode == KEY_ESC)
		return (exit_cube3d(prog));
	else
	{
		if (keycode == KEY_L || keycode == KEY_R)
			prog->pressed_key[0] = -1;
		else if (keycode == KEY_S || keycode == KEY_W)
			prog->pressed_key[1] = -1;
		else if (keycode == KEY_A || keycode == KEY_D)
			prog->pressed_key[2] = -1;
		else if (keycode == KEY_SPACE)
			k(prog);
	}
	return (0);
}
