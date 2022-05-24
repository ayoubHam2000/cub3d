/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:02:22 by mbel-bas          #+#    #+#             */
/*   Updated: 2022/05/24 20:22:12 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

// t_sprite	*get_sprites(t_prog *prog)
// {
// 	t_queue	*queue;

// 	queue = q_init();
// 	q_enqueue(queue, )
// }

void sprite(t_prog *prog, char *ZBuffer)
{
	t_player	*p;
	int			i;
	int			*sprite_order;
	t_sprite	*sprite;
	double		*sprite_distance;
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
	int			texwidth;
	int			y;
	int			d;
	int			color;
	
	p = &prog->player;
	i = -1;
	// while (++i < s_number)
	// {
	// 	sprite_distance[i] = ((p->x - sprite[i].x) * (p->x - sprite[i].x) + (p->y - sprite[i].y) * (p->y - sprite[i].y));
	// 	printf("huh\n");
	// 	//printf("%f\n",sprite_distance);
	// }
	//sort_sprite(sprite_order,sprite_distance,s_number);

	t_sprite s;

	s.x = 3.5;
	s.y = 4.5;
	s.tex = &prog->texs[0];

	i = -1;
	while (++i < s_number)
	{
		spriteX = s.x - p->x;
		spriteY = s.y - p->y;
		invDet = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
		transformX = invDet * (p->dir_y * spriteX - p->dir_x * spriteY);
		transformY = invDet * (-p->plane_y * spriteX + p->plane_x * spriteY);
		spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		spriteHeight = abs((int)(HEIGHT / transformY));
		drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		spriteWidth = abs((int)(HEIGHT / (transformY)));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
		 	drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		texwidth = get_prog()->texs[0]->width;
		while (stripe < drawEndX)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * get_prog()->texs[0]->width / spriteWidth) / 256;
			//if((transformY > 0 && stripe > 0 && stripe < WIDTH) && transformY < ZBuffer[stripe])
			//{
			y = drawStartY;
			while (y < drawEndY)
			{
				d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128;
				texY = ((d * get_prog()->texs[0]->height) / spriteHeight) / 256;
				color = get_tex_color(prog->texs[7], texX, texY);
				if((color & 0x00FFFFFF) != 0)
					ft_put_pixel(stripe,y,color);
				y++;
				}
			//}
			stripe++;	
		}
	}
}

/*int sort_sprite(int* order, double* dist, int amount)
{
    int i;
    int j;

    i = 0;
    while (i < number)
	{
		while ()
	}

}*/