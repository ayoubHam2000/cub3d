/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_mouse_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:52:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/31 21:04:39 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_sgn(double x)
{
	if (x < 0)
		return (-1);
	return (1);
}

int	hit_sprite(t_prog *prog)
{
	t_ray	ray;
	int		i;
	double	x_1;
	double	x_2;
	double	y_1;
	double	y_2;
	double	a;
	double	b;
	double	delta;
	double	r;
	double	dist;
	char	k;

	raycasting(0.0, &ray, &prog->player);

	i = 0;
	while (prog->sprites[i])
		i++;
	while (--i >= 0)
	{
		k = prog->sprites[i]->k;
		if (prog->sprites[i]->health <= 0 || (k != 'e' && k != 'm'))
			continue;
		x_1 = prog->player.x - prog->sprites[i]->x;
		x_2 = x_1 + prog->player.dir_x;
		y_1 = prog->player.y - prog->sprites[i]->y;
		y_2 = y_1 + prog->player.dir_y;
		a = (y_2 - y_1) / (x_2 - x_1);
		b = y_2 - a * x_2;
		r = 0.2;
		delta = -4 * (b * b - r * r * (1 + a * a));
		dist = (y_1 * y_1) + (x_1 * x_1);
		if (delta > 0 && prog->sprites[i]->height / 2.5 > abs(HEIGHT / 2 - prog->m_y) && dist - ray.dist * ray.dist < 0 && dist < 100)
		{
			prog->sprites[i]->health -= 10;
			if (prog->sprites[i]->health <= 0)
				prog->sprites[i]->save = prog->frame;
			prog->sprites[i]->hit = 1;
			break ;
		}
		else
		{
			prog->sprites[i]->hit = 0;
		}
		//else
		//{
		//	printf("?? %d -- %d\n", prog->sprites[i]->height / 2, abs(HEIGHT / 2 - prog->m_y));
		//}
	}
	return (0);
}

void	stop_hit(t_prog *prog)
{
	int		i;

	i = 0;
	while (prog->sprites[i])
	{
		prog->sprites[i]->hit = 0;
		i++;
	}
}

int	on_mouse_down(int button, int x, int y, t_prog *prog)
{
	if (button == 1)
		prog->pressed_key[3] = button;
	return (0);
}

int	on_mouse_up(int button, int x, int y, t_prog *prog)
{
	if (button == 1)
	{
		prog->pressed_key[3] = -1;
		stop_hit(prog);
	}
	return (0);
}
