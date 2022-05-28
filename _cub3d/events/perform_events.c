/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:10:39 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/27 14:22:57 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define R_SPEED 0.06
#define M_SPEED 0.11
#define MOUSE_ROTATE_SPEED 0.17

static void	rotate(double *x, double *y, double angle)
{
	double	t;

	t = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = t * sin(angle) + *y * cos(angle);
}

static void	rotate_arrow(int keycode, t_player *p)
{
	double	d;

	d = 1;
	if (keycode == KEY_L)
		d = -1;
	if (get_prog()->pressed_key[1] != -1)
		d *= 0.75;
	rotate(&p->dir_x, &p->dir_y, R_SPEED * d);
	rotate(&p->plane_x, &p->plane_y, R_SPEED * d);
}

static void	rotate_mouse(t_prog *prog)
{
	static int	old_x;
	t_player	*p;
	double		d;

	if (old_x == prog->m_x)
		return ;
	p = &prog->player;
	d = (prog->old_m_x - prog->m_x) * MOUSE_ROTATE_SPEED;
	rotate(&p->dir_x, &p->dir_y, R_SPEED * d);
	rotate(&p->plane_x, &p->plane_y, R_SPEED * d);
	old_x = prog->m_x;
}

static void	move(t_player *p, char **map, int d)
{
	t_pointf	step;
	int			a;

	a = 1;
	if (d == KEY_S || d == KEY_D)
		a = -1;
	if (d == KEY_W || d == KEY_S)
	{
		step.x = p->dir_x * M_SPEED * a;
		step.y = p->dir_y * M_SPEED * a;
	}
	if (d == KEY_A || d == KEY_D)
	{
		step.x = p->dir_y * M_SPEED * a * -1.0;
		step.y = p->dir_x * M_SPEED * a;
	}
	if (p->map[(int)p->y][(int)(p->x + step.x * 4)] != '1')
		p->x = p->x + step.x;
	if (p->map[(int)(p->y + step.y * 4)][(int)p->x] != '1')
		p->y = p->y + step.y;
}

void	gun_hit(t_prog *prog)
{
	t_ray	ray;

	ray.pos_x = prog->player.x;
	ray.pos_y = prog->player.y;
	raycasting(0, &ray, &prog->player);
	if (ray.dist < 8)
		printf("%d, %d\n", ray.map_x, ray.map_y);
}

void	perform_events(t_prog *prog)
{
	t_player	*p;

	p = &prog->player;
	if (prog->pressed_key[0] != -1)
		rotate_arrow(prog->pressed_key[0], p);
	if (prog->pressed_key[1] != -1)
		move(p, prog->player.map, prog->pressed_key[1]);
	if (prog->pressed_key[2] != -1)
		move(p, prog->player.map, prog->pressed_key[2]);
	if (prog->pressed_key[3] == 1)
		gun_hit(prog);
	rotate_mouse(prog);
	prog->m_y = prog->old_m_y;
}
