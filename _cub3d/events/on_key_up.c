/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:35:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/22 09:41:31 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	k(t_prog *prog)
{
	t_player	*p;
	t_ray		ray;
	int			f;
	int x, y;

	p = &prog->player;
	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	//ray.flag = 0;
	raycasting(0.0, &ray, p);
	f = -1;
	x = p->x;
	y = p->y;
	if (p->map_info[ray.map_y][ray.map_x].type == 'D')
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

void j(t_prog *prog)
{
	t_player	*p;
	t_ray		ray;
	int			f;
	int x, y;

	p = &prog->player;
	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	raycasting(0.0, &ray, p);
	if (ray.hit_door && ray.door_dist <= 1.4 && !prog->player.map_info[ray.door_y][ray.door_x].on)
	{
		printf("%d %d || %f\n",ray.door_x, ray.door_y, ray.door_dist);
		if (prog->player.map_info[ray.door_y][ray.door_x].timer == 0)
			prog->player.map_info[ray.door_y][ray.door_x].on = 1;
		else
			prog->player.map_info[ray.door_y][ray.door_x].on = -1;
	}
	else
		printf("no hit\n");
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
		{
			prog->player.timer += TIMER_CONST;
			//j(prog);
		}
	}
	return (0);
}
