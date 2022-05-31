/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:47:33 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/31 21:26:17 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ATTACK 0
#define STANDING 1
#define WALKING 2
#define DIEING 3

static void	sprite_move(t_sprite *s, char **map)
{
	double	next_x;
	double	next_y;
	int		a;
	int		b;

	a = 1;
	b = 1;
	if (s->vx < 0)
		a = -1;
	if (s->vy < 0)
		b = -1;
	next_x = s->x + s->vx + 0.2 * a;
	next_y = s->y + s->vy + 0.2 * b;
	if (map[(int)(s->y)][(int)(next_x)] != '1')
		s->x += s->vx;
	if (map[(int)(next_y)][(int)(s->x)] != '1')
		s->y += s->vy;
}

static t_pointf	unit_vector(double x, double y, double px, double py)
{
	t_pointf	res;
	double		u;

	res.x = (px - x);
	res.y = (py - y);
	u = sqrt(res.x * res.x + res.y * res.y);
	res.x /= u;
	res.y /= u;
	return (res);
}

void	enemy_e(t_prog *p, t_sprite *s)
{
	t_pointf	v;
	t_ray		ray;
	t_player	v_p;
	double		dist;
	int			i;
	int			f;
	int			r;

	v_p.map = p->player.map;
	v_p.map_info = p->player.map_info;
	i = -1;
	f = p->frame - s->save;
	if (s->is_die)
		s->tex = p->static_tex.enemy_1[11];
	else if (s->health <= 0)
	{
		s->tex = p->static_tex.enemy_1[(f % 80) / 20 + 8];
		if (f == 79)
			s->is_die = 1;
	}
	else
	{
		dist = (p->player.x - s->x)*(p->player.x - s->x) + (p->player.y - s->y)*(p->player.y - s->y);
		v = unit_vector(s->x, s->y, p->player.x, p->player.y);
		s->vx = 0;
		s->vy = 0;
		r = ft_rand() % 2;
		if (s->count <= 0)
		{
			if (dist > 100)
				s->state = STANDING;
			else
			{
				if (dist > 25)
					s->state = WALKING;
				else
					s->state = r * 2;
			}
			s->save = p->frame;
			s->count = 120;
		}
		f = p->frame - s->save;
		if (s->state == WALKING)
		{
			s->tex = p->static_tex.enemy_1[(f % 30) / 10 + 1];
			if (dist > 9)
			{

			s->vx = v.x * 0.07 + ((ft_rand() % 2) * 0.005);
			s->vy = v.y * 0.07 + ((ft_rand() % 2) * 0.005);

			}
			else
			{
				s->save = p->frame;
				f = 0;
				s->state = 0;
			}
		}
		else if (s->state == ATTACK)
		{
			s->tex = p->static_tex.enemy_1[(f % 120) / 30 + 4];
			if ((f % 120 == 90))
			{
				v_p.dir_x = v.x;
				v_p.dir_y = v.y;
				v_p.plane_x = - p->player.plane_x;
				v_p.plane_y = - p->player.plane_y;

				v_p.x = s->x;
				v_p.y = s->y;
				raycasting(0, &ray, &v_p);
				if (dist - ray.dist * ray.dist < 0)
				{
					p->player.hit = 15;
					p->player.health -= E_DAM;
				}
			}
			if ((f % 120) == 119)
				s->state = 1;
		}
		else if (s->state == STANDING)
			s->tex = p->static_tex.enemy_1[0];
		sprite_move(s, p->player.map);
		s->count--;
	}
}

void	enemy_m(t_prog *p, t_sprite *s)
{
	t_pointf	v;
	t_ray		ray;
	t_player	v_p;
	double		dist;
	int			i;
	int			f;
	int			r;

	v_p.map = p->player.map;
	v_p.map_info = p->player.map_info;
	i = -1;
	f = p->frame - s->save;
	if (s->is_die)
		s->tex = p->static_tex.enemy_2[9];
	else if (s->health <= 0)
	{
		s->tex = p->static_tex.enemy_2[(f % 60 ) / 20 + 7];
		if (f == 59)
			s->is_die = 1;
	}
	else
	{
		dist = (p->player.x - s->x)*(p->player.x - s->x) + (p->player.y - s->y)*(p->player.y - s->y);
		v = unit_vector(s->x, s->y, p->player.x, p->player.y);
		s->vx = 0;
		s->vy = 0;
		r = ft_rand() % 2;
		if (s->count <= 0)
		{
			if (dist > 100)
				s->state = STANDING;
			else
			{
				if (dist > 25)
					s->state = WALKING;
				else
					s->state = r * 2;
			}
			s->save = p->frame;
			s->count = 120;
		}
		f = p->frame - s->save;
		if (s->state == WALKING)
		{
			s->tex = p->static_tex.enemy_2[(f % 30) / 10 + 1];
			if (dist > 9)
			{

			s->vx = v.x * 0.1;
			s->vy = v.y * 0.1;

			}
			else
			{
				s->save = p->frame;
				f = 0;
				s->state = 0;
			}
		}
		else if (s->state == ATTACK)
		{
			s->tex = p->static_tex.enemy_2[(f % 120) / 40 + 4];
			if ((f % 120 == 90))
			{
				v_p.dir_x = v.x;
				v_p.dir_y = v.y;
				v_p.plane_x = - p->player.plane_x;
				v_p.plane_y = - p->player.plane_y;

				v_p.x = s->x;
				v_p.y = s->y;
				raycasting(0, &ray, &v_p);
				if (dist - ray.dist * ray.dist < 0)
				{
					p->player.hit = 15;
					p->player.health -= M_DAM;
				}
			}
			if ((f % 120) == 119)
				s->state = 1;
		}
		else if (s->state == STANDING)
			s->tex = p->static_tex.enemy_2[0];
		sprite_move(s, p->player.map);
		s->count--;
	}
}

void	normal_sprite(t_prog *p, t_sprite *s)
{
	int	i;

	i = p->map_keys[s->k - 33]->tex_index[0];
	s->tex = p->texs[i];
}

void	heal_sprite(t_prog *p, t_sprite *s)
{
	double	dist;

	dist = (p->player.x - s->x)*(p->player.x - s->x) + (p->player.y - s->y)*(p->player.y - s->y);
	if (dist < 1 && s->health > 0)
	{
		s->health = 0;
		p->player.health += HEAL_ADD;
		if (p->player.health > PLAYER_HEALTH)
			p->player.health = PLAYER_HEALTH;
		p->player.map[(int)s->y][(int)s->x] = '0';
	}
	s->tex = p->static_tex.heal[0];
}
