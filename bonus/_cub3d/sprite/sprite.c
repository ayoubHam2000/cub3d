/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:02:22 by mbel-bas          #+#    #+#             */
/*   Updated: 2022/06/03 20:55:09 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_tex_to_sprite(t_prog *p)
{
	t_sprite	**s;

	s = p->sprites;
	while (*s)
	{
		if ((*s)->k == 'e')
			enemy_e(p, *s);
		else if ((*s)->k == 'm')
			enemy_m(p, *s);
		else if ((*s)->k == 'h')
			heal_sprite(p, *s);
		else if ((*s)->k == 'b')
			bullet_sprite(p, *s);
		else
			normal_sprite(p, *s);
		s++;
	}
}

void	sprite_health(t_prog *prog, t_d_sprite *s, t_sprite *sprite, double *b)
{
	float	health_bar;
	int		h;

	s->sp = s->s_x;
	h = HEIGHT / 2;
	if ((sprite->k == 'e' || sprite->k == 'm') && sprite->health > 0)
	{
		if (sprite->k == 'e')
			health_bar = sprite->health / E_HEALTH;
		if (sprite->k == 'm')
			health_bar = sprite->health / M_HEALTH;
		while (s->sp < s->e_x)
		{
			if (s->tr_y > 0 && s->sp > 0 && s->sp < WIDTH && s->tr_y < b[s->sp])
			{
				ft_put_pixel(s->sp, s->s_y + h - prog->m_y + 2, 0xff0000);
				ft_put_pixel(s->sp, s->s_y + h - prog->m_y + 1, 0xff0000);
				if ((1.0 * s->sp - s->s_x) / (s->e_x - s->s_x) > health_bar)
					break ;
			}
			s->sp++;
		}
	}
}

static void	s_init(t_prog *prog, t_d_sprite	*s, t_sprite *sprite)
{
	t_player	*p;

	p = &prog->player;
	s->x = sprite->x - p->x;
	s->y = sprite->y - p->y;
	s->inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	s->tr_x = s->inv_det * (p->dir_y * s->x - p->dir_x * s->y);
	s->tr_y = s->inv_det * (-p->plane_y * s->x + p->plane_x * s->y);
	s->v_move_screen = (int)((0) / s->tr_y);
	s->screen_x = (int)((WIDTH / 2) * (1 + s->tr_x / s->tr_y));
	s->height = abs((int)((HEIGHT) / s->tr_y));
	s->s_y = -s->height / 2 + HEIGHT / 2 + s->v_move_screen;
	if (s->s_y < 0)
		s->s_y = 0;
	s->e_y = s->height / 2 + HEIGHT / 2 + s->v_move_screen;
	if (s->e_y >= HEIGHT)
		s->e_y = HEIGHT -1;
	s->sprite_width = abs((int)(HEIGHT / (s->tr_y)));
	s->s_x = -s->sprite_width / 2 + s->screen_x;
	if (s->s_x < 0)
		s->s_x = 0;
	s->e_x = s->sprite_width / 2 + s->screen_x;
	if (s->e_x >= WIDTH)
		s->e_x = WIDTH - 1;
}

void	draw_sprite(t_prog *prog, double *zb, t_d_sprite *s, t_sprite *sprite)
{
	int	y;
	int	d;
	int	color;

	s->sp = s->s_x;
	while (s->sp < s->e_x)
	{
		s->tex_x = (int)(256 * (s->sp - (-s->sprite_width / 2 + s->screen_x))
				* sprite->tex->width / s->sprite_width) / 256;
		if (s->tr_y > 0 && s->sp > 0 && s->sp < WIDTH && s->tr_y < zb[s->sp])
		{
			y = s->s_y;
			while (y < s->e_y)
			{
				d = (y) * 256 - (HEIGHT) * 128 + s->height * 128;
				s->tex_y = ((d * sprite->tex->height) / s->height) / 256;
				color = get_tex_color(sprite->tex, s->tex_x, s->tex_y);
				if ((color & 0x00FFFFFF) != 0)
					ft_put_pixel(s->sp, y + HEIGHT / 2 - prog->m_y,
						tr_c(color, sprite->hit, sprite->k, prog->frame));
				y++;
			}
		}
		s->sp++;
	}
}

void	sprite(t_prog *prog, double *z_buffer)
{
	t_sprite	**sprites;
	t_d_sprite	s;
	int			i;

	sort_sprites(prog->sprites, &prog->player);
	set_tex_to_sprite(prog);
	sprites = prog->sprites;
	i = -1;
	while (sprites[++i])
	{
		if (sprites[i]->k == 'h' && sprites[i]->health <= 0)
			continue ;
		s_init(prog, &s, sprites[i]);
		sprite_health(prog, &s, sprites[i], z_buffer);
		draw_sprite(prog, z_buffer, &s, sprites[i]);
		sprites[i]->hit--;
	}
}
