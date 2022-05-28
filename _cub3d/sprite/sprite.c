/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:02:22 by mbel-bas          #+#    #+#             */
/*   Updated: 2022/05/28 14:56:50 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void insertion_sort(t_sprite **sprites) 
{
	int			size;
	int			step;
	t_sprite	*key;
	int			j;

	size = 0;
	while (sprites[size])
		size++;
	step = 1;
	while (step < size)
	{
		key = sprites[step];
		j = step - 1;

		while (j >= 0 && key->dist >= sprites[j]->dist)
		{
			sprites[j + 1] = sprites[j];
			j--;
		}
		sprites[j + 1] = key;
		step++;
	}
}

t_sprite	*get_sprite(double x, double y, t_player *p)
{
	t_sprite	*s;

	s = ft_malloc(sizeof(t_sprite));
	s->x = x;
	s->y = y;
	s->tex = get_prog()->texs[get_tex(x, y)[0]];
	s->dist = ((s->x - p->x) * (s->x - p->x) + (s->y - p->y) * (s->y - p->y));
	return (s);
}

t_sprite	**map_sprite(t_player *p)
{
	t_queue		*queue;
	t_sprite	**sprites;
	int			i;
	int			x;
	int			y;

	queue = q_init();
	y = -1;
	while (p->map[++y])
	{
		x = -1;
		while(p->map[y][++x])
			if (p->map_info[y][x].type == 'S')
				q_enqueue(queue, get_sprite(x + 0.5, y + 0.5, p));
	}
	sprites = ft_malloc(sizeof(t_sprite *) * (queue->len + 1));
	i = 0;
	while (queue->len)
		sprites[i++] = q_dequeue(queue);
	sprites[i] = NULL;
	free_all(NULL);
	return (sprites);
}

void sprite(t_prog *prog, double *ZBuffer)
{
	t_player	*p;
	int			i;
	t_sprite	**sprites;
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			drawStartY;
	int			drawEndY;
	int			spriteWidth;
	int			drawStartX;
	int			drawEndX;
	int			stripe;
	int			texX;
	int			texY;
	int			y;
	int			d;
	int			color;

	p = &prog->player;
	sprites = map_sprite(p);
	insertion_sort(sprites);
	i = -1;
	while (sprites[++i])
	{
		spriteX = sprites[i]->x - p->x;
		spriteY = sprites[i]->y - p->y;
		invDet = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
		transformX = invDet * (p->dir_y * spriteX - p->dir_x * spriteY);
		transformY = invDet * (-p->plane_y * spriteX + p->plane_x * spriteY);
		spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		spriteHeight = abs((int)(HEIGHT / transformY));
		drawStartY = -spriteHeight / 2   + HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2  + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT -1;
		spriteWidth = abs((int)(HEIGHT / (transformY)));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
		 	drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		while (stripe < drawEndX)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprites[i]->tex->width / spriteWidth) / 256;
			if((transformY > 0 && stripe > 0 && stripe < WIDTH) && transformY < ZBuffer[stripe])
			{
				y = drawStartY;
				while (y < drawEndY)
				{
					d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128;
					texY = ((d * sprites[i]->tex->height) / spriteHeight) / 256;
					color = get_tex_color(sprites[i]->tex, texX, texY);
					if((color & 0x00FFFFFF) != 0)
						ft_put_pixel(stripe,y + HEIGHT / 2 - prog->m_y,color);
					y++;
				}
			}
			stripe++;	
		}
	}
}
